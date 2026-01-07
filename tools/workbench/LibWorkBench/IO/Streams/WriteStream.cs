using LibWorkBench.IO.Encodings;
using LibWorkBench.IO.Sources;
using LibWorkBench.Utility;

namespace LibWorkBench.IO.Streams
{
    /// <summary>
    /// Base class for streams with read+write access
    /// </summary>
    public abstract class WriteStream : ReadStream
    {
        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="source">Stream data source</param>
        /// <param name="primEncoding">Stream primitive format</param>
        /// <param name="charEncoding">Stream character format</param>
        /// <param name="endian">Stream endianness (byte-order)</param>
        public WriteStream(IDataSource source, IPrimEncoding primEncoding,
                           ICharEncoding charEncoding, EndianUtil.Type endian)
            : base(source,
                   primEncoding,
                   charEncoding,
                   endian)
        {
        }

        /// <summary>
        /// Aligns the stream position to the specified byte-alignment
        /// </summary>
        /// <param name="alignment">Required byte-alignment</param>
        public new void Align(ulong alignment)
        {
            // Number of bytes required to reach alignment
            ulong misalign = (alignment - (Position % alignment)) % alignment;
            if (misalign == 0)
            {
                return;
            }

            if (EOF)
            {
                WritePadding(misalign);
            }
            else
            {
                Skip((long)misalign);
            }
        }

        /// <summary>
        /// Writes a specified block of data to the stream
        /// </summary>
        /// <param name="data">Data contents to write</param>
        /// <param name="size">Number of bytes to write (optional)</param>
        public void Write(byte[] data, ulong? size = null)
        {
            Source.Write(data, size);
        }

        /// <summary>
        /// Writes an unsigned 8-bit value to the stream
        /// </summary>
        /// <param name="value">Unsigned 8-bit value</param>
        public void WriteU8(byte value)
        {
            PrimEncoding.WriteU8(Source, Endian, value);
        }

        /// <summary>
        /// Writes an unsigned 16-bit value to the stream
        /// <param name="value">Unsigned 16-bit value</param>
        /// </summary>
        public void WriteU16(ushort value)
        {
            PrimEncoding.WriteU16(Source, Endian, value);
        }

        /// <summary>
        /// Writes an unsigned 32-bit value to the stream
        /// </summary>
        /// <param name="value">Unsigned 32-bit value</param>
        public void WriteU32(uint value)
        {
            PrimEncoding.WriteU32(Source, Endian, value);
        }

        /// <summary>
        /// Writes an unsigned 64-bit value to the stream
        /// </summary>
        /// <param name="value">Unsigned 64-bit value</param>
        public void WriteU64(ulong value)
        {
            PrimEncoding.WriteU64(Source, Endian, value);
        }

        /// <summary>
        /// Writes a signed 8-bit value to the stream
        /// </summary>
        /// <param name="value">Signed 8-bit value</param>
        public void WriteS8(sbyte value)
        {
            PrimEncoding.WriteS8(Source, Endian, value);
        }

        /// <summary>
        /// Writes a signed 16-bit value to the stream
        /// </summary>
        /// <param name="value">Signed 16-bit value</param>
        public void WriteS16(short value)
        {
            PrimEncoding.WriteS16(Source, Endian, value);
        }

        /// <summary>
        /// Writes a signed 32-bit value to the stream
        /// </summary>
        /// <param name="value">Signed 32-bit value</param>
        public void WriteS32(int value)
        {
            PrimEncoding.WriteS32(Source, Endian, value);
        }

        /// <summary>
        /// Writes a signed 64-bit value to the stream
        /// </summary>
        /// <param name="value">Signed 64-bit value</param>
        public void WriteS64(long value)
        {
            PrimEncoding.WriteS64(Source, Endian, value);
        }

        /// <summary>
        /// Writes a single-precision floating point value to the stream
        /// </summary>
        /// <param name="value">Single-precision floating point value</param>
        public void WriteF32(float value)
        {
            PrimEncoding.WriteF32(Source, Endian, value);
        }

        /// <summary>
        /// Writes a double-precision floating point value to the stream
        /// </summary>
        /// <param name="value">Double-precision floating point value</param>
        public void WriteF64(double value)
        {
            PrimEncoding.WriteF64(Source, Endian, value);
        }

        /// <summary>
        /// Writes a UTF-8 string value to the stream
        /// </summary>
        /// <param name="value">String value</param>
        /// <param name="maxlen">Maximum string length</param>
        /// <param name="terminate">Whether to null-terminate the string (binary modes only)</param>
        /// <param name="exact">Whether to write exactly `maxlen` bytes</param>
        public void WriteString(string value, int maxlen = int.MaxValue,
                                bool terminate = true, bool exact = false)
        {
            CharEncoding.WriteString(Source, Endian, value, maxlen, terminate,
                                     exact);
        }

        /// <summary>
        /// Writes a UTF-16 string value to the stream
        /// </summary>
        /// <param name="value">String value</param>
        /// <param name="maxlen">Maximum string length</param>
        /// <param name="terminate">Whether to null-terminate the string (binary modes only)</param>
        /// <param name="exact">Whether to write exactly `maxlen` bytes</param>
        public void WriteWideString(string value, int maxlen = int.MaxValue,
                                    bool terminate = true, bool exact = false)
        {
            CharEncoding.WriteWideString(Source, Endian, value, maxlen,
                                         terminate, exact);
        }

        /// <summary>
        /// Writes a Shift-JIS string value to the stream
        /// </summary>
        /// <param name="value">String value</param>
        /// <param name="maxlen">Maximum string length</param>
        /// <param name="terminate">Whether to null-terminate the string (binary modes only)</param>
        /// <param name="exact">Whether to write exactly `maxlen` bytes</param>
        public void WriteSjisString(string value, int maxlen = int.MaxValue,
                                    bool terminate = true, bool exact = false)
        {
            CharEncoding.WriteSjisString(Source, Endian, value, maxlen,
                                         terminate, exact);
        }

        /// <summary>
        /// Writes a boolean value to the stream
        /// </summary>
        /// <param name="value">Boolean value</param>
        public void WriteBool(bool value)
        {
            PrimEncoding.WriteU8(Source, Endian, (byte)(value ? 1 : 0));
        }

        /// <summary>
        /// Writes padding (0x00 bytes) to the stream
        /// </summary>
        /// <param name="length"></param>
        public void WritePadding(ulong length)
        {
            for (ulong i = 0; i < length; i++)
            {
                WriteU8(0x00);
            }
        }

        /// <summary>
        /// Writes debug fill data ("CAFEBABE" pattern) to the stream
        /// </summary>
        /// <param name="length">Number of bytes to fill</param>
        public void WriteDebugFill(ulong length)
        {
            byte[] fill = BitConverter.GetBytes(0xCAFEBABE);

            for (ulong i = 0; i < length; i++)
            {
                WriteU8(fill[i % (ulong)fill.Length]);
            }
        }
    }
}
