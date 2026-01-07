using LibWorkBench.IO.Encodings;
using LibWorkBench.IO.Sources;
using LibWorkBench.Utility;

namespace LibWorkBench.IO.Streams
{
    /// <summary>
    /// File stream with read+write access
    /// </summary>
    public class FileWriter : WriteStream
    {
        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="path">File path to open</param>
        /// <param name="primEncoding">Stream primitive format</param>
        /// <param name="charEncoding">Stream character format</param>
        /// <param name="endian">Stream endianness (byte-order)</param>
        public FileWriter(string path, IPrimEncoding primEncoding,
                          ICharEncoding charEncoding, EndianUtil.Type endian)
            : base(new FileDataSource(path, writable: true),
                   primEncoding,
                   charEncoding,
                   endian)
        {
        }
    }
}
