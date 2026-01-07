using LibWorkBench.Utility;
using System.Text.Json;
using System.Text.Json.Serialization;

namespace LibWorkBench.Converters
{
    /// <summary>
    /// JSON converter for byte arrays (saves as hex bytes instead of Base64)
    /// </summary>
    public sealed class HexByteArrayJsonConverter : JsonConverter<byte[]>
    {
        /// <summary>
        /// Deserializes a byte array from JSON
        /// </summary>
        /// <param name="reader">JSON file reader</param>
        /// <param name="t">Destination type</param>
        /// <param name="options">Configuration for the deserializer</param>
        /// <returns>Byte array</returns>
        public override byte[]? Read(ref Utf8JsonReader reader, Type t, JsonSerializerOptions options)
        {
            string? str = reader.GetString();
            if (str == null)
            {
                return null;
            }

            return Util.FromHex(str);
        }

        /// <summary>
        /// Serializes a byte array to JSON
        /// </summary>
        /// <param name="writer">JSON file writer</param>
        /// <param name="value">Byte array</param>
        /// <param name="options">Configuration for the serializer</param>
        public override void Write(Utf8JsonWriter writer, byte[] value, JsonSerializerOptions options)
        {
            string str = Util.ToHex(value, prefix: true);
            writer.WriteStringValue(str);
        }
    }
}
