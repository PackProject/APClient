using LibWorkBench.Attributes;
using LibWorkBench.Attributes.Details;
using LibWorkBench.Core.Models.Data;
using LibWorkBench.Core.Models.Details;
using LibWorkBench.IO.Streams;

namespace LibWorkBench.Core.Models.Binary
{
    /// <summary>
    /// Base class for binary-view models
    /// </summary>
    public abstract class BinaryModel : ProfileProxy<BinaryModelProfileAttribute>, IUseBinary
    {
        /// <summary>
        /// Resource that owns this model
        /// </summary>
        public ResourceImpl? Resource { get; set; } = null;

        /// <summary>
        /// Deserializes the contents of this model from a file
        /// </summary>
        /// <param name="reader">Binary stream to the file</param>
        public abstract void Read(ReadStream reader);

        /// <summary>
        /// Serializes the contents of this model to a file
        /// </summary>
        /// <param name="writer">Binary stream to the file</param>
        public abstract void Write(WriteStream writer);

        /// <summary>
        /// Updates this model to match the contents of the data-view model
        /// </summary>
        /// <param name="dataModel">Data-view model</param>
        public abstract void Sync(DataModel dataModel);
    }
}
