using LibWorkBench.IO.Encodings;
using LibWorkBench.IO.Sources;
using LibWorkBench.Utility;

namespace LibWorkBench.IO.Streams
{
    /// <summary>
    /// File stream with read access
    /// </summary>
    public class FileReader : ReadStream
    {
        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="path">File path to open</param>
        /// <param name="primEncoding">Stream primitive format</param>
        /// <param name="charEncoding">Stream character format</param>
        /// <param name="endian">Stream endianness (byte-order)</param>
        public FileReader(string path, IPrimEncoding primEncoding,
                          ICharEncoding charEncoding, EndianUtil.Type endian)
            : base(new FileDataSource(path, writable: false),
                   primEncoding,
                   charEncoding,
                   endian)
        {
        }
    }
}
