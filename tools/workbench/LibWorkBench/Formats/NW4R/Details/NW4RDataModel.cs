using LibWorkBench.Core.Models.Binary;
using LibWorkBench.Core.Models.Data;
using LibWorkBench.Formats.NW4R.Details;
using System.Text.Json.Serialization;

namespace LibWorkBench.Formats.NW4R
{
    /// <summary>
    /// Base class for NW4R data-view models (implementation details)
    /// </summary>
    /// <typeparam name="TParentResource">Parent resource class</typeparam>
    public abstract class NW4RDataModel : DataModel
    {
        /// <summary>
        /// Version of this file's specification
        /// </summary>
        [JsonPropertyOrder(int.MinValue)]
        public uint Version { get; set; } = 0;

        /// <summary>
        /// Updates this model to match the contents of the binary-view model
        /// </summary>
        /// <param name="binaryModel">Binary-view model</param>
        public override void Sync(BinaryModel binaryModel)
        {
            NW4RBinaryModel src = (NW4RBinaryModel)binaryModel;

            Version = src.Version;

            OnSync(src);
        }

        /// <summary>
        /// Updates this model to match the contents of the binary-view model (derived implementation)
        /// </summary>
        /// <param name="binaryModel">Binary-view model</param>
        public abstract void OnSync(NW4RBinaryModel binaryModel);
    }
}
