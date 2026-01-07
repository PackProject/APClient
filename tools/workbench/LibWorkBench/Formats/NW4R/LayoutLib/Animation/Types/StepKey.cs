using LibWorkBench.IO.Streams;
using LibWorkBench.Formats.NW4R.LayoutLib.Animation.Types.Details;

namespace LibWorkBench.Formats.NW4R.LayoutLib.Animation.Types
{
    /// <summary>
    /// Linear step keyframe
    /// </summary>
    public sealed class StepKey : KeyFrameImpl
    {
        /// <summary>
        /// Frame value
        /// </summary>
        public ushort Value { get; set; } = 0;

        /// <summary>
        /// Constructor
        /// </summary>
        public StepKey()
            : base(Type.Step)
        {
        }

        /// <summary>
        /// Deserializes the contents of this object from a file
        /// </summary>
        /// <param name="reader">Binary stream to the file</param>
        public override void Read(ReadStream reader)
        {
            Frame = reader.ReadF32();
            Value = reader.ReadU16();
            reader.Align(4);
        }

        /// <summary>
        /// Serializes the contents of this object to a file
        /// </summary>
        /// <param name="writer">Binary stream to the file</param>
        public override void Write(WriteStream writer)
        {
            writer.WriteF32(Frame);
            writer.WriteU16(Value);
            writer.Align(4);
        }
    }
}
