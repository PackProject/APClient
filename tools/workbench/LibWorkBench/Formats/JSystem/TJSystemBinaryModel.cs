using LibWorkBench.Core.Models.Binary;
using LibWorkBench.Core.Models.Details;
using LibWorkBench.Formats.JSystem.Details;

namespace LibWorkBench.Formats.JSystem
{
    /// <summary>
    /// Base class for JSYSTEM binary-view models
    /// </summary>
    /// <typeparam name="TParentResource">Parent resource class</typeparam>
    /// <typeparam name="TBlockFactory">Block factory class</typeparam>
    public abstract class TJSystemBinaryModel<TParentResource, TBlockFactory> : JSystemBinaryModel
        where TParentResource : ResourceImpl
        where TBlockFactory : BinaryBlockFactory, new()
    {
        /// <summary>
        /// Resource that owns this model
        /// </summary>
        public new TParentResource? Resource
            => (TParentResource?)base.Resource;

        /// <summary>
        /// Constructor
        /// </summary>
        public TJSystemBinaryModel()
            : base(new TBlockFactory())
        {
        }
    }
}
