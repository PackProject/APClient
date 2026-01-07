using LibWorkBench.Core.Models.Data;
using LibWorkBench.Core.Models.Details;
using System.Text.Json.Serialization;

namespace LibWorkBench.Formats
{
    /// <summary>
    /// Base class for simple data-view models
    /// </summary>
    /// <typeparam name="TParentResource">Parent resource class</typeparam>
    public abstract class TRawDataModel<TParentResource> : DataModel
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
