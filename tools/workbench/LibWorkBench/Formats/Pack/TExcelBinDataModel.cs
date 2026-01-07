using LibWorkBench.Core.Models.Details;
using LibWorkBench.Formats.Pack.Details;
using System.Text.Json.Serialization;

namespace LibWorkBench.Formats.Pack
{
    /// <summary>
    /// Base class for ExcelBin data-view models
    /// </summary>
    /// <typeparam name="TParentResource">Parent resource class</typeparam>
    public abstract class TExcelBinDataModel<TParentResource> : ExcelBinDataModel
        where TParentResource : ResourceImpl
    {
        /// <summary>
        /// Resource that owns this model
        /// </summary>
        [JsonIgnore]
        public new TParentResource? Resource
            => (TParentResource?)base.Resource;
    }
}
