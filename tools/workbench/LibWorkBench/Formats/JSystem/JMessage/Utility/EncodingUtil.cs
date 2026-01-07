using LibWorkBench.Exceptions;
using LibWorkBench.IO.Streams;
using LibWorkBench.Utility;
using System.Text;
using LibWorkBench.Formats.JSystem.JMessage.MsgRes.Types;

namespace LibWorkBench.Formats.JSystem.JMessage.Utility
{
    /// <summary>
    /// Text encoding utilities
    /// </summary>
    public static class EncodingUtil
    {
        /// <summary>
        /// Reads a single character from a stream in the specified encoding
        /// </summary>
        /// <param name="reader">Input stream</param>
        /// <param name="encoding">Text encoding</param>
        /// <returns>32-bit character code</returns>
        /// <exception cref="OperationException">Invalid text encoding was provided</exception>
        public static uint ReadChar(ReadStream reader, TextEncoding encoding)
        {
            switch (encoding)
            {
                case TextEncoding.CP1252:
                case TextEncoding.UTF8:
                    return reader.ReadU8();

                case TextEncoding.UTF16:
                case TextEncoding.SJIS:
                    return reader.ReadU16();

                default:
                    throw new OperationException("Invalid TextEncoding");
            }
        }

        /// <summary>
        /// Writes a single character to a stream in the specified encoding
        /// </summary>
        /// <param name="writer">Output stream</param>
        /// <param name="encoding">Text encoding</param>
        /// <param name="value">32-bit character code</param>
        /// <exception cref="OperationException">Invalid text encoding was provided</exception>
        public static void WriteChar(WriteStream writer, TextEncoding encoding,
                                     uint value)
        {
            byte oneByte = (byte)value;
            ushort twoByte = (ushort)value;

            switch (encoding)
            {
                case TextEncoding.CP1252:
                case TextEncoding.UTF8:
                    writer.WriteU8(oneByte);
                    break;

                case TextEncoding.UTF16:
                case TextEncoding.SJIS:
                    writer.WriteU16(twoByte);
                    break;

                default:
                    throw new OperationException("Invalid TextEncoding");
            }
        }

        /// <summary>
        /// Decodes a character code into its string representation
        /// </summary>
        /// <param name="encoding">Text encoding</param>
        /// <param name="endian">Endianness</param>
        /// <param name="value">32-bit character code</param>
        /// <returns>String representation of the character code</returns>
        /// <exception cref="OperationException">Invalid text encoding was provided</exception>
        public static string DecodeChar(TextEncoding encoding,
                                        EndianUtil.Type endian, uint value)
        {
            byte oneByte = (byte)value;
            ushort twoByte = (ushort)value;

            switch (encoding)
            {
                case TextEncoding.CP1252:
                    return Encoding.ASCII.GetString([oneByte]);

                case TextEncoding.UTF8:
                    return Encoding.UTF8.GetString([oneByte]);

                case TextEncoding.UTF16:
                    return Encoding.Unicode.GetString(
                        BitConverter.GetBytes(twoByte));

                case TextEncoding.SJIS:
                    throw new NotImplementedException("Not yet implemented");

                default:
                    throw new OperationException("Invalid TextEncoding");
            }
        }

        /// <summary>
        /// Reads a string from the stream, using the specified text encoding
        /// </summary>
        /// <param name="reader">Input stream</param>
        /// <param name="encoding">Message text encoding type</param>
        /// <param name="maxlen">Maximum string length</param>
        /// <returns>String value</returns>
        /// <exception cref="OperationException">Text encoding type is invalid</exception>
        public static string ReadString(ReadStream reader,
                                        TextEncoding encoding,
                                        int maxlen = int.MaxValue)
        {
            switch (encoding)
            {
                // TODO(kiwi) Are these safe to merge?
                case TextEncoding.CP1252:
                case TextEncoding.UTF8:
                    return reader.ReadString(maxlen);

                case TextEncoding.UTF16:
                    return reader.ReadWideString(maxlen);

                case TextEncoding.SJIS:
                    return reader.ReadWideString(maxlen);

                default:
                    throw new OperationException("Invalid TextEncoding");
            }
        }

        /// <summary>
        /// Writes a string to the stream, using the specified text encoding
        /// </summary>
        /// <param name="writer">Output stream</param>
        /// <param name="encoding">Message text encoding type</param>
        /// <param name="text">Message text string</param>
        /// <param name="maxlen">Maximum string length</param>
        /// <param name="terminate">Whether to null-terminate the string (binary modes only)</param>
        /// <exception cref="OperationException">Text encoding type is invalid</exception>
        public static void WriteString(WriteStream writer,
                                       TextEncoding encoding, string text,
                                       int maxlen = int.MaxValue,
                                       bool terminate = true)
        {
            switch (encoding)
            {
                // TODO(kiwi) Are these safe to merge?
                case TextEncoding.CP1252:
                case TextEncoding.UTF8:
                    writer.WriteString(text, maxlen, terminate);
                    break;

                case TextEncoding.UTF16:
                    writer.WriteWideString(text, maxlen, terminate);
                    break;

                case TextEncoding.SJIS:
                    writer.WriteSjisString(text, maxlen, terminate);
                    break;

                default:
                    throw new OperationException("Invalid TextEncoding");
            }
        }

        /// <summary>
        /// Gets the byte-size of a single character in the specified text encoding
        /// </summary>
        /// <param name="encoding">Text encoding</param>
        /// <returns>Number of bytes needed to represent a single character</returns>
        /// <exception cref="OperationException">Invalid text encoding was provided</exception>
        public static uint GetCharSize(TextEncoding encoding)
        {
            switch (encoding)
            {
                case TextEncoding.CP1252:
                case TextEncoding.UTF8:
                    return 1;

                case TextEncoding.UTF16:
                case TextEncoding.SJIS:
                    return 2;

                default:
                    throw new OperationException("Invalid TextEncoding");
            }
        }
    }
}
