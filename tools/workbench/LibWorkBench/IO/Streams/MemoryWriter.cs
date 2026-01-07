using LibWorkBench.IO.Encodings;
using LibWorkBench.IO.Sources;
using LibWorkBench.Utility;

namespace LibWorkBench.IO.Streams
{
    /// <summary>
    /// Memory stream with read+write access
    /// </summary>
    public class MemoryWriter : WriteStream
    {
        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="buffer">Memory buffer to open</param>
        /// <param name="charEncoding">Stream character format</param>
        /// <param name="endian">Stream endianness (byte-order)</param>
        public MemoryWriter(byte[] buffer, ICharEncoding charEncoding,
                            EndianUtil.Type endian)
            : base(new MemoryDataSource(buffer, writable: false),
                   new BinaryPrimEncoding(),
                   charEncoding,
                   endian)
        {
        }
    }
}
