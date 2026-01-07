using LibWorkBench.Core;
using LibWorkBench.IO.Streams;
using LibWorkBench.Formats.Revolution.GX.Types;

namespace LibWorkBench.Formats.NW4R.LayoutLib.Layout.Types
{
    /// <summary>
    /// Visibility test
    /// </summary>
    public sealed class AlphaCompare : IUseBinary
    {
        /// <summary>
        /// Compare operation #0
        /// </summary>
        public GXCompare Compare0 { get; set; } = GXCompare.GX_ALWAYS;

        /// <summary>
        /// Compare operand #0
        /// </summary>
        public byte Ref0 { get; set; } = 0;

        /// <summary>
        /// Compare operation #1
        /// </summary>
        public GXCompare Compare1 { get; set; } = GXCompare.GX_ALWAYS;

        /// <summary>
        /// Compare operand #1
        /// </summary>
        public byte Ref1 { get; set; } = 0;

        /// <summary>
        /// Logic operation between comparisons
        /// </summary>
        public GXAlphaOp Op { get; set; } = GXAlphaOp.GX_AOP_AND;

        /// <summary>
        /// Deserializes the contents of this object from a file
        /// </summary>
        /// <param name="reader">Binary stream to the file</param>
        public void Read(ReadStream reader)
        {
            byte compare01 = reader.ReadU8();
            Compare0 = (GXCompare)(compare01 >> 0 & 0b1111);
            Compare1 = (GXCompare)(compare01 >> 4 & 0b1111);

            Op = (GXAlphaOp)reader.ReadU8();
            Ref0 = reader.ReadU8();
            Ref1 = reader.ReadU8();
        }

        /// <summary>
        /// Serializes the contents of this object to a file
        /// </summary>
        /// <param name="writer">Binary stream to the file</param>
        public void Write(WriteStream writer)
        {
            byte compare01 = 0;
            compare01 |= (byte)(((int)Compare0 & 0b1111) << 0);
            compare01 |= (byte)(((int)Compare1 & 0b1111) << 4);
            writer.WriteU8(compare01);

            writer.WriteU8((byte)Op);
            writer.WriteU8(Ref0);
            writer.WriteU8(Ref1);
        }
    }
}
