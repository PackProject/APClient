using LibWorkBench.IO.Streams;
using LibWorkBench.Formats.NW4R.LayoutLib.Animation.Types.Details;

namespace LibWorkBench.Formats.NW4R.LayoutLib.Animation.Types
{
    /// <summary>
    /// Hermite interpolation keyframe
    /// </summary>
    public sealed class HermiteKey : KeyFrameImpl
    {
        /// <summary>
        /// Frame value
        /// </summary>
        public float Value { get; set; } = 0.0f;

        /// <summary>
        /// Hermite slope
        /// </summary>
        public float Slope { get; set; } = 0.0f;

        /// <summary>
        /// Constructor
        /// </summary>
        public HermiteKey()
            : base(Type.Hermite)
        {
        }

        /// <summary>
        /// Deserializes the contents of this object from a file
        /// </summary>
        /// <param name="reader">Binary stream to the file</param>
        public override void Read(ReadStream reader)
        {
            Frame = reader.ReadF32();
            Value = reader.ReadF32();
            Slope = reader.ReadF32();
        }

        /// <summary>
        /// Serializes the contents of this object to a file
        /// </summary>
        /// <param name="writer">Binary stream to the file</param>
        public override void Write(WriteStream writer)
        {
            writer.WriteF32(Frame);
            writer.WriteF32(Value);
            writer.WriteF32(Slope);
        }
    }
}
