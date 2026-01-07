using LibWorkBench.IO.Encodings;
using LibWorkBench.IO.Sources;
using LibWorkBench.Utility;

namespace LibWorkBench.IO.Streams
{
    /// <summary>
    /// Base class for streams with read access
    /// </summary>
    public abstract class ReadStream : Stream
    {
        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="source">Stream data source</param>
        /// <param name="primEncoding">Stream primitive format</param>
        /// <param name="charEncoding">Stream character format</param>
        /// <param name="endian">Stream endianness (byte-order)</param>
        public ReadStream(IDataSource source, IPrimEncoding primEncoding,
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
        public void Align(ulong alignment)
        {
            // Number of bytes required to reach alignment
            ulong misalign = (alignment - (Position % alignment)) % alignment;
            if (misalign == 0)
            {
                return;
            }

            Skip((long)misalign);
        }

        /// <summary>
        /// Reads a specified amount of data from the data source
        /// </summary>
        /// <param name="size">Number of bytes to read</param>
        /// <returns>Data block as an array of bytes</returns>
        public byte[] Read(ulong size)
        {
            return Source.Read(size);
        }

        /// <summary>
        /// Reads an unsigned 8-bit value from the stream
        /// </summary>
        /// <returns>Unsigned 8-bit value</returns>
        public byte ReadU8()
        {
            return PrimEncoding.ReadU8(Source, Endian);
        }

        /// <summary>
        /// Reads an unsigned 16-bit value from the stream
        /// </summary>
        /// <returns>Unsigned 16-bit value</returns>
        public ushort ReadU16()
        {
            return PrimEncoding.ReadU16(Source, Endian);
        }

        /// <summary>
        /// Reads an unsigned 32-bit value from the stream
        /// </summary>
        /// <returns>Unsigned 32-bit value</returns>
        public uint ReadU32()
        {
            return PrimEncoding.ReadU32(Source, Endian);
        }

        /// <summary>
        /// Reads an unsigned 64-bit value from the stream
        /// </summary>
        /// <returns>Unsigned 64-bit value</returns>
        public ulong ReadU64()
        {
            return PrimEncoding.ReadU64(Source, Endian);
        }

        /// <summary>
        /// Reads a signed 8-bit value from the stream
        /// </summary>
        /// <returns>Signed 8-bit value</returns>
        public sbyte ReadS8()
        {
            return PrimEncoding.ReadS8(Source, Endian);
        }

        /// <summary>
        /// Reads a signed 16-bit value from the stream
        /// </summary>
        /// <returns>Signed 16-bit value</returns>
        public short ReadS16()
        {
            return PrimEncoding.ReadS16(Source, Endian);
        }

        /// <summary>
        /// Reads a signed 32-bit value from the stream
        /// </summary>
        /// <returns>Signed 32-bit value</returns>
        public int ReadS32()
        {
            return PrimEncoding.ReadS32(Source, Endian);
        }

        /// <summary>
        /// Reads a signed 64-bit value from the stream
        /// </summary>
        /// <returns>Signed 64-bit value</returns>
        public long ReadS64()
        {
            return PrimEncoding.ReadS64(Source, Endian);
        }

        /// <summary>
        /// Reads a single-precision floating point value from the stream
        /// </summary>
        /// <returns>Single-precision floating point value</returns>
        public float ReadF32()
        {
            return PrimEncoding.ReadF32(Source, Endian);
        }

        /// <summary>
        /// Reads a double-precision floating point value from the stream
        /// </summary>
        /// <returns>Double-precision floating point value</returns>
        public double ReadF64()
        {
            return PrimEncoding.ReadF64(Source, Endian);
        }

        /// <summary>
        /// Reads a UTF-8 string value from the stream
        /// </summary>
        /// <param name="maxlen">Maximum string length</param>
        /// <param name="exact">Whether to read exactly `maxlen` bytes</param>
        /// <returns>String value</returns>
        public string ReadString(int maxlen = int.MaxValue, bool exact = false)
        {
            return CharEncoding.ReadString(Source, Endian, maxlen, exact);
        }

        /// <summary>
        /// Reads a UTF-16 string value from the stream
        /// </summary>
        /// <param name="maxlen">Maximum string length</param>
        /// <param name="exact">Whether to read exactly `maxlen` bytes</param>
        /// <returns>String value</returns>
        public string ReadWideString(int maxlen = int.MaxValue,
                                     bool exact = false)
        {
            return CharEncoding.ReadWideString(Source, Endian, maxlen, exact);
        }

        /// <summary>
        /// Reads a Shift-JIS string value from the stream
        /// </summary>
        /// <param name="maxlen">Maximum string length</param>
        /// <param name="exact">Whether to read exactly `maxlen` bytes</param>
        /// <returns>String value</returns>
        public string ReadSjisString(int maxlen = int.MaxValue,
                                     bool exact = false)
        {
            return CharEncoding.ReadSjisString(Source, Endian, maxlen, exact);
        }

        /// <summary>
        /// Reads a boolean value from the stream
        /// </summary>
        /// <returns>Boolean value</returns>
        public bool ReadBool()
        {
            return ReadU8() != 0;
        }
    }
}
