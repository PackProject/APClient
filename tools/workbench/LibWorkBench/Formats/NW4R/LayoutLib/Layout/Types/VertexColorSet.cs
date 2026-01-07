using LibWorkBench.Core;
using LibWorkBench.IO.Streams;
using LibWorkBench.Formats.Revolution.GX.Types;

namespace LibWorkBench.Formats.NW4R.LayoutLib.Layout.Types
{
    /// <summary>
    /// Vertex color set
    /// </summary>
    public sealed class VertexColorSet : IUseBinary
    {
        /// <summary>
        /// Top-left corner vertex
        /// </summary>
        public GXColor LeftTop { get; set; } = new();

        /// <summary>
        /// Top-right corner vertex
        /// </summary>
        public GXColor RightTop { get; set; } = new();

        /// <summary>
        /// Bottom-left corner vertex
        /// </summary>
        public GXColor LeftBottom { get; set; } = new();

        /// <summary>
        /// Bottom-right corner vertex
        /// </summary>
        public GXColor RightBottom { get; set; } = new();

        /// <summary>
        /// Deserializes the contents of this object from a file
        /// </summary>
        /// <param name="reader">Binary stream to the file</param>
        public void Read(ReadStream reader)
        {
            LeftTop.Read(reader);
            RightTop.Read(reader);
            LeftBottom.Read(reader);
            RightBottom.Read(reader);
        }

        /// <summary>
        /// Serializes the contents of this object to a file
        /// </summary>
        /// <param name="writer">Binary stream to the file</param>
        public void Write(WriteStream writer)
        {
            LeftTop.Write(writer);
            RightTop.Write(writer);
            LeftBottom.Write(writer);
            RightBottom.Write(writer);
        }
    }
}
