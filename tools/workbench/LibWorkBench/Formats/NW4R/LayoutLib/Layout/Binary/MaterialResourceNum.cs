using LibWorkBench.Core;
using LibWorkBench.Exceptions;
using LibWorkBench.IO.Streams;
using LibWorkBench.Formats.NW4R.LayoutLib.Layout;
using LibWorkBench.Formats.Revolution.GX.Types;

namespace LibWorkBench.Formats.NW4R.LayoutLib.Layout.Binary
{
    /// <summary>
    /// Material resource counts
    /// </summary>
    public sealed class MaterialResourceNum : IUseBinary
    {
        /// <summary>
        /// Number of texture maps used by this material
        /// </summary>
        public byte TexMapNum { get; set; } = 0;

        /// <summary>
        /// Number of texture S/R/T transformations used by this material
        /// </summary>
        public byte TexSrtNum { get; set; } = 0;

        /// <summary>
        /// Number of texture coordinate generators used by this material
        /// </summary>
        public byte TexCoordGenNum { get; set; } = 0;

        /// <summary>
        /// Whether this material uses a TEV swap table
        /// </summary>
        public bool HasTevSwapTable { get; set; } = false;

        /// <summary>
        /// Number of indirect texture S/R/T transformations used by this material
        /// </summary>
        public byte IndTexSrtNum { get; set; } = 0;

        /// <summary>
        /// Number of indirect stages used by this material
        /// </summary>
        public byte IndStageNum { get; set; } = 0;

        /// <summary>
        /// Number of TEV stages used by this material
        /// </summary>
        public byte TevStageNum { get; set; } = 0;

        /// <summary>
        /// Whether this material uses a visibility test
        /// </summary>
        public bool HasAlphaCompare { get; set; } = false;

        /// <summary>
        /// Whether this material configures a blend mode
        /// </summary>
        public bool HasBlendMode { get; set; } = false;

        /// <summary>
        /// Whether this material configures channels
        /// </summary>
        public bool HasChanCtrl { get; set; } = false;

        /// <summary>
        /// Whether this material has a color
        /// </summary>
        public bool HasMatColor { get; set; } = false;

        /// <summary>
        /// Deserializes the contents of this object from a file
        /// </summary>
        /// <param name="reader">Binary stream to the file</param>
        public void Read(ReadStream reader)
        {
            uint packed = reader.ReadU32();

            TexMapNum = (byte)(packed >> 0 & 0b1111);
            TexSrtNum = (byte)(packed >> 4 & 0b1111);
            TexCoordGenNum = (byte)(packed >> 8 & 0b1111);
            HasTevSwapTable = (packed >> 12 & 0b1) != 0;
            IndTexSrtNum = (byte)(packed >> 13 & 0b11);
            IndStageNum = (byte)(packed >> 15 & 0b111);
            TevStageNum = (byte)(packed >> 18 & 0b11111);
            HasAlphaCompare = (packed >> 23 & 0b1) != 0;
            HasBlendMode = (packed >> 24 & 0b1) != 0;
            HasChanCtrl = (packed >> 25 & 0b1) != 0;
            HasMatColor = (packed >> 27 & 0b1) != 0;

            Validate();
        }

        /// <summary>
        /// Serializes the contents of this object to a file
        /// </summary>
        /// <param name="writer">Binary stream to the file</param>
        public void Write(WriteStream writer)
        {
            Validate();

            uint packed = 0;

            packed |= (uint)((TexMapNum & 0b1111) << 0);
            packed |= (uint)((TexSrtNum & 0b1111) << 4);
            packed |= (uint)((TexCoordGenNum & 0b1111) << 8);
            packed |= (uint)((HasTevSwapTable ? 1 : 0) << 12);
            packed |= (uint)((IndTexSrtNum & 0b11) << 13);
            packed |= (uint)((IndStageNum & 0b111) << 15);
            packed |= (uint)((TevStageNum & 0b11111) << 18);
            packed |= (uint)((HasAlphaCompare ? 1 : 0) << 23);
            packed |= (uint)((HasBlendMode ? 1 : 0) << 24);
            packed |= (uint)((HasChanCtrl ? 1 : 0) << 25);
            packed |= (uint)((HasMatColor ? 1 : 0) << 27);

            writer.WriteU32(packed);
        }

        /// <summary>
        /// Validates that all resource counts are within the expected range
        /// </summary>
        /// <exception cref="FileBrokenException">Resource configuration is invalid</exception>
        private void Validate()
        {
            if (TexMapNum > (byte)GXTexMapID.GX_MAX_TEXMAP)
            {
                throw new FileBrokenException("Too many texture maps");
            }

            if (TexSrtNum > LayoutDefine.MAX_TEX_SRT)
            {
                throw new FileBrokenException(
                    "Too many texture S/R/T transformations");
            }

            if (TexCoordGenNum > (byte)GXTexCoordID.GX_MAX_TEXCOORD)
            {
                throw new FileBrokenException(
                    "Too many texture coordinate generators");
            }

            if (IndTexSrtNum > LayoutDefine.MAX_IND_SRT)
            {
                throw new FileBrokenException(
                    "Too many indirect texture S/R/T transformations");
            }

            if (IndStageNum > (byte)GXIndTexStageID.GX_MAX_INDTEXSTAGE)
            {
                throw new FileBrokenException("Too many indirect stages");
            }

            if (TevStageNum > (byte)GXTevStageID.GX_MAX_TEVSTAGE)
            {
                throw new FileBrokenException("Too many TEV stages");
            }
        }
    }
}
