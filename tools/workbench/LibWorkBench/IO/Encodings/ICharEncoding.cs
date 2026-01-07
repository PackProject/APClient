using LibWorkBench.IO.Sources;
using LibWorkBench.Utility;

namespace LibWorkBench.IO.Encodings
{
    /// <summary>
    /// Interface for stream character encoding types
    /// </summary>
    public interface ICharEncoding
    {
        /// <summary>
        /// Reads an ASCII string value from the data source, represented in the specified endianness
        /// </summary>
        /// <param name="source">Stream data source</param>
        /// <param name="endian">Stream endianness</param>
        /// <param name="maxlen">Maximum string length</param>
        /// <param name="exact">Whether to read exactly `maxlen` bytes</param>
        /// <returns>String value</returns>
        public abstract string ReadString(IDataSource source,
                                          EndianUtil.Type endian, int maxlen,
                                          bool exact);

        /// <summary>
        /// Writes an ASCII string value to the data source, represented in the specified endianness
        /// </summary>
        /// <param name="source">Stream data source</param>
        /// <param name="endian">Stream endianness</param>
        /// <param name="value">String value</param>
        /// <param name="maxlen">Maximum string length</param>
        /// <param name="terminate">Whether to null-terminate the string</param>
        /// <param name="exact">Whether to write exactly `maxlen` bytes</param>
        public abstract void WriteString(IDataSource source,
                                         EndianUtil.Type endian, string value,
                                         int maxlen, bool terminate,
                                         bool exact);

        /// <summary>
        /// Reads a UTF-16 string value from the data source, represented in the specified endianness
        /// </summary>
        /// <param name="source">Stream data source</param>
        /// <param name="endian">Stream endianness</param>
        /// <param name="maxlen">Maximum string length</param>
        /// <param name="exact">Whether to read exactly `maxlen` bytes</param>
        /// <returns>String value</returns>
        public abstract string ReadWideString(IDataSource source,
                                              EndianUtil.Type endian,
                                              int maxlen, bool exact);

        /// <summary>
        /// Writes a UTF-16 string value to the data source, represented in the specified endianness
        /// </summary>
        /// <param name="source">Stream data source</param>
        /// <param name="endian">Stream endianness</param>
        /// <param name="value">String value</param>
        /// <param name="maxlen">Maximum string length</param>
        /// <param name="terminate">Whether to null-terminate the string</param>
        /// <param name="exact">Whether to write exactly `maxlen` bytes</param>
        public abstract void WriteWideString(IDataSource source,
                                             EndianUtil.Type endian,
                                             string value, int maxlen,
                                             bool terminate, bool exact);

        /// <summary>
        /// Reads a Shift-JIS string value from the data source, represented in the specified endianness
        /// </summary>
        /// <param name="source">Stream data source</param>
        /// <param name="endian">Stream endianness</param>
        /// <param name="maxlen">Maximum string length</param>
        /// <param name="exact">Whether to read exactly `maxlen` bytes</param>
        /// <returns>String value</returns>
        public abstract string ReadSjisString(IDataSource source,
                                              EndianUtil.Type endian,
                                              int maxlen, bool exact);

        /// <summary>
        /// Writes a Shift-JIS string value to the data source, represented in the specified endianness
        /// </summary>
        /// <param name="source">Stream data source</param>
        /// <param name="endian">Stream endianness</param>
        /// <param name="value">String value</param>
        /// <param name="maxlen">Maximum string length</param>
        /// <param name="terminate">Whether to null-terminate the string</param>
        /// <param name="exact">Whether to write exactly `maxlen` bytes</param>
        public abstract void WriteSjisString(IDataSource source,
                                             EndianUtil.Type endian,
                                             string value, int maxlen,
                                             bool terminate, bool exact);
    }
}
