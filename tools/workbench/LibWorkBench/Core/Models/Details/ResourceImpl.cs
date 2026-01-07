using LibWorkBench.Attributes;
using LibWorkBench.Attributes.Details;
using LibWorkBench.Core.Models.Binary;
using LibWorkBench.Core.Models.Data;
using LibWorkBench.IO.Streams;

namespace LibWorkBench.Core.Models.Details
{
    /// <summary>
    /// Base class for resource types (implementation details)
    /// </summary>
    public abstract class ResourceImpl
        : ProfileProxy<ResourceProfileAttribute>, IUseBinary, IUseJson
    {
        /// <summary>
        /// The binary-view model of this resource
        /// </summary>
        protected readonly BinaryModel _binaryModel;
        /// <summary>
        /// The data-view model of this resource
        /// </summary>
        protected readonly DataModel _dataModel;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="binaryModel">Binary-view model</param>
        /// <param name="dataModel">Data-view model</param>
        public ResourceImpl(BinaryModel binaryModel,
                            DataModel dataModel)
        {
            _binaryModel = binaryModel;
            _dataModel = dataModel;
        }

        /// <summary>
        /// Deserializes the contents of the binary-view model from a file
        /// </summary>
        /// <param name="reader">Binary stream to the file</param>
        public void Read(ReadStream reader)
        {
            _binaryModel.Read(reader);

            // "Load" data-view model from new binary contents
            _dataModel.Sync(_binaryModel);
        }

        /// <summary>
        /// Serializes the contents of the binary-view model to a file
        /// </summary>
        /// <param name="writer">Binary stream to the file</param>
        public void Write(WriteStream writer)
        {
            // "Save" data-view model as binary contents
            _binaryModel.Sync(_dataModel);

            _binaryModel.Write(writer);
        }

        /// <summary>
        /// Deserializes the contents of the data-view model from a file
        /// </summary>
        /// <param name="reader">Stream to the JSON file</param>
        public void Load(JsonFileReader reader)
        {
            _dataModel.Load(reader);
        }

        /// <summary>
        /// Serializes the contents of the data-view model to a file
        /// </summary>
        /// <param name="writer">Stream to the JSON file</param>
        public void Dump(JsonFileWriter writer)
        {
            _dataModel.Dump(writer);
        }
    }
}
