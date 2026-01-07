using LibWorkBench.Core.Models.Binary.Details;

namespace LibWorkBench.Core.Models.Binary
{
    /// <summary>
    /// Base class for binary model blocks
    /// </summary>
    public abstract class TBinaryBlock<TParentModel> : BinaryBlock
        where TParentModel : BlockBinaryModel, new()
    {
        /// <summary>
        /// Model that owns this block
        /// </summary>
        public new TParentModel? Model
        {
            get => (TParentModel?)base.Model;
            set => base.Model = value;
        }
    }

}
