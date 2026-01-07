using LibWorkBench.Core;
using LibWorkBench.IO.Streams;
using LibWorkBench.Formats.Revolution.GX.Types;

namespace LibWorkBench.Formats.NW4R.LayoutLib.Layout.Binary
{
    /// <summary>
    /// Material texture map (binary-view)
    /// </summary>
    public sealed class ResTexMap : IUseBinary
    {
        /// <summary>
        /// Texture list index
        /// </summary>
        public ushort TextureIndex { get; set; } = 0;

        /// <summary>
        /// Texture wrap mode (S)
        /// </summary>
        public GXTexWrapMode WrapS { get; set; } = GXTexWrapMode.GX_CLAMP;

        /// <summary>
        /// Texture wrap mode (T)
        /// </summary>
        public GXTexWrapMode WrapT { get; set; } = GXTexWrapMode.GX_CLAMP;

        /// <summary>
        /// Deserializes the contents of this object from a file
        /// </summary>
        /// <param name="reader">Binary stream to the file</param>
        public void Read(ReadStream reader)
        {
            TextureIndex = reader.ReadU16();
            WrapS = (GXTexWrapMode)reader.ReadU8();
            WrapT = (GXTexWrapMode)reader.ReadU8();
        }

        /// <summary>
        /// Serializes the contents of this object to a file
        /// </summary>
        /// <param name="writer">Binary stream to the file</param>
        public void Write(WriteStream writer)
        {
            writer.WriteU16(TextureIndex);
            writer.WriteU8((byte)WrapS);
            writer.WriteU8((byte)WrapT);
        }
    }
}
