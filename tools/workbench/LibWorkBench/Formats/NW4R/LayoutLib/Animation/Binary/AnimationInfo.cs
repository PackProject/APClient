using LibWorkBench.Core;
using LibWorkBench.Exceptions;
using LibWorkBench.IO.Encodings;
using LibWorkBench.IO.Streams;
using LibWorkBench.Formats.NW4R.LayoutLib.Animation;
using LibWorkBench.Formats.NW4R.LayoutLib.Animation.Types;
using LibWorkBench.Formats.NW4R.LayoutLib.Animation.Types.Details;
using LibWorkBench.Formats.NW4R.LayoutLib.Animation.Utility;

namespace LibWorkBench.Formats.NW4R.LayoutLib.Animation.Binary
{
    /// <summary>
    /// Layout animation info
    /// </summary>
    public sealed class AnimationInfo : IUseBinary
    {
        /// <summary>
        /// Animation info type
        /// </summary>
        public AnimInfoKind Kind { get; set; } = AnimInfoKind.PaneSrt;

        /// <summary>
        /// Targets this animation will control
        /// </summary>
        public List<AnimationTargetImpl> Targets { get; set; } = new();

        /// <summary>
        /// Creates a new animation target for this animation info
        /// </summary>
        /// <returns>Animation target matching this info's animation type</returns>
        /// <exception cref="OperationException">Animation info type is invalid</exception>
        public AnimationTargetImpl CreateTarget()
        {
            switch (Kind)
            {
                case AnimInfoKind.PaneSrt:
                    return new AnimationTargetPaneSrt();

                case AnimInfoKind.PaneVis:
                    return new AnimationTargetPaneVis();

                case AnimInfoKind.VtxClr:
                    return new AnimationTargetVtxClr();

                case AnimInfoKind.MatClr:
                    return new AnimationTargetMatClr();

                case AnimInfoKind.TexSrt:
                    return new AnimationTargetTexSrt();

                case AnimInfoKind.TexPat:
                    return new AnimationTargetTexPat();

                case AnimInfoKind.IndTexSrt:
                    return new AnimationTargetIndTexSrt();

                default:
                    throw new OperationException(
                        $"Invalid animation info type: {Kind}");
            }
        }

        /// <summary>
        /// Deserializes the contents of this object from a file
        /// </summary>
        /// <param name="reader">Binary stream to the file</param>
        public void Read(ReadStream reader)
        {
            // Target offsets are relative to this info
            long infoPos = (long)reader.Position;

            string signature = reader.ReadString(
                maxlen: AnimationDefine.ANIM_INFO_SIGNATURE_LEN,
                exact: true
            );

            Kind = AnimationUtil.GetAnimInfoKind(signature);

            byte targetNum = reader.ReadU8();
            reader.Align(4);

            // Parse animation target table
            List<uint> targetOffsets = new();
            for (uint i = 0; i < targetNum; i++)
            {
                targetOffsets.Add(reader.ReadU32());
            }

            foreach (var it in targetOffsets)
            {
                if ((ulong)infoPos + it > reader.Length)
                {
                    throw new FileBrokenException("Invalid target offset");
                }

                reader.Seek(infoPos + it, SeekOrigin.Begin);

                AnimationTargetImpl target = CreateTarget();
                target.Read(reader);
                Targets.Add(target);
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

            if (Targets.Count > byte.MaxValue)
            {
                throw new FileBrokenException("Too many animation targets");
            }

            work.WriteU32((uint)Kind);

            work.WriteU8((byte)Targets.Count);
            work.Align(4);

            // Reserve space for offset table
            long offsetTablePos = (long)work.Position;
            work.WriteDebugFill((ulong)Targets.Count * sizeof(uint));

            // Calculate offset for each material
            List<uint> offsetList = new();
            foreach (var it in Targets)
            {
                if (work.Position > uint.MaxValue)
                {
                    throw new FileBrokenException("Target list is too large");
                }

                offsetList.Add((uint)work.Position);
                it.Write(work);
            }

            // Go back and fix the offset table
            work.Seek(offsetTablePos, SeekOrigin.Begin);
            offsetList.ForEach(work.WriteU32);

            // Flush data to the real stream
            writer.Write(work.Buffer, work.Length);
        }
    }
}
