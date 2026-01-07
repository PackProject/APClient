using LibWorkBench.IO.Sources;
using LibWorkBench.Utility;

namespace LibWorkBench.IO.Encodings
{
    /// <summary>
    /// Null/dummy primitive encoding strategy
    /// </summary>
    public sealed class DummyPrimEncoding : IPrimEncoding
    {
        /// <summary>
        /// Reads an unsigned 8-bit value from the data source, represented in the specified endianness
        /// </summary>
        /// <param name="source">Stream data source</param>
        /// <param name="endian">Stream endianness</param>
        /// <returns>Unsigned 8-bit value</returns>
        public byte ReadU8(IDataSource source, EndianUtil.Type endian)
        {
            throw new NotSupportedException(
                "Please register a primitive encoding strategy");
        }

        /// <summary>
        /// Reads an unsigned 16-bit value from the data source, represented in the specified endianness
        /// </summary>
        /// <param name="source">Stream data source</param>
        /// <param name="endian">Stream endianness</param>
        /// <returns>Unsigned 16-bit value</returns>
        public ushort ReadU16(IDataSource source, EndianUtil.Type endian)
        {
            throw new NotSupportedException(
                "Please register a primitive encoding strategy");
        }

        /// <summary>
        /// Reads an unsigned 32-bit value from the data source, represented in the specified endianness
        /// </summary>
        /// <param name="source">Stream data source</param>
        /// <param name="endian">Stream endianness</param>
        /// <returns>Unsigned 32-bit value</returns>
        public uint ReadU32(IDataSource source, EndianUtil.Type endian)
        {
            throw new NotSupportedException(
                "Please register a primitive encoding strategy");
        }

        /// <summary>
        /// Reads an unsigned 64-bit value from the data source, represented in the specified endianness
        /// </summary>
        /// <param name="source">Stream data source</param>
        /// <param name="endian">Stream endianness</param>
        /// <returns>Unsigned 64-bit value</returns>
        public ulong ReadU64(IDataSource source, EndianUtil.Type endian)
        {
            throw new NotSupportedException(
                "Please register a primitive encoding strategy");
        }

        /// <summary>
        /// Reads a signed 8-bit value from the data source, represented in the specified endianness
        /// </summary>
        /// <param name="source">Stream data source</param>
        /// <param name="endian">Stream endianness</param>
        /// <returns>Signed 8-bit value</returns>
        public sbyte ReadS8(IDataSource source, EndianUtil.Type endian)
        {
            throw new NotSupportedException(
                "Please register a primitive encoding strategy");
        }

        /// <summary>
        /// Reads a signed 16-bit value from the data source, represented in the specified endianness
        /// </summary>
        /// <param name="source">Stream data source</param>
        /// <param name="endian">Stream endianness</param>
        /// <returns>Signed 16-bit value</returns>
        public short ReadS16(IDataSource source, EndianUtil.Type endian)
        {
            throw new NotSupportedException(
                "Please register a primitive encoding strategy");
        }

        /// <summary>
        /// Reads a signed 32-bit value from the data source, represented in the specified endianness
        /// </summary>
        /// <param name="source">Stream data source</param>
        /// <param name="endian">Stream endianness</param>
        /// <returns>Signed 32-bit value</returns>
        public int ReadS32(IDataSource source, EndianUtil.Type endian)
        {
            throw new NotSupportedException(
                "Please register a primitive encoding strategy");
        }

        /// <summary>
        /// Reads a signed 64-bit value from the data source, represented in the specified endianness
        /// </summary>
        /// <param name="source">Stream data source</param>
        /// <param name="endian">Stream endianness</param>
        /// <returns>Signed 64-bit value</returns>
        public long ReadS64(IDataSource source, EndianUtil.Type endian)
        {
            throw new NotSupportedException(
                "Please register a primitive encoding strategy");
        }

        /// <summary>
        /// Reads a single-precision floating point value from the data source, represented in the specified endianness
        /// </summary>
        /// <param name="source">Stream data source</param>
        /// <param name="endian">Stream endianness</param>
        /// <returns>Single-precision floating point value</returns>
        public float ReadF32(IDataSource source, EndianUtil.Type endian)
        {
            throw new NotSupportedException(
                "Please register a primitive encoding strategy");
        }

        /// <summary>
        /// Reads a double-precision floating point value from the data source, represented in the specified endianness
        /// </summary>
        /// <param name="source">Stream data source</param>
        /// <param name="endian">Stream endianness</param>
        /// <returns>Double-precision floating point value</returns>
        public double ReadF64(IDataSource source, EndianUtil.Type endian)
        {
            throw new NotSupportedException(
                "Please register a primitive encoding strategy");
        }

