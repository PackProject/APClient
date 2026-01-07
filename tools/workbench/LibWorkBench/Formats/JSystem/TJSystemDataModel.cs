using LibWorkBench.Core.Models.Details;
using LibWorkBench.Formats.JSystem.Details;
using System.Text.Json.Serialization;

namespace LibWorkBench.Formats.JSystem
{
    /// <summary>
    /// Base class for JSYSTEM data-view models
    /// </summary>
    /// <typeparam name="TParentResource">Parent resource class</typeparam>
    public abstract class TJSystemDataModel<TParentResource> : JSystemDataModel
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
