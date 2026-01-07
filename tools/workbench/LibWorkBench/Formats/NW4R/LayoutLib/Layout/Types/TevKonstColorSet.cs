using LibWorkBench.Core;
using LibWorkBench.IO.Streams;
using LibWorkBench.Formats.Revolution.GX.Types;

namespace LibWorkBench.Formats.NW4R.LayoutLib.Layout.Types
{
    /// <summary>
    /// TEV constant color (KCOLOR) set
    /// </summary>
    public sealed class TevKonstColorSet : IUseBinary
    {
        /// <summary>
        /// TEV constant color register 0 (GX_KCOLOR0)
        /// </summary>
        public GXColor Color0 { get; set; } = new();

        /// <summary>
        /// TEV constant color register 1 (GX_KCOLOR1)
        /// </summary>
        public GXColor Color1 { get; set; } = new();

        /// <summary>
        /// TEV constant color register 2 (GX_KCOLOR2)
        /// </summary>
        public GXColor Color2 { get; set; } = new();

        /// <summary>
        /// TEV constant color register 3 (GX_KCOLOR3)
        /// </summary>
        public GXColor Color3 { get; set; } = new();

        /// <summary>
        /// Deserializes the contents of this object from a file
        /// </summary>
        /// <param name="reader">Binary stream to the file</param>
        public void Read(ReadStream reader)
        {
            Color0.Read(reader);
            Color1.Read(reader);
            Color2.Read(reader);
            Color3.Read(reader);
        }

        /// <summary>
        /// Serializes the contents of this object to a file
        /// </summary>
        /// <param name="writer">Binary stream to the file</param>
        public void Write(WriteStream writer)
        {
            Color0.Write(writer);
            Color1.Write(writer);
            Color2.Write(writer);
            Color3.Write(writer);
        }
    }
}
