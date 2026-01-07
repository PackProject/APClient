using LibWorkBench.Core.Models.Binary;
using LibWorkBench.Core.Models.Data;

namespace LibWorkBench.Formats.Pack.Details
{
    /// <summary>
    /// Base class for ExcelBin data-view models (implementation details)
    /// </summary>
    public abstract class ExcelBinDataModel : DataModel
    {
        /// <summary>
        /// Updates this model to match the contents of the binary-view model
        /// </summary>
        /// <param name="binaryModel">Binary-view model</param>
        public override void Sync(BinaryModel binaryModel)
        {
            ExcelBinBinaryModel src = (ExcelBinBinaryModel)binaryModel;

            OnSync(src);
        }

        /// <summary>
        /// Updates this model to match the contents of the binary-view model (derived implementation)
        /// </summary>
        /// <param name="binaryModel">Binary-view model</param>
        public abstract void OnSync(ExcelBinBinaryModel binaryModel);
    }
}
