using LibWorkBench.Core;
using LibWorkBench.IO.Streams;
using LibWorkBench.Formats.Revolution.GX.Types;

namespace LibWorkBench.Formats.NW4R.LayoutLib.Layout.Types
{
    /// <summary>
    /// TEV stage
    /// </summary>
    public sealed class TevStage : IUseBinary
    {
        /// <summary>
        /// Texture coordinate generator
        /// </summary>
        public GXTexCoordID TexCoordGen { get; set; }
            = GXTexCoordID.GX_TEXCOORD_NULL;

        /// <summary>
        /// Color channel ID
        /// </summary>
        public GXChannelID ColorChannel { get; set; }
            = GXChannelID.GX_COLOR0A0;

        /// <summary>
        /// Texture map
        /// </summary>
        public GXTexMapID TexMap { get; set; } = GXTexMapID.GX_TEXMAP_NULL;

        /// <summary>
        /// TEV swap table slot
        /// </summary>
        public GXTevSwapSel SwapSelect { get; set; }
            = GXTevSwapSel.GX_TEV_SWAP0;

        /// <summary>
        /// TEV color combiner inputs
        /// </summary>
        public TevColorInput ColorInput { get; set; } = new();

        /// <summary>
        /// TEV alpha combiner inputs
        /// </summary>
        public TevAlphaInput AlphaInput { get; set; } = new();

        /// <summary>
        /// Indirect texture stage
        /// </summary>
        public GXIndTexStageID IndirectStage { get; set; }
            = GXIndTexStageID.GX_INDTEXSTAGE0;

        /// <summary>
        /// Indirect texture bias
        /// </summary>
        public GXIndTexBiasSel IndirectBias { get; set; }
            = GXIndTexBiasSel.GX_ITB_NONE;

        /// <summary>
        /// Indirect texture matrix
        /// </summary>
        public GXIndTexMtxID IndirectMtx { get; set; }
            = GXIndTexMtxID.GX_ITM_OFF;

        /// <summary>
        /// Indirect texture wrap mode (S)
        /// </summary>
        public GXIndTexWrap IndirectWrapS { get; set; }
            = GXIndTexWrap.GX_ITW_OFF;

        /// <summary>
        /// Indirect texture wrap mode (T)
        /// </summary>
        public GXIndTexWrap IndirectWrapT { get; set; }
            = GXIndTexWrap.GX_ITW_OFF;

        /// <summary>
        /// Indirect texture format
        /// </summary>
        public GXIndTexFormat IndirectFormat { get; set; }
            = GXIndTexFormat.GX_ITF_8;

        /// <summary>
        /// Whether to add texture coordinate results from the previous TEV stage
        /// </summary>
        public bool IndirectAddPrev { get; set; } = false;

        /// <summary>
        /// Whether to use unmodified texture coordinates
        /// </summary>
        public bool IndirectUtcLod { get; set; } = false;

        /// <summary>
        /// Indirect texture alpha selection
        /// </summary>
        public GXIndTexAlphaSel IndirectAlpha { get; set; }
            = GXIndTexAlphaSel.GX_ITBA_OFF;

        /// <summary>
        /// Deserializes the contents of this object from a file
        /// </summary>
        /// <param name="reader">Binary stream to the file</param>
        public void Read(ReadStream reader)
        {
            TexCoordGen = (GXTexCoordID)reader.ReadU8();
            ColorChannel = (GXChannelID)reader.ReadU8();
            TexMap = (GXTexMapID)reader.ReadU8();
            SwapSelect = (GXTevSwapSel)reader.ReadU8();
            ColorInput.Read(reader);
            AlphaInput.Read(reader);
            IndirectStage = (GXIndTexStageID)reader.ReadU8();

            byte indBiMt = reader.ReadU8();
            IndirectBias = (GXIndTexBiasSel)(indBiMt >> 0 & 0b111);
            IndirectMtx = (GXIndTexMtxID)(indBiMt >> 3 & 0b1111);

            byte indWrap = reader.ReadU8();
            IndirectWrapS = (GXIndTexWrap)(indWrap >> 0 & 0b111);
            IndirectWrapT = (GXIndTexWrap)(indWrap >> 3 & 0b111);

            byte indFoAdUtAl = reader.ReadU8();
            IndirectFormat = (GXIndTexFormat)(indFoAdUtAl >> 0 & 0b11);
            IndirectAddPrev = (indFoAdUtAl >> 2 & 0b1) != 0;
            IndirectUtcLod = (indFoAdUtAl >> 3 & 0b1) != 0;
            IndirectAlpha = (GXIndTexAlphaSel)(indFoAdUtAl >> 4 & 0b11);
        }

        /// <summary>
        /// Serializes the contents of this object to a file
        /// </summary>
        /// <param name="writer">Binary stream to the file</param>
        public void Write(WriteStream writer)
        {
            writer.WriteU8((byte)TexCoordGen);
            writer.WriteU8((byte)ColorChannel);
            writer.WriteU8((byte)TexMap);
            writer.WriteU8((byte)SwapSelect);
            ColorInput.Write(writer);
            AlphaInput.Write(writer);
            writer.WriteU8((byte)IndirectStage);

            byte indBiMt = 0;
            indBiMt |= (byte)(((int)IndirectBias & 0b111) << 0);
            indBiMt |= (byte)(((int)IndirectMtx & 0b1111) << 3);
            writer.WriteU8(indBiMt);

            byte indWrap = 0;
            indWrap |= (byte)(((int)IndirectWrapS & 0b111) << 0);
            indWrap |= (byte)(((int)IndirectWrapT & 0b111) << 3);
            writer.WriteU8(indWrap);

            byte indFoAdUtAl = 0;
            indFoAdUtAl |= (byte)(((int)IndirectFormat & 0b11) << 0);
            indFoAdUtAl |= (byte)((IndirectAddPrev ? 1 : 0) << 2);
            indFoAdUtAl |= (byte)((IndirectUtcLod ? 1 : 0) << 3);
            indFoAdUtAl |= (byte)(((int)IndirectAlpha & 0b11) << 4);
            writer.WriteU8(indFoAdUtAl);
        }
    }
}
