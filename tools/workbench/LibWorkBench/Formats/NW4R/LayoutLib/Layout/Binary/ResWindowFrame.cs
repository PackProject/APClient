using LibWorkBench.Core;
using LibWorkBench.IO.Streams;
using LibWorkBench.Formats.NW4R.LayoutLib.Layout.Types;

namespace LibWorkBench.Formats.NW4R.LayoutLib.Layout.Binary
{
    /// <summary>
    /// Window frame (binary-view)
    /// </summary>
    public sealed class ResWindowFrame : IUseBinary
    {
        /// <summary>
        /// Material list index
        /// </summary>
        public ushort MaterialIndex { get; set; } = 0;

        /// <summary>
        /// Texture flip type
        /// </summary>
        public TextureFlip TextureFlip { get; set; } = TextureFlip.None;

        /// <summary>
        /// Deserializes the contents of this object from a file
        /// </summary>
        /// <param name="reader">Binary stream to the file</param>
        public void Read(ReadStream reader)
        {
            MaterialIndex = reader.ReadU16();
            TextureFlip = (TextureFlip)reader.ReadU8();

            // Padding after texture flip
            reader.Align(4);
        }

        /// <summary>
        /// Serializes the contents of this object to a file
        /// </summary>
        /// <param name="writer">Binary stream to the file</param>
        public void Write(WriteStream writer)
        {
            writer.WriteU16(MaterialIndex);
            writer.WriteU8((byte)TextureFlip);

            // Padding after texture flip
            writer.Align(4);
        }
    }
}