        /// <summary>
        /// Writes an unsigned 8-bit value to the data source, represented in the specified endianness
        /// </summary>
        /// <param name="source">Stream data source</param>
        /// <param name="endian">Stream endianness</param>
        /// <param name="value">Unsigned 8-bit value</param>
        public void WriteU8(IDataSource source, EndianUtil.Type endian,
                            byte value)
        {
            throw new NotSupportedException(
                "Please register a primitive encoding strategy");
        }

        /// <summary>
        /// Writes an unsigned 16-bit value to the data source, represented in the specified endianness
        /// </summary>
        /// <param name="source">Stream data source</param>
        /// <param name="endian">Stream endianness</param>
        /// <param name="value">Unsigned 16-bit value</param>
        public void WriteU16(IDataSource source, EndianUtil.Type endian,
                             ushort value)
        {
            throw new NotSupportedException(
                "Please register a primitive encoding strategy");
        }

        /// <summary>
        /// Writes an unsigned 32-bit value to the data source, represented in the specified endianness
        /// </summary>
        /// <param name="source">Stream data source</param>
        /// <param name="endian">Stream endianness</param>
        /// <param name="value">Unsigned 32-bit value</param>
        public void WriteU32(IDataSource source, EndianUtil.Type endian,
                             uint value)
        {
            throw new NotSupportedException(
                "Please register a primitive encoding strategy");
        }

        /// <summary>
        /// Writes an unsigned 64-bit value to the data source, represented in the specified endianness
        /// </summary>
        /// <param name="source">Stream data source</param>
        /// <param name="endian">Stream endianness</param>
        /// <param name="value">Unsigned 64-bit value</param>
        public void WriteU64(IDataSource source, EndianUtil.Type endian,
                             ulong value)
        {
            throw new NotSupportedException(
                "Please register a primitive encoding strategy");
        }

        /// <summary>
        /// Writes a signed 8-bit value to the data source, represented in the specified endianness
        /// </summary>
        /// <param name="source">Stream data source</param>
        /// <param name="endian">Stream endianness</param>
        /// <param name="value">Signed 8-bit value</param>
        public void WriteS8(IDataSource source, EndianUtil.Type endian,
                            sbyte value)
        {
            throw new NotSupportedException(
                "Please register a primitive encoding strategy");
        }

        /// <summary>
        /// Writes a signed 16-bit value to the data source, represented in the specified endianness
        /// </summary>
        /// <param name="source">Stream data source</param>
        /// <param name="endian">Stream endianness</param>
        /// <param name="value">Signed 16-bit value</param>
        public void WriteS16(IDataSource source, EndianUtil.Type endian,
                             short value)
        {
            throw new NotSupportedException(
                "Please register a primitive encoding strategy");
        }

        /// <summary>
        /// Writes a signed 32-bit value to the data source, represented in the specified endianness
        /// </summary>
        /// <param name="source">Stream data source</param>
        /// <param name="endian">Stream endianness</param>
        /// <param name="value">Signed 32-bit value</param>
        public void WriteS32(IDataSource source, EndianUtil.Type endian,
                             int value)
        {
            throw new NotSupportedException(
                "Please register a primitive encoding strategy");
        }

        /// <summary>
        /// Writes a signed 64-bit value to the data source, represented in the specified endianness
        /// </summary>
        /// <param name="source">Stream data source</param>
        /// <param name="endian">Stream endianness</param>
        /// <param name="value">Signed 64-bit value</param>
        public void WriteS64(IDataSource source, EndianUtil.Type endian,
                             long value)
        {
            throw new NotSupportedException(
                "Please register a primitive encoding strategy");
        }

        /// <summary>
        /// Writes a single-precision floating point value to the data source, represented in the specified endianness
        /// </summary>
        /// <param name="source">Stream data source</param>
        /// <param name="endian">Stream endianness</param>
        /// <param name="value">Single-precision floating point value</param>
        public void WriteF32(IDataSource source, EndianUtil.Type endian,
                             float value)
        {
            throw new NotSupportedException(
                "Please register a primitive encoding strategy");
        }

        /// <summary>
        /// Writes a double-precision floating point value to the data source, represented in the specified endianness
        /// </summary>
        /// <param name="source">Stream data source</param>
        /// <param name="endian">Stream endianness</param>
        /// <param name="value">Double-precision floating point value</param>
        public void WriteF64(IDataSource source, EndianUtil.Type endian,
                             double value)
        {
            throw new NotSupportedException(
                "Please register a primitive encoding strategy");
        }
    }
}
