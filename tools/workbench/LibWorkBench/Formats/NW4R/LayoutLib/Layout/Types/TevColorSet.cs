using LibWorkBench.Core;
using LibWorkBench.IO.Streams;
using LibWorkBench.Formats.Revolution.GX.Types;

namespace LibWorkBench.Formats.NW4R.LayoutLib.Layout.Types
{
    /// <summary>
    /// TEV color set
    /// </summary>
    public sealed class TevColorSet : IUseBinary
    {
        /// <summary>
        /// TEV color register 0 (GX_TEVREG0)
        /// </summary>
        public GXColorS10 Reg0 { get; set; } = new();

        /// <summary>
        /// TEV color register 1 (GX_TEVREG1)
        /// </summary>
        public GXColorS10 Reg1 { get; set; } = new();

        /// <summary>
        /// TEV color register 2 (GX_TEVREG2)
        /// </summary>
        public GXColorS10 Reg2 { get; set; } = new();

        /// <summary>
        /// Deserializes the contents of this object from a file
        /// </summary>
        /// <param name="reader">Binary stream to the file</param>
        public void Read(ReadStream reader)
        {
            Reg0.Read(reader);
            Reg1.Read(reader);
            Reg2.Read(reader);
        }

        /// <summary>
        /// Serializes the contents of this object to a file
        /// </summary>
        /// <param name="writer">Binary stream to the file</param>
        public void Write(WriteStream writer)
        {
            Reg0.Write(writer);
            Reg1.Write(writer);
            Reg2.Write(writer);
        }
    }
}
