using LibWorkBench.IO.Sources;
using LibWorkBench.Utility;

namespace LibWorkBench.IO.Encodings
{
    /// <summary>
    /// Null/dummy character encoding strategy
    /// </summary>
    public sealed class DummyCharEncoding : ICharEncoding
    {
        /// <summary>
        /// Reads a UTF-8 string value from the data source, represented in the specified endianness
        /// </summary>
        /// <param name="source">Stream data source</param>
        /// <param name="endian">Stream endianness</param>
        /// <param name="maxlen">Maximum string length</param>
        /// <param name="exact">Whether to read exactly `maxlen` bytes</param>
        /// <returns>String value</returns>
        public string ReadString(IDataSource source, EndianUtil.Type endian,
                                 int maxlen, bool exact)
        {
            throw new NotSupportedException(
                "Please register a character encoding strategy");
        }

        /// <summary>
        /// Writes a UTF-8 string value to the data source, represented in the specified endianness
        /// </summary>
        /// <param name="source">Stream data source</param>
        /// <param name="endian">Stream endianness</param>
        /// <param name="value">String value</param>
        /// <param name="maxlen">Maximum string length</param>
        /// <param name="terminate">Whether to null-terminate the string</param>
        /// <param name="exact">Whether to write exactly `maxlen` bytes</param>
        public void WriteString(IDataSource source, EndianUtil.Type endian,
                                string value, int maxlen, bool terminate,
                                bool exact)
        {
            throw new NotSupportedException(
                "Please register a character encoding strategy");
        }

        /// <summary>
        /// Reads a UTF-16 string value from the data source, represented in the specified endianness
        /// </summary>
        /// <param name="source">Stream data source</param>
        /// <param name="endian">Stream endianness</param>
        /// <param name="maxlen">Maximum string length</param>
        /// <param name="exact">Whether to read exactly `maxlen` bytes</param>
        /// <returns>String value</returns>
        public string ReadWideString(IDataSource source,
                                     EndianUtil.Type endian, int maxlen,
                                     bool exact)
        {
            throw new NotSupportedException(
                "Please register a character encoding strategy");
        }

        /// <summary>
        /// Writes a UTF-16 string value to the data source, represented in the specified endianness
        /// </summary>
        /// <param name="source">Stream data source</param>
        /// <param name="endian">Stream endianness</param>
        /// <param name="value">String value</param>
        /// <param name="maxlen">Maximum string length</param>
        /// <param name="terminate">Whether to null-terminate the string</param>
        /// <param name="exact">Whether to write exactly `maxlen` bytes</param>
        public void WriteWideString(IDataSource source, EndianUtil.Type endian,
                                    string value, int maxlen, bool terminate,
                                    bool exact)
        {
            throw new NotSupportedException(
                "Please register a character encoding strategy");
        }

        /// <summary>
        /// Reads a Shift-JIS string value from the data source, represented in the specified endianness
        /// </summary>
        /// <param name="source">Stream data source</param>
        /// <param name="endian">Stream endianness</param>
        /// <param name="maxlen">Maximum string length</param>
        /// <param name="exact">Whether to read exactly `maxlen` bytes</param>
        /// <returns>String value</returns>
        public string ReadSjisString(IDataSource source,
                                     EndianUtil.Type endian, int maxlen,
                                     bool exact)
        {
            throw new NotSupportedException(
                "Please register a character encoding strategy");
        }

        /// <summary>
        /// Writes a Shift-JIS string value to the data source, represented in the specified endianness
        /// </summary>
        /// <param name="source">Stream data source</param>
        /// <param name="endian">Stream endianness</param>
        /// <param name="value">String value</param>
        /// <param name="maxlen">Maximum string length</param>
        /// <param name="terminate">Whether to null-terminate the string</param>
        /// <param name="exact">Whether to write exactly `maxlen` bytes</param>
        public void WriteSjisString(IDataSource source, EndianUtil.Type endian,
                                    string value, int maxlen, bool terminate,
                                    bool exact)
        {
            throw new NotSupportedException(
                "Please register a character encoding strategy");
        }
    }
}
