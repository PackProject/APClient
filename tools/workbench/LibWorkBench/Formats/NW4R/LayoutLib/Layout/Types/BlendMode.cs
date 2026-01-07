using LibWorkBench.Core;
using LibWorkBench.IO.Streams;
using LibWorkBench.Formats.Revolution.GX.Types;

namespace LibWorkBench.Formats.NW4R.LayoutLib.Layout.Types
{
    /// <summary>
    /// Blend mode configuration
    /// </summary>
    public sealed class BlendMode : IUseBinary
    {
        /// <summary>
        /// Blend type
        /// </summary>
        public GXBlendMode Mode { get; set; } = GXBlendMode.GX_BM_BLEND;

        /// <summary>
        /// Source blend factor
        /// </summary>
        public GXBlendFactor SrcFactor { get; set; }
            = GXBlendFactor.GX_BL_SRCALPHA;

        /// <summary>
        /// Destination blend factor
        /// </summary>
        public GXBlendFactor DstFactor { get; set; }
            = GXBlendFactor.GX_BL_INVSRCALPHA;

        /// <summary>
        /// Logic operation for blending
        /// </summary>
        public GXLogicOp Operation { get; set; } = GXLogicOp.GX_LO_SET;

        /// <summary>
        /// Deserializes the contents of this object from a file
        /// </summary>
        /// <param name="reader">Binary stream to the file</param>
        public void Read(ReadStream reader)
        {
            Mode = (GXBlendMode)reader.ReadU8();
            SrcFactor = (GXBlendFactor)reader.ReadU8();
            DstFactor = (GXBlendFactor)reader.ReadU8();
            Operation = (GXLogicOp)reader.ReadU8();
        }

        /// <summary>
        /// Serializes the contents of this object to a file
        /// </summary>
        /// <param name="writer">Binary stream to the file</param>
        public void Write(WriteStream writer)
        {
            writer.WriteU8((byte)Mode);
            writer.WriteU8((byte)SrcFactor);
            writer.WriteU8((byte)DstFactor);
            writer.WriteU8((byte)Operation);
        }
    }
}
