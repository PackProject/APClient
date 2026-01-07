using LibWorkBench.Core;
using LibWorkBench.IO.Streams;
using LibWorkBench.Formats.Revolution.GX.Types;

namespace LibWorkBench.Formats.NW4R.LayoutLib.Layout.Types
{
    /// <summary>
    /// TEV alpha combiner inputs
    /// </summary>
    public sealed class TevAlphaInput : IUseBinary
    {
        /// <summary>
        /// Component A in the output equation
        /// </summary>
        public GXTevAlphaArg A { get; set; } = GXTevAlphaArg.GX_CA_ZERO;

        /// <summary>
        /// Component B in the output equation
        /// </summary>
        public GXTevAlphaArg B { get; set; } = GXTevAlphaArg.GX_CA_ZERO;

        /// <summary>
        /// Component C in the output equation
        /// </summary>
        public GXTevAlphaArg C { get; set; } = GXTevAlphaArg.GX_CA_ZERO;

        /// <summary>
        /// Component D in the output equation
        /// </summary>
        public GXTevAlphaArg D { get; set; } = GXTevAlphaArg.GX_CA_ZERO;

        /// <summary>
        /// Operation in the output equation
        /// </summary>
        public GXTevOp Operation { get; set; } = GXTevOp.GX_TEV_ADD;

        /// <summary>
        /// Bias in the output equation
        /// </summary>
        public GXTevBias Bias { get; set; } = GXTevBias.GX_TB_ZERO;

        /// <summary>
        /// Scale in the output equation
        /// </summary>
        public GXTevScale Scale { get; set; } = GXTevScale.GX_CS_SCALE_1;

        /// <summary>
        /// Whether to clamp the output to the range [0, 1]
        /// </summary>
        public bool Clamp { get; set; } = true;

        /// <summary>
        /// TEV register in which to store the result
        /// </summary>
        public GXTevRegID Output { get; set; } = GXTevRegID.GX_TEVPREV;

        /// <summary>
        /// Constant alpha available to combiner arguments (GX_CA_KONST)
        /// </summary>
        public GXTevKAlphaSel Constant { get; set; }
            = GXTevKAlphaSel.GX_TEV_KASEL_K0_R;

        /// <summary>
        /// Deserializes the contents of this object from a file
        /// </summary>
        /// <param name="reader">Binary stream to the file</param>
        public void Read(ReadStream reader)
        {
            byte ab = reader.ReadU8();
            byte cd = reader.ReadU8();
            byte op = reader.ReadU8();
            byte cl = reader.ReadU8();

            A = (GXTevAlphaArg)(ab >> 0 & 0b1111);
            B = (GXTevAlphaArg)(ab >> 4 & 0b1111);
            C = (GXTevAlphaArg)(cd >> 0 & 0b1111);
            D = (GXTevAlphaArg)(cd >> 4 & 0b1111);

            Operation = (GXTevOp)(op >> 0 & 0b1111);
            Bias = (GXTevBias)(op >> 4 & 0b11);
            Scale = (GXTevScale)(op >> 6 & 0b11);

            Clamp = (cl >> 0 & 0b1) != 0;
            Output = (GXTevRegID)(cl >> 1 & 0b11);
            Constant = (GXTevKAlphaSel)(cl >> 3 & 0b11111);
        }

        /// <summary>
        /// Serializes the contents of this object to a file
        /// </summary>
        /// <param name="writer">Binary stream to the file</param>
        public void Write(WriteStream writer)
        {
            byte ab = 0;
            ab |= (byte)(((int)A & 0b1111) << 0);
            ab |= (byte)(((int)B & 0b1111) << 4);
            writer.WriteU8(ab);

            byte cd = 0;
            cd |= (byte)(((int)C & 0b1111) << 0);
            cd |= (byte)(((int)D & 0b1111) << 4);
            writer.WriteU8(cd);

            byte op = 0;
            op |= (byte)(((int)Operation & 0b1111) << 0);
            op |= (byte)(((int)Bias & 0b11) << 4);
            op |= (byte)(((int)Scale & 0b11) << 6);
            writer.WriteU8(op);

            byte cl = 0;
            cl |= (byte)((Clamp ? 1 : 0) << 0);
            cl |= (byte)(((int)Output & 0b11) << 1);
            cl |= (byte)(((int)Constant & 0b11111) << 3);
            writer.WriteU8(cl);
        }
    }
}
