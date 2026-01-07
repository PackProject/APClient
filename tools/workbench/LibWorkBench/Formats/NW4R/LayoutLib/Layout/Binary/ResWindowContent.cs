using LibWorkBench.Core;
using LibWorkBench.IO.Streams;
using LibWorkBench.Formats.NW4R.LayoutLib.Layout.Types;

namespace LibWorkBench.Formats.NW4R.LayoutLib.Layout.Binary
{
    /// <summary>
    /// Window content (binary-view)
    /// </summary>
    public sealed class ResWindowContent : IUseBinary
    {
        /// <summary>
        /// Vertex colors
        /// </summary>
        public VertexColorSet VertexColors { get; set; } = new();

        /// <summary>
        /// Material list index
        /// </summary>
        public ushort MaterialIndex { get; set; } = 0;

        /// <summary>
        /// Number of texture coordinates
        /// </summary>
        public byte TexCoordNum { get; set; } = 0;

        /// <summary>
        /// Deserializes the contents of this object from a file
        /// </summary>
        /// <param name="reader">Binary stream to the file</param>
        public void Read(ReadStream reader)
        {
            VertexColors.Read(reader);

            MaterialIndex = reader.ReadU16();
            TexCoordNum = reader.ReadU8();
            reader.Align(4);
        }

        /// <summary>
        /// Serializes the contents of this object to a file
        /// </summary>
        /// <param name="writer">Binary stream to the file</param>
        public void Write(WriteStream writer)
        {
            VertexColors.Write(writer);

            writer.WriteU16(MaterialIndex);
            writer.WriteU8(TexCoordNum);
            writer.Align(4);
        }
    }
}
