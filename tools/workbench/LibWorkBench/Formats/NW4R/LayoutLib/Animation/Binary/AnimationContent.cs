using LibWorkBench.Core;
using LibWorkBench.Exceptions;
using LibWorkBench.IO.Encodings;
using LibWorkBench.IO.Streams;
using LibWorkBench.Formats.NW4R.LayoutLib.Animation;
using LibWorkBench.Formats.NW4R.LayoutLib.Animation.Types;

namespace LibWorkBench.Formats.NW4R.LayoutLib.Animation.Binary
{
    /// <summary>
    /// Layout animation content
    /// </summary>
    public sealed class AnimationContent : IUseBinary
    {
        /// <summary>
        /// Animation target name
        /// </summary>
        public string Target { get; set; } = "";

        /// <summary>
        /// Animation content type
        /// </summary>
        public AnimContentKind Kind { get; set; } = AnimContentKind.Pane;

        /// <summary>
        /// Animation data
        /// </summary>
        public List<AnimationInfo> Animations { get; set; } = new();

        /// <summary>
        /// Deserializes the contents of this object from a file
        /// </summary>
        /// <param name="reader">Binary stream to the file</param>
        public void Read(ReadStream reader)
        {
            // Info offsets are relative to this content
            long contentPos = (long)reader.Position;

            Target = reader.ReadString(
                maxlen: AnimationDefine.TARGET_NAME_LEN,
                exact: true
            );

            byte infoNum = reader.ReadU8();
            Kind = (AnimContentKind)reader.ReadU8();
            reader.Align(4);

            // Parse animation info table
            List<uint> infoOffsets = new();
            for (uint i = 0; i < infoNum; i++)
            {
                infoOffsets.Add(reader.ReadU32());
            }

            foreach (var it in infoOffsets)
            {
                if ((ulong)contentPos + it > reader.Length)
                {
                    throw new FileBrokenException("Invalid info offset");
                }

                reader.Seek(contentPos + it, SeekOrigin.Begin);

                AnimationInfo info = new();
                info.Read(reader);
                Animations.Add(info);
            }
        }

        /// <summary>
        /// Serializes the contents of this object to a file
        /// </summary>
        /// <param name="writer">Binary stream to the file</param>
        public void Write(WriteStream writer)
        {
            WorkMemWriter work = new(new BinaryCharEncoding(),
                                     writer.Endian);

            work.WriteString(
                Target,
                maxlen: AnimationDefine.TARGET_NAME_LEN,
                terminate: false,
                exact: true
            );

            if (Animations.Count > byte.MaxValue)
            {
                throw new FileBrokenException("Too many animation infos");
            }

            work.WriteU8((byte)Animations.Count);
            work.WriteU8((byte)Kind);
            work.Align(4);

            // Reserve space for animation info offset table
            long infoTblPos = (long)work.Position;
            work.WriteDebugFill((uint)Animations.Count * sizeof(uint));

            List<uint> offsetList = new();
            foreach (var it in Animations)
            {
                if (work.Position > uint.MaxValue)
                {
                    throw new FileBrokenException(
                        "Animation info table is too large");
                }

                offsetList.Add((uint)work.Position);
                it.Write(work);
            }

            // Go back and fix offset table
            work.Seek(infoTblPos, SeekOrigin.Begin);
            offsetList.ForEach(work.WriteU32);

            // Flush data to the real stream
            writer.Write(work.Buffer, work.Length);
        }
    }
}
