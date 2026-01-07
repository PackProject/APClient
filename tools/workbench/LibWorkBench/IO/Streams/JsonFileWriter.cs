using LibWorkBench.IO.Encodings;
using LibWorkBench.IO.Sources;
using LibWorkBench.Utility;
using System.Text.Json;
using System.Text.Json.Serialization;

namespace LibWorkBench.IO.Streams
{
    /// <summary>
    /// JSON file stream with write access
    /// </summary>
    public class JsonFileWriter : Stream // (don't want prim methods)
    {
        /// <summary>
        /// Configuration for the serializer
        /// </summary>
        public JsonSerializerOptions Options { get; } = new();

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="path">File path to open</param>
        public JsonFileWriter(string path)
            : base(new FileDataSource(path, writable: true),
                   new DummyPrimEncoding(),
                   new DummyCharEncoding(),
                   EndianUtil.GetHostEndian())
        {
            Options.IndentSize = 2;
            Options.WriteIndented = true;
            Options.PropertyNamingPolicy = JsonNamingPolicy.SnakeCaseLower;

            // Default enum serialization is to-string
            Options.Converters.Add(
                new JsonStringEnumConverter(JsonNamingPolicy.SnakeCaseUpper));
        }

        /// <summary>
        /// Serializes the contents of the specified JSON object
        /// </summary>
        /// <typeparam name="T">Object type</typeparam>
        /// <param name="src">Source object</param>
        /// <exception cref="JsonException">Serialization is not possible</exception>
        public void Serialize<T>(T src)
        {
            FileStream stream = ((FileDataSource)Source).BaseStream;

            try
            {
                JsonSerializer.Serialize(stream, src, Options);
            }
            catch (NotSupportedException e)
            {
                throw new JsonException(e.Message);
            }
        }
    }
}
