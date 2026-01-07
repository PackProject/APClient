using LibWorkBench.Core;
using LibWorkBench.IO.Streams;

namespace LibWorkBench.Formats.NW4R.LayoutLib.Layout.Types
{
    /// <summary>
    /// Size with width/height components
    /// </summary>
    public sealed class Size : IUseBinary
    {
        /// <summary>
        /// Size width (in pixels)
        /// </summary>
        public float Width { get; set; } = 0.0f;

        /// <summary>
        /// Size height (in pixels)
        /// </summary>
        public float Height { get; set; } = 0.0f;

        /// <summary>
        /// Deserializes the contents of this object from a file
        /// </summary>
        /// <param name="reader">Binary stream to the file</param>
        public void Read(ReadStream reader)
        {
            Width = reader.ReadF32();
            Height = reader.ReadF32();
        }

        /// <summary>
        /// Serializes the contents of this object to a file
        /// </summary>
        /// <param name="writer">Binary stream to the file</param>
        public void Write(WriteStream writer)
        {
            writer.WriteF32(Width);
            writer.WriteF32(Height);
        }
    }
}
