using LibWorkBench.Core.Models.Binary;
using LibWorkBench.Core.Models.Details;
using LibWorkBench.Formats.NW4R.Details;

namespace LibWorkBench.Formats.NW4R
{
    /// <summary>
    /// Base class for NW4R binary-view models
    /// </summary>
    /// <typeparam name="TParentResource">Parent resource class</typeparam>
    /// <typeparam name="TBlockFactory">Block factory class</typeparam>
    public abstract class TNW4RBinaryModel<TParentResource, TBlockFactory> : NW4RBinaryModel
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
        public TNW4RBinaryModel()
            : base(new TBlockFactory())
        {
        }
    }
}
