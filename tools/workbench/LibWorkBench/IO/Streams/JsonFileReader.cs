using LibWorkBench.IO.Encodings;
using LibWorkBench.IO.Sources;
using LibWorkBench.Utility;
using System.Reflection;
using System.Text.Json;
using System.Text.Json.Serialization;

namespace LibWorkBench.IO.Streams
{
    /// <summary>
    /// JSON file stream with read access
    /// </summary>
    public class JsonFileReader : Stream // (don't want prim methods)
    {
        /// <summary>
        /// Configuration for the serializer
        /// </summary>
        public JsonSerializerOptions Options { get; } = new();

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="path">File path to open</param>
        public JsonFileReader(string path)
            : base(new MemoryDataSource(File.ReadAllBytes(path),
                                        writable: false),
                   new DummyPrimEncoding(),
                   new DummyCharEncoding(),
                   EndianUtil.GetHostEndian())
        {
            Options.PropertyNamingPolicy = JsonNamingPolicy.SnakeCaseLower;

            // Default enum serialization is to-string
            Options.Converters.Add(
                new JsonStringEnumConverter(JsonNamingPolicy.SnakeCaseUpper));
        }

        /// <summary>
        /// Deserializes the contents of this JSON file
        /// </summary>
        /// <typeparam name="T">Object type</typeparam>
        /// <returns>Deserialized element</returns>
        /// <exception cref="JsonException">Deserialization is not possible</exception>
        public T Deserialize<T>()
        {
            MemoryStream stream = ((MemoryDataSource)Source).BaseStream;
            T? obj = JsonSerializer.Deserialize<T>(stream, Options);

            if (obj == null)
            {
                throw new JsonException();
            }

            return obj;
        }

        /// <summary>
        /// Deserializes the contents of this JSON file into an existing object
        /// </summary>
        /// <typeparam name="T">Object type</typeparam>
        /// <param name="dst">Destination object</param>
        /// <exception cref="JsonException">Deserialization is not possible</exception>
        public void Deserialize<T>(T dst)
        {
            T obj = Deserialize<T>();
            PopulateObject(dst, obj);
        }

        /// <summary>
        /// Populates a destination object's properties using a specified source object
        /// </summary>
        /// <typeparam name="T">Object type</typeparam>
        /// <param name="dst">Destination object</param>
        /// <param name="src">Source object</param>
        private static void PopulateObject<T>(T dst, T src)
        {
            // Only operate on non-static, public properties
            PropertyInfo[] properties = typeof(T).GetProperties(
                BindingFlags.Instance | BindingFlags.Public);

            // Copy over from the source object
            foreach (var it in properties)
            {
                // Ignore properties that are not serialized
                if (Attribute.IsDefined(it, typeof(JsonIgnoreAttribute)))
                {
                    continue;
                }

                it.SetValue(dst, it.GetValue(src));
            }
        }
    }
}
