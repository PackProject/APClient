using LibWorkBench.IO.Encodings;
using LibWorkBench.Utility;

namespace LibWorkBench.IO.Streams
{
    /// <summary>
    /// Binary file stream with read+write access
    /// </summary>
    public class BinaryFileWriter : FileWriter
    {
        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="path">File path to open</param>
        /// <param name="endian">Stream endianness (byte-order)</param>
        public BinaryFileWriter(string path, EndianUtil.Type endian)
            : base(path,
                   new BinaryPrimEncoding(),
                   new BinaryCharEncoding(),
                   endian)
        {
        }
    }
}
