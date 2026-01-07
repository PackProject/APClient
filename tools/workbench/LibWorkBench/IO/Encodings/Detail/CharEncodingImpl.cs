using LibWorkBench.IO.Sources;
using System.Text;

namespace LibWorkBench.IO.Encodings.Detail
{
    /// <summary>
    /// Base class for stream character encodings (internal implementation)
    /// </summary>
    public class CharEncodingImpl
    {
        /// <summary>
        /// Reads a string value from the data source, represented in the specified endianness
        /// </summary>
        /// <param name="source">Stream data source</param>
        /// <param name="encoding">Character encoding</param>
        /// <param name="maxlen">Maximum string length</param>
        /// <param name="terminate">Whether to expect a null-terminated string</param>
        /// <param name="exact">Whether to read exactly `maxlen` bytes</param>
        /// <returns>String value</returns>
        protected static string ReadStringImpl(IDataSource source,
                                               Encoding encoding, int maxlen,
                                               bool terminate, bool exact)
        {
            StringBuilder builder = new StringBuilder();
            ulong stride = (ulong)(encoding.IsSingleByte ? 1 : 2);

            while (!source.EOF && builder.Length < maxlen)
            {
                byte[] data = source.Read(sizeof(byte) * stride);

                // Null-terminator
                if (terminate && data.All(c => c == '\0'))
                {
                    break;
                }

                // Newline
                if (!terminate && (
                    (stride == 1 && data[0] == '\n') ||
                    (stride == 2 && data[0] == '\r' && data[1] == '\n')
                ))
                {
                    break;
                }

                builder.Append(encoding.GetChars(data));
            }

            // Skip to the end of fixed-size buffers
            if (exact && builder.Length < maxlen)
            {
                source.Seek((maxlen - (builder.Length + 1)) * (int)stride,
                            SeekOrigin.Current);
            }

            return builder.ToString();
        }

        /// <summary>
        /// Writes a string value to the data source, represented in the specified endianness
        /// </summary>
        /// <param name="source">Stream data source</param>
        /// <param name="encoding">Character encoding</param>
        /// <param name="value">String value</param>
        /// <param name="maxlen">Maximum string length</param>
        /// <param name="terminate">Whether to null-terminate the string</param>
        /// <param name="exact">Whether to write exactly `maxlen` bytes</param>
        protected static void WriteStringImpl(IDataSource source,
                                              Encoding encoding, string value,
                                              int maxlen, bool terminate,
                                              bool exact)
        {
            ulong stride = (ulong)(encoding.IsSingleByte ? 1 : 2);

            byte[] data = encoding.GetBytes(value);
            source.Write(data);

            // Determine padding size
            ulong fillNum = 0;
            if (value.Length < maxlen)
            {
                // Null terminator (if there is room)
                if (terminate)
                {
                    fillNum = 1;
                }
                // Fill fixed-size buffers
                else if (exact)
                {
                    fillNum = (ulong)(maxlen - value.Length);
                }
            }

            for (ulong i = 0; i < fillNum * stride; i++)
            {
                source.Write([0x00]);
            }
        }
    }
}
