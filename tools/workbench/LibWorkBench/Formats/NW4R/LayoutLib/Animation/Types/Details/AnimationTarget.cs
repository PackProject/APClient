using LibWorkBench.Core;
using LibWorkBench.Exceptions;
using LibWorkBench.IO.Encodings;
using LibWorkBench.IO.Streams;

namespace LibWorkBench.Formats.NW4R.LayoutLib.Animation.Types.Details
{
    /// <summary>
    /// Specialized template for layout animation targets
    /// </summary>
    public abstract class AnimationTarget<TAnimTarget, TKeyFrame> : AnimationTargetImpl, IUseBinary
        where TAnimTarget : Enum
        where TKeyFrame : KeyFrameImpl, new()
    {
        /// <summary>
        /// Target element type
        /// </summary>
        // TODO(kiwi) Better way to set default value?
        public TAnimTarget TargetType { get; set; } = (TAnimTarget)(dynamic)0;

        /// <summary>
        /// Animation keyframes
        /// </summary>
        public List<TKeyFrame> KeyFrames { get; set; } = new();

        /// <summary>
        /// Deserializes the contents of this object from a file
        /// </summary>
        /// <param name="reader">Binary stream to the file</param>
        public override void Read(ReadStream reader)
        {
            // Keyframe offsets are relative to this target
            long targetPos = (long)reader.Position;

            TargetID = reader.ReadU8();
            TargetType = (TAnimTarget)(dynamic)reader.ReadU8();

            // TODO(kiwi) Can we send KeyType as a template argument?
            KeyFrameImpl.Type curveType = (KeyFrameImpl.Type)reader.ReadU8();
            if (curveType != new TKeyFrame().KeyType)
            {
                throw new FileBrokenException("Not for this class");
            }

            reader.Align(4);

            ushort keyNum = reader.ReadU16();
            reader.Align(4);

            uint keysOffset = reader.ReadU32();
            if ((ulong)targetPos + keysOffset > reader.Length)
            {
                throw new FileBrokenException("Invalid keyframe offset");
            }

            // Parse keyframes
            reader.Seek(targetPos + keysOffset, SeekOrigin.Begin);

            for (uint i = 0; i < keyNum; i++)
            {
                TKeyFrame frame = new();
                frame.Read(reader);
                KeyFrames.Add(frame);
            }
        }

        /// <summary>
        /// Serializes the contents of this object to a file
        /// </summary>
        /// <param name="writer">Binary stream to the file</param>
        public override void Write(WriteStream writer)
        {
            WorkMemWriter work = new(new BinaryCharEncoding(),
                                     writer.Endian);

            if (KeyFrames.Count > ushort.MaxValue)
            {
                throw new FileBrokenException("Too many keyframes");
            }

            // Since they all match, we can assume the type from the first one
            KeyFrameImpl.Type keyType = KeyFrames.First().KeyType;

            if (KeyFrames.Any(it => it.KeyType != keyType))
            {
                throw new FileBrokenException("Cannot mix types of keyframes");
            }

            work.WriteU8(TargetID);
            work.WriteU8((byte)(dynamic)TargetType);

            work.WriteU8((byte)keyType);
            work.Align(4);

            work.WriteU16((ushort)KeyFrames.Count);
            work.Align(4);

            // Reserve space for keyframe offset
            long keyOffsetPos = (long)work.Position;
            work.WriteDebugFill(sizeof(uint));

            // Write keyframe data
            uint keyOffset = (uint)work.Position;
            KeyFrames.ForEach(it => it.Write(work));

            // Go back and fix keyframe offset
            work.Seek(keyOffsetPos, SeekOrigin.Begin);
            work.WriteU32(keyOffset);

            // Flush data to the real stream
            writer.Write(work.Buffer, work.Length);
        }
    }
}
