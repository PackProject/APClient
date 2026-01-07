using LibWorkBench.Core;
using LibWorkBench.IO.Streams;
using LibWorkBench.Formats.Revolution.GX.Types;

namespace LibWorkBench.Formats.NW4R.LayoutLib.Layout.Types
{
    /// <summary>
    /// Indirect texture stage
    /// </summary>
    public sealed class IndirectStage : IUseBinary
    {
        /// <summary>
        /// Texture coordinate generator
        /// </summary>
        public GXTexCoordID TexCoordGen { get; set; }
            = GXTexCoordID.GX_TEXCOORD0;

        /// <summary>
        /// Texture map
        /// </summary>
        public GXTexMapID TexMap { get; set; } = GXTexMapID.GX_TEXMAP0;

        /// <summary>
        /// Texture scale (S)
        /// </summary>
        public GXIndTexScale ScaleS { get; set; } = GXIndTexScale.GX_ITS_1;

        /// <summary>
        /// Texture scale (T)
        /// </summary>
        public GXIndTexScale ScaleT { get; set; } = GXIndTexScale.GX_ITS_1;

        /// <summary>
        /// Deserializes the contents of this object from a file
        /// </summary>
        /// <param name="reader">Binary stream to the file</param>
        public void Read(ReadStream reader)
        {
            TexCoordGen = (GXTexCoordID)reader.ReadU8();
            TexMap = (GXTexMapID)reader.ReadU8();
            ScaleS = (GXIndTexScale)reader.ReadU8();
            ScaleT = (GXIndTexScale)reader.ReadU8();
        }

        /// <summary>
        /// Serializes the contents of this object to a file
        /// </summary>
        /// <param name="writer">Binary stream to the file</param>
        public void Write(WriteStream writer)
        {
            writer.WriteU8((byte)TexCoordGen);
            writer.WriteU8((byte)TexMap);
            writer.WriteU8((byte)ScaleS);
            writer.WriteU8((byte)ScaleT);
        }
    }
}
