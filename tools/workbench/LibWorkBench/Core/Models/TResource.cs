using LibWorkBench.Core.Models.Binary;
using LibWorkBench.Core.Models.Data;
using LibWorkBench.Core.Models.Details;

namespace LibWorkBench.Core.Models
{
    /// <summary>
    /// Base class for resource types
    /// </summary>
    /// <typeparam name="TBinaryModel">Binary-view model class</typeparam>
    /// <typeparam name="TDataModel">Data-view model class</typeparam>
    public class TResource<TBinaryModel, TDataModel> : ResourceImpl
        where TBinaryModel : BinaryModel, new()
        where TDataModel : DataModel, new()
    {
        /// <summary>
        /// Accesses the binary-view model
        /// </summary>
        protected TBinaryModel BinaryModel => (TBinaryModel)_binaryModel;
        /// <summary>
        /// Accesses the data-view model
        /// </summary>
        protected TDataModel DataModel => (TDataModel)_dataModel;

        /// <summary>
        /// Constructor
        /// </summary>
        public TResource()
            : base(new TBinaryModel(),
                   new TDataModel())
        {
            _binaryModel.Resource = this;
            _dataModel.Resource = this;
        }
    }
}
