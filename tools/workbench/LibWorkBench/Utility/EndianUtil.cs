using LibWorkBench.Exceptions;
using System.Buffers.Binary;

namespace LibWorkBench.Utility
{
    /// <summary>
    /// Endian conversion utilities
    /// </summary>
    public static class EndianUtil
    {
        /// <summary>
        /// Byteorder
        /// </summary>
        public enum Type
        {
            /// <summary>
            /// Little endian (least significant bits come first)
            /// </summary>
            Little,

            /// <summary>
            /// Big endian (most significant bits come first)
            /// </summary>
            Big
        };

        /// <summary>
        /// Gets the host system's endianness
        /// </summary>
        /// <returns>Type enum value</returns>
        public static Type GetHostEndian()
        {
            return BitConverter.IsLittleEndian ? Type.Little : Type.Big;
        }

        /// <summary>
        /// Converts the input value to little endian
        /// </summary>
        /// <typeparam name="T">Type of value (must be primitive type)</typeparam>
        /// <param name="value">Original value</param>
        /// <returns>Value represented in little endian</returns>
        public static T ToLittleEndian<T>(T value)
            where T : unmanaged
        {
            return GetHostEndian() == Type.Little ? value : Swap(value);
        }

        /// <summary>
        /// Converts the input value to big endian
        /// </summary>
        /// <typeparam name="T">Type of value (must be primitive type)</typeparam>
        /// <param name="value">Original value</param>
        /// <returns>Value represented in big endian</returns>
        public static T ToBigEndian<T>(T value)
            where T : unmanaged
        {
            return GetHostEndian() == Type.Big ? value : Swap(value);
        }

        /// <summary>
        /// Converts the input value to the specified endianness
        /// </summary>
        /// <typeparam name="T">Type of value (must be primitive type)</typeparam>
        /// <param name="value">Original value</param>
        /// <param name="endian">Target endianness</param>
        /// <returns>Value represented in the specified endianness</returns>
        public static T ToEndian<T>(T value, Type endian)
            where T : unmanaged
        {
            return endian == Type.Little ? ToLittleEndian(value) : ToBigEndian(value);
        }

        /// <summary>
        /// Encodes the specified primitive value into its byte representation
        /// </summary>
        /// <typeparam name="T">Value type</typeparam>
        /// <param name="value">Input value</param>
        /// <param name="toEndian">Target endianness (optional)</param>
        /// <param name="size">Maximum byte size (optional)</param>
        /// <returns>Byte representation of the value</returns>
        public static byte[] ToBytes<T>(T value, Type? toEndian = null,
                                        int? size = null)
            where T : unmanaged
        {
            // Least-significant bits come first in little endian
            bool takeFirst = GetHostEndian()
                == Type.Little;

            // Optional endianness swap
            if (toEndian != null)
            {
                value = ToEndian(value, (Type)toEndian);
            }

            byte[] bytes = BitConverter.GetBytes((dynamic)value);

            // Optional truncation
            if (size != null)
            {
                bytes = takeFirst
                    ? bytes.Take((int)size).ToArray()
                    : bytes.TakeLast((int)size).ToArray();
            }

            return bytes;
        }

        /// <summary>
        /// Decodes a primitive value from its byte representation
        /// </summary>
        /// <typeparam name="T">Value type</typeparam>
        /// <param name="bytes">Byte representation of the value</param>
        /// <param name="fromEndian">Source endianness (optional)</param>
        /// <returns>Primitive value</returns>
        /// <exception cref="OperationException">Unknown type was provided</exception>
        public static T FromBytes<T>(byte[] bytes, Type? fromEndian = null)
            where T : unmanaged
        {
            // Optional endianness swap
            if (fromEndian != null && fromEndian != GetHostEndian())
            {
                bytes = bytes.Reverse().ToArray();
            }

            switch (typeof(T).FullName)
            {
                case "System.Int8":
                case "System.UInt8":
                    return (T)(dynamic)bytes[0];

                case "System.Int16":
                    return (T)(dynamic)BitConverter.ToInt16(bytes);
                case "System.UInt16":
                    return (T)(dynamic)BitConverter.ToUInt16(bytes);

                case "System.Int32":
                    return (T)(dynamic)BitConverter.ToInt32(bytes);
                case "System.UInt32":
                    return (T)(dynamic)BitConverter.ToUInt32(bytes);

                case "System.Int64":
                    return (T)(dynamic)BitConverter.ToInt64(bytes);
                case "System.UInt64":
                    return (T)(dynamic)BitConverter.ToUInt64(bytes);

                case "System.Single":
                    return (T)(dynamic)BitConverter.ToSingle(bytes);
                case "System.Double":
                    return (T)(dynamic)BitConverter.ToDouble(bytes);

                default:
                    throw new OperationException(
                        $"Unsupported type: {typeof(T).FullName}");
            }
        }

        /// <summary>
        /// Performs a byteswap on the specified value
        /// </summary>
        /// <typeparam name="T">Value type</typeparam>
        /// <param name="value">Input value</param>
        /// <returns>Input value represented in the opposite endianness</returns>
        private static T Swap<T>(T value)
            where T : unmanaged
        {
            // BinaryPrimitives does not support decimal types yet
            if (typeof(T) == typeof(float)
                || typeof(T) == typeof(double))
            {
                return FromBytes<T>(ToBytes(value).Reverse().ToArray());
            }

            // Use the more optimized BinaryPrimitives when possible
            return BinaryPrimitives.ReverseEndianness((dynamic)value);
        }
    }
}
