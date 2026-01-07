using LibWorkBench.Core;
using LibWorkBench.IO.Streams;

namespace LibWorkBench.Formats.NW4R.LayoutLib.Layout.Types
{
    /// <summary>
    /// TEV color channel swap table
    /// </summary>
    public sealed class TevSwapTable : IUseBinary
    {
        /// <summary>
        /// Swap select #0
        /// </summary>
        public TevSwapMode Swap0 { get; set; } = new();

        /// <summary>
        /// Swap select #1
        /// </summary>
        public TevSwapMode Swap1 { get; set; } = new();

        /// <summary>
        /// Swap select #2
        /// </summary>
        public TevSwapMode Swap2 { get; set; } = new();

        /// <summary>
        /// Swap select #3
        /// </summary>
        public TevSwapMode Swap3 { get; set; } = new();

        /// <summary>
        /// Deserializes the contents of this object from a file
        /// </summary>
        /// <param name="reader">Binary stream to the file</param>
        public void Read(ReadStream reader)
        {
            Swap0.Read(reader);
            Swap1.Read(reader);
            Swap2.Read(reader);
            Swap3.Read(reader);
        }

        /// <summary>
        /// Serializes the contents of this object to a file
        /// </summary>
        /// <param name="writer">Binary stream to the file</param>
        public void Write(WriteStream writer)
        {
            Swap0.Write(writer);
            Swap1.Write(writer);
            Swap2.Write(writer);
            Swap3.Write(writer);
        }
    }
}
