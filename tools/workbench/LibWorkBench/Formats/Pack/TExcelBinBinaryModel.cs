using LibWorkBench.Core.Models.Details;
using LibWorkBench.Formats.Pack.Details;

namespace LibWorkBench.Formats.Pack
{
    /// <summary>
    /// Base class for ExcelBin binary-view models
    /// </summary>
    /// <typeparam name="TParentResource">Parent resource class</typeparam>
    public abstract class TExcelBinBinaryModel<TParentResource> : ExcelBinBinaryModel
        where TParentResource : ResourceImpl
    {
        /// <summary>
        /// Resource that owns this model
        /// </summary>
        public new TParentResource? Resource
            => (TParentResource?)base.Resource;
    }
}
