using LibWorkBench.IO.Encodings;
using LibWorkBench.IO.Sources;
using LibWorkBench.Utility;

namespace LibWorkBench.IO.Streams
{
    /// <summary>
    /// Work/scratch memory stream with read+write access
    /// </summary>
    public class WorkMemWriter : WriteStream
    {
        /// <summary>
        /// Accesses the work memory buffer
        /// </summary>
        public byte[] Buffer => ((WorkMemDataSource)Source).Buffer;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="charEncoding">Stream character format</param>
        /// <param name="endian">Stream endianness (byte-order)</param>
        public WorkMemWriter(ICharEncoding charEncoding,
                             EndianUtil.Type endian)
            : base(new WorkMemDataSource(),
                   new BinaryPrimEncoding(),
                   charEncoding,
                   endian)
        {
        }
    }
}
