using LibWorkBench.Core;
using System.Text;

namespace LibWorkBench.Utility
{
    /// <summary>
    /// Miscellaneous utility functions
    /// </summary>
    public static class Util
    {
        /// <summary>
        /// Rounds a value up to the nearest instance of the specified alignment
        /// </summary>
        /// <typeparam name="T">Input value type</typeparam>
        /// <param name="x">Input value</param>
        /// <param name="alignment">Alignment</param>
        /// <returns>Aligned value (rounded up)</returns>
        public static T RoundUp<T>(T x, ulong alignment)
            where T : unmanaged
        {
            T result = (T)(alignment + (dynamic)x - 1 & ~(alignment - 1));
            return result;
        }

        /// <summary>
        /// Rounds a value down to the nearest instance of the specified alignment
        /// </summary>
        /// <typeparam name="T">Input value type</typeparam>
        /// <param name="x">Input value</param>
        /// <param name="alignment">Alignment</param>
        /// <returns>Aligned value (rounded down)</returns>
        public static T RoundDown<T>(T x, ulong alignment)
            where T : unmanaged
        {
            T result = (T)((dynamic)x & ~(alignment - 1));
            return result;
        }

        /// <summary>
        /// Counts the number of values in the specified enum
        /// </summary>
        /// <typeparam name="T">Enum type</typeparam>
        /// <returns>Number of enum values</returns>
        public static int EnumCount<T>()
        {
            return Enum.GetValues(typeof(T)).Length;
        }

        /// <summary>
        /// Prints the specified object hierarchy to the console for debugging purposes
        /// </summary>
        /// <param name="root">Root object</param>
        /// <param name="indent">Text indent level</param>
        public static void DumpHierarchy<T>(T root, uint indent = 0)
            where T : IUseName, IUseHierarchy<T>
        {
            for (uint i = 0; i < indent; i++)
            {
                Console.Write("-");
            }

            Console.WriteLine(root.Name);

            foreach (var it in root.Children)
            {
                DumpHierarchy(it, ++indent);
            }
        }

        /// <summary>
        /// Encodes a byte array into its hexadecimal string representation
        /// </summary>
        /// <param name="bytes">Input data</param>
        /// <param name="delimit">Whether to delimit bytes by whitespace</param>
        /// <param name="prefix">Whether to include the "0x" prefix</param>
        /// <returns>String representation of bytes</returns>
        public static string ToHex(byte[] bytes, bool delimit = true,
                                   bool prefix = false)
        {
            StringBuilder builder = new();

            for (int i = 0; i < bytes.Length; i++)
            {
                string next = $"{bytes[i]:X2}";
                builder.Append(delimit && prefix ? $"0x{next}" : next);

                if (delimit && i != bytes.Length - 1)
                {
                    builder.Append(' ');
                }
            }

            string hex = builder.ToString();
            return !delimit && prefix ? $"0x{hex}" : hex;
        }

        /// <summary>
        /// Decodes a hexadecimal string into its original bytes
        /// </summary>
        /// <param name="str">Input string</param>
        /// <returns>Bytes contained within the string</returns>
        public static byte[] FromHex(string str)
        {
            // Remove optional prefix
            str = str.Replace("0x", "");

            // Remove optional delimiters
            str = str.Replace(" ", "");

            return Convert.FromHexString(str);
        }

        /// <summary>
        /// Encodes a primitive value into its hexadecimal string representation
        /// </summary>
        /// <typeparam name="T">Value type</typeparam>
        /// <param name="value">Input value</param>
        /// <param name="toEndian">Target endianness (optional)</param>
        /// <param name="size">Maximum byte size (optional)</param>
        /// <param name="delimit">Whether to delimit bytes by whitespace</param>
        /// <param name="prefix">Whether to include the "0x" prefix</param>
        /// <returns>String representation of value bytes</returns>
        public static string ToHex<T>(T value,
                                 EndianUtil.Type toEndian = EndianUtil.Type.Big,
                                 int? size = null, bool delimit = true,
                                 bool prefix = false)
            where T : unmanaged
        {
            byte[] bytes = EndianUtil.ToBytes(value, toEndian, size);
            return ToHex(bytes, delimit, prefix);
        }

        /// <summary>
        /// Decodes a hexadecimal string into its original value
        /// </summary>
        /// <typeparam name="T">Value type</typeparam>
        /// <param name="str">Input string</param>
        /// <param name="fromEndian">Source endianness (optional)</param>
        /// <returns>Value contained within the string</returns>
        public static T FromHex<T>(string str,
                                   EndianUtil.Type fromEndian = EndianUtil.Type.Big)
            where T : unmanaged
        {
            byte[] bytes = FromHex(str);
            return EndianUtil.FromBytes<T>(bytes, fromEndian);
        }
    }
}
