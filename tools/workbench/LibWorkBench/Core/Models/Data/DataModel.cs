using LibWorkBench.Core.Models.Binary;
using LibWorkBench.Core.Models.Details;
using LibWorkBench.IO.Streams;
using System.Text.Json.Serialization;

namespace LibWorkBench.Core.Models.Data
{
    /// <summary>
    /// Base class for data-view models
    /// </summary>
    public abstract class DataModel : IUseJson
    {
        /// <summary>
        /// Resource that owns this model
        /// </summary>
        [JsonIgnore]
        public ResourceImpl? Resource { get; set; } = null;

        /// <summary>
        /// Deserializes the contents of this model from a file
        /// </summary>
        /// <param name="reader">Stream to the JSON file</param>
        public abstract void Load(JsonFileReader reader);

        /// <summary>
        /// Serializes the contents of this model to a file
        /// </summary>
        /// <param name="writer">Stream to the JSON file</param>
        public abstract void Dump(JsonFileWriter writer);

        /// <summary>
        /// Updates this model to match the contents of the binary-view model
        /// </summary>
        /// <param name="binaryModel">Binary-view model</param>
        public abstract void Sync(BinaryModel binaryModel);
    }
}
