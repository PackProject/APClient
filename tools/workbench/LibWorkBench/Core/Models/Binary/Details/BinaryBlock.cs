using LibWorkBench.Attributes;
using LibWorkBench.Attributes.Details;
using LibWorkBench.Core.Models.Data;
using LibWorkBench.IO.Streams;

namespace LibWorkBench.Core.Models.Binary.Details
{
    /// <summary>
    /// Base class for binary model blocks (implementation details)
    /// </summary>
    public abstract class BinaryBlock : ProfileProxy<BinaryBlockProfileAttribute>, IUseBinary
    {
        /// <summary>
        /// Model that owns this block
        /// </summary>
        public BlockBinaryModel? Model { get; set; } = null;

        /// <summary>
        /// Deserializes the contents of this object from a file
        /// </summary>
        /// <param name="reader">Binary stream to the file</param>
        public void Read(ReadStream reader)
        {
            OnRead(reader);
        }

        /// <summary>
        /// Serializes the contents of this object to a file
        /// </summary>
        /// <param name="writer">Binary stream to the file</param>
        public void Write(WriteStream writer)
        {
            OnWrite(writer);

            // Model cannot track count because of recursive blocks
            if (Model != null)
            {
                Model.BlocksWritten++;
            }
        }

        /// <summary>
        /// Updates this block to match the contents of the data-view model
        /// </summary>
        /// <param name="dataModel">Data-view model</param>
        public void Sync(DataModel dataModel)
        {
            OnSync(dataModel);
        }

        /// <summary>
        /// Deserializes the contents of this object from a file (derived implementation)
        /// </summary>
        /// <param name="reader">Binary stream to the file</param>
        public abstract void OnRead(ReadStream reader);

        /// <summary>
        /// Serializes the contents of this object to a file (derived implementation)
        /// </summary>
        /// <param name="writer">Binary stream to the file</param>
        public abstract void OnWrite(WriteStream writer);

        /// <summary>
        /// Updates this block to match the contents of the data-view model (derived implementation)
        /// </summary>
        /// <param name="dataModel">Data-view model</param>
        public abstract void OnSync(DataModel dataModel);
    }
}
