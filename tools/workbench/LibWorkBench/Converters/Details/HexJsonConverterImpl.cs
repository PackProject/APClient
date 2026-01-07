using LibWorkBench.Utility;
using System.Text.Json;
using System.Text.Json.Serialization;

namespace LibWorkBench.Converters.Details
{
    /// <summary>
    /// Base class for hexadecimal number JSON converters
    /// </summary>
    public class HexJsonConverterImpl<T> : JsonConverter<T>
        where T : unmanaged
    {
        /// <summary>
        /// Deserializes a hexadecimal number value from JSON
        /// </summary>
        /// <param name="reader">JSON file reader</param>
        /// <param name="t">Destination type</param>
        /// <param name="options">Configuration for the deserializer</param>
        /// <returns>Number value</returns>
        public override T Read(ref Utf8JsonReader reader, Type t, JsonSerializerOptions options)
        {
            string? str = reader.GetString();
            if (str == null)
            {
                return default;
            }

            return Util.FromHex<T>(str);
        }

        /// <summary>
        /// Serializes a number value to JSON as its hexadecimal representation
        /// </summary>
        /// <param name="writer">JSON file writer</param>
        /// <param name="value">Numeric value</param>
        /// <param name="options">Configuration for the serializer</param>
        public override void Write(Utf8JsonWriter writer, T value, JsonSerializerOptions options)
        {
            string hex = Util.ToHex<T>(value, delimit: false, prefix: true);
            writer.WriteStringValue(hex);
        }
    }
}
