using LibWorkBench.IO.Streams;

namespace LibWorkBench.Core
{
    /// <summary>
    /// Interface for objects serialized as JSON data
    /// </summary>
    public interface IUseJson
    {
        /// <summary>
        /// Deserializes the contents of this object from a file
        /// </summary>
        /// <param name="reader">Stream to the JSON file</param>
        public abstract void Load(JsonFileReader reader);

        /// <summary>
        /// Serializes the contents of this object to a file
        /// </summary>
        /// <param name="writer">Stream to the JSON file</param>
        public abstract void Dump(JsonFileWriter writer);
    }
}
