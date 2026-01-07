using LibWorkBench.Core.Models.Binary;
using LibWorkBench.Core.Models.Data;

namespace LibWorkBench.Formats.Pack.Details
{
    /// <summary>
    /// Base class for ExcelBin binary-view models (implementation details)
    /// </summary>
    public abstract class ExcelBinBinaryModel : BinaryModel
    {
        /// <summary>
        /// Updates this model to match the contents of the data-view model
        /// </summary>
        /// <param name="dataModel">Data-view model</param>
        public override void Sync(DataModel dataModel)
        {
            ExcelBinDataModel src = (ExcelBinDataModel)dataModel;

            OnSync(src);
        }

        /// <summary>
        /// Updates this model to match the contents of the data-view model (derived implementation)
        /// </summary>
        /// <param name="dataModel">Data-view model</param>
        public abstract void OnSync(ExcelBinDataModel dataModel);
    }
}
