using LibWorkBench.IO.Sources;
using LibWorkBench.Utility;

namespace LibWorkBench.IO.Encodings
{
    /// <summary>
    /// Interface for stream primitive (numeric) encoding types
    /// </summary>
    public interface IPrimEncoding
    {
        /// <summary>
        /// Reads an unsigned 8-bit value from the data source, represented in the specified endianness
        /// </summary>
        /// <param name="source">Stream data source</param>
        /// <param name="endian">Stream endianness</param>
        /// <returns>Unsigned 8-bit value</returns>
        public abstract byte ReadU8(IDataSource source,
                                    EndianUtil.Type endian);

        /// <summary>
        /// Reads an unsigned 16-bit value from the data source, represented in the specified endianness
        /// </summary>
        /// <param name="source">Stream data source</param>
        /// <param name="endian">Stream endianness</param>
        /// <returns>Unsigned 16-bit value</returns>
        public abstract ushort ReadU16(IDataSource source,
                                       EndianUtil.Type endian);

        /// <summary>
        /// Reads an unsigned 32-bit value from the data source, represented in the specified endianness
        /// </summary>
        /// <param name="source">Stream data source</param>
        /// <param name="endian">Stream endianness</param>
        /// <returns>Unsigned 32-bit value</returns>
        public abstract uint ReadU32(IDataSource source,
                                     EndianUtil.Type endian);

        /// <summary>
        /// Reads an unsigned 64-bit value from the data source, represented in the specified endianness
        /// </summary>
        /// <param name="source">Stream data source</param>
        /// <param name="endian">Stream endianness</param>
        /// <returns>Unsigned 64-bit value</returns>
        public abstract ulong ReadU64(IDataSource source,
                                      EndianUtil.Type endian);

        /// <summary>
        /// Reads a signed 8-bit value from the data source, represented in the specified endianness
        /// </summary>
        /// <param name="source">Stream data source</param>
        /// <param name="endian">Stream endianness</param>
        /// <returns>Signed 8-bit value</returns>
        public abstract sbyte ReadS8(IDataSource source,
                                     EndianUtil.Type endian);

        /// <summary>
        /// Reads a signed 16-bit value from the data source, represented in the specified endianness
        /// </summary>
        /// <param name="source">Stream data source</param>
        /// <param name="endian">Stream endianness</param>
        /// <returns>Signed 16-bit value</returns>
        public abstract short ReadS16(IDataSource source,
                                      EndianUtil.Type endian);

        /// <summary>
        /// Reads a signed 32-bit value from the data source, represented in the specified endianness
        /// </summary>
        /// <param name="source">Stream data source</param>
        /// <param name="endian">Stream endianness</param>
        /// <returns>Signed 32-bit value</returns>
        public abstract int ReadS32(IDataSource source,
                                    EndianUtil.Type endian);

        /// <summary>
        /// Reads a signed 64-bit value from the data source, represented in the specified endianness
        /// </summary>
        /// <param name="source">Stream data source</param>
        /// <param name="endian">Stream endianness</param>
        /// <returns>Signed 64-bit value</returns>
        public abstract long ReadS64(IDataSource source,
                                     EndianUtil.Type endian);

        /// <summary>
        /// Reads a single-precision floating point value from the data source, represented in the specified endianness
        /// </summary>
        /// <param name="source">Stream data source</param>
        /// <param name="endian">Stream endianness</param>
        /// <returns>Single-precision floating point value</returns>
        public abstract float ReadF32(IDataSource source,
                                      EndianUtil.Type endian);

        /// <summary>
        /// Reads a double-precision floating point value from the data source, represented in the specified endianness
        /// </summary>
        /// <param name="source">Stream data source</param>
        /// <param name="endian">Stream endianness</param>
        /// <returns>Double-precision floating point value</returns>
        public abstract double ReadF64(IDataSource source,
                                       EndianUtil.Type endian);

        /// <summary>
        /// Writes an unsigned 8-bit value to the data source, represented in the specified endianness
        /// </summary>
        /// <param name="source">Stream data source</param>
        /// <param name="endian">Stream endianness</param>
        /// <param name="value">Unsigned 8-bit value</param>
        public abstract void WriteU8(IDataSource source,
                                     EndianUtil.Type endian, byte value);

        /// <summary>
        /// Writes an unsigned 16-bit value to the data source, represented in the specified endianness
        /// </summary>
        /// <param name="source">Stream data source</param>
        /// <param name="endian">Stream endianness</param>
        /// <param name="value">Unsigned 16-bit value</param>
        public abstract void WriteU16(IDataSource source,
                                      EndianUtil.Type endian, ushort value);

        /// <summary>
        /// Writes an unsigned 32-bit value to the data source, represented in the specified endianness
        /// </summary>
        /// <param name="source">Stream data source</param>
        /// <param name="endian">Stream endianness</param>
        /// <param name="value">Unsigned 32-bit value</param>
        public abstract void WriteU32(IDataSource source,
                                      EndianUtil.Type endian, uint value);

        /// <summary>
        /// Writes an unsigned 64-bit value to the data source, represented in the specified endianness
        /// </summary>
        /// <param name="source">Stream data source</param>
        /// <param name="endian">Stream endianness</param>
        /// <param name="value">Unsigned 64-bit value</param>
        public abstract void WriteU64(IDataSource source,
                                      EndianUtil.Type endian, ulong value);

        /// <summary>
        /// Writes a signed 8-bit value to the data source, represented in the specified endianness
        /// </summary>
        /// <param name="source">Stream data source</param>
        /// <param name="endian">Stream endianness</param>
        /// <param name="value">Signed 8-bit value</param>
        public abstract void WriteS8(IDataSource source,
                                     EndianUtil.Type endian, sbyte value);

        /// <summary>
        /// Writes a signed 16-bit value to the data source, represented in the specified endianness
        /// </summary>
        /// <param name="source">Stream data source</param>
        /// <param name="endian">Stream endianness</param>
        /// <param name="value">Signed 16-bit value</param>
        public abstract void WriteS16(IDataSource source,
                                      EndianUtil.Type endian, short value);

        /// <summary>
        /// Writes a signed 32-bit value to the data source, represented in the specified endianness
        /// </summary>
        /// <param name="source">Stream data source</param>
        /// <param name="endian">Stream endianness</param>
        /// <param name="value">Signed 32-bit value</param>
        public abstract void WriteS32(IDataSource source,
                                      EndianUtil.Type endian, int value);

        /// <summary>
        /// Writes a signed 64-bit value to the data source, represented in the specified endianness
        /// </summary>
        /// <param name="source">Stream data source</param>
        /// <param name="endian">Stream endianness</param>
        /// <param name="value">Signed 64-bit value</param>
        public abstract void WriteS64(IDataSource source,
                                      EndianUtil.Type endian, long value);

        /// <summary>
        /// Writes a single-precision floating point value to the data source, represented in the specified endianness
        /// </summary>
        /// <param name="source">Stream data source</param>
        /// <param name="endian">Stream endianness</param>
        /// <param name="value">Single-precision floating point value</param>
        public abstract void WriteF32(IDataSource source,
                                      EndianUtil.Type endian, float value);

        /// <summary>
        /// Writes a double-precision floating point value to the data source, represented in the specified endianness
        /// </summary>
        /// <param name="source">Stream data source</param>
        /// <param name="endian">Stream endianness</param>
        /// <param name="value">Double-precision floating point value</param>
        public abstract void WriteF64(IDataSource source,
                                      EndianUtil.Type endian, double value);
    }
}
