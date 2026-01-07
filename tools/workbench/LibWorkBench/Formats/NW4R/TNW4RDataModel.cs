using LibWorkBench.Core.Models.Details;
using System.Text.Json.Serialization;

namespace LibWorkBench.Formats.NW4R
{
    /// <summary>
    /// Base class for NW4R data-view models
    /// </summary>
    /// <typeparam name="TParentResource">Parent resource class</typeparam>
    public abstract class TNW4RDataModel<TParentResource> : NW4RDataModel
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
