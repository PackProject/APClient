using LibWorkBench.IO.Encodings.Detail;
using LibWorkBench.IO.Sources;
using LibWorkBench.Utility;
using System.Text;

namespace LibWorkBench.IO.Encodings
{
    /// <summary>
    /// Textual (non null-terminated) character encoding strategy
    /// </summary>
    public sealed class TextCharEncoding : CharEncodingImpl, ICharEncoding
    {
        /// <summary>
        /// Reads an ASCII string value from the data source, represented in the specified endianness
        /// </summary>
        /// <param name="source">Stream data source</param>
        /// <param name="endian">Stream endianness</param>
        /// <param name="maxlen">Maximum string length</param>
        /// <param name="exact">Whether to read exactly `maxlen` bytes</param>
        /// <returns>String value</returns>
        public string ReadString(IDataSource source, EndianUtil.Type endian,
                                 int maxlen, bool exact)
        {
            return ReadStringImpl(source, Encoding.ASCII, maxlen,
                                  terminate: false, exact: false);
        }

        /// <summary>
        /// Writes an ASCII string value to the data source, represented in the specified endianness
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
            WriteStringImpl(source, Encoding.ASCII, value, maxlen,
                            terminate: false, exact: false);
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
            return ReadStringImpl(
                source,
                endian == EndianUtil.Type.Little
                        ? Encoding.Unicode : Encoding.BigEndianUnicode,
                maxlen,
                terminate: false,
                exact: false
            );
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
            WriteStringImpl(
                source,
                endian == EndianUtil.Type.Little
                        ? Encoding.Unicode : Encoding.BigEndianUnicode,
                value,
                maxlen,
                terminate: false,
                exact: false
            );
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
            throw new NotImplementedException("Not yet implemented");
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
            throw new NotImplementedException("Not yet implemented");
        }
    }
}
