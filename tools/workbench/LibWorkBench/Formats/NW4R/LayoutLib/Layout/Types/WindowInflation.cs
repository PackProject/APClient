using LibWorkBench.Core;
using LibWorkBench.IO.Streams;

namespace LibWorkBench.Formats.NW4R.LayoutLib.Layout.Types
{
    /// <summary>
    /// Window content inflation
    /// </summary>
    public sealed class WindowInflation : IUseBinary
    {
        /// <summary>
        /// Inflation from the left edge
        /// </summary>
        public float Left { get; set; } = 0.0f;

        /// <summary>
        /// Inflation from the right edge
        /// </summary>
        public float Right { get; set; } = 0.0f;

        /// <summary>
        /// Inflation from the top edge
        /// </summary>
        public float Top { get; set; } = 0.0f;

        /// <summary>
        /// Inflation from the bottom edge
        /// </summary>
        public float Bottom { get; set; } = 0.0f;

        /// <summary>
        /// Deserializes the contents of this object from a file
        /// </summary>
        /// <param name="reader">Binary stream to the file</param>
        public void Read(ReadStream reader)
        {
            Left = reader.ReadF32();
            Right = reader.ReadF32();
            Top = reader.ReadF32();
            Bottom = reader.ReadF32();
        }

        /// <summary>
        /// Serializes the contents of this object to a file
        /// </summary>
        /// <param name="writer">Binary stream to the file</param>
        public void Write(WriteStream writer)
        {
            writer.WriteF32(Left);
            writer.WriteF32(Right);
            writer.WriteF32(Top);
            writer.WriteF32(Bottom);
        }
    }
}
