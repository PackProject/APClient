using LibWorkBench.Core;
using LibWorkBench.IO.Streams;
using LibWorkBench.Formats.NW4R.SystemLib.Types;

namespace LibWorkBench.Formats.NW4R.LayoutLib.Layout.Types
{
    /// <summary>
    /// Texture coordinates
    /// </summary>
    public sealed class TexCoord : IUseBinary
    {
        /// <summary>
        /// Top-left coordinate
        /// </summary>
        public VEC2 LeftTop { get; set; } = new();

        /// <summary>
        /// Top-right coordinate
        /// </summary>
        public VEC2 RightTop { get; set; } = new();

        /// <summary>
        /// Bottom-left coordinate
        /// </summary>
        public VEC2 LeftBottom { get; set; } = new();

        /// <summary>
        /// Bottom-right coordinate
        /// </summary>
        public VEC2 RightBottom { get; set; } = new();

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
