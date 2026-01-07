using LibWorkBench.Core;
using LibWorkBench.IO.Streams;
using LibWorkBench.Formats.Revolution.GX.Types;

namespace LibWorkBench.Formats.NW4R.LayoutLib.Layout.Types
{
    /// <summary>
    /// Texture coordinate generator configuration
    /// </summary>
    public sealed class TexCoordGen : IUseBinary
    {
        /// <summary>
        /// Generator type
        /// </summary>
        public GXTexGenType Type { get; set; } = GXTexGenType.GX_TG_MTX2x4;

        /// <summary>
        /// Generator source
        /// </summary>
        public GXTexGenSrc Src { get; set; } = GXTexGenSrc.GX_TG_TEX0;

        /// <summary>
        /// Texture matrix
        /// </summary>
        public GXTexMtx Mtx { get; set; } = GXTexMtx.GX_IDENTITY;

        /// <summary>
        /// Deserializes the contents of this object from a file
        /// </summary>
        /// <param name="reader">Binary stream to the file</param>
        public void Read(ReadStream reader)
        {
            Type = (GXTexGenType)reader.ReadU8();
            Src = (GXTexGenSrc)reader.ReadU8();
            Mtx = (GXTexMtx)reader.ReadU8();
            reader.Align(4);
        }

        /// <summary>
        /// Serializes the contents of this object to a file
        /// </summary>
        /// <param name="writer">Binary stream to the file</param>
        public void Write(WriteStream writer)
        {
            writer.WriteU8((byte)Type);
            writer.WriteU8((byte)Src);
            writer.WriteU8((byte)Mtx);
            writer.Align(4);
        }
    }
}
