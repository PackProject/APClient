using LibWorkBench.Core.Models.Binary;
using LibWorkBench.Formats.NW4R.LayoutLib.Animation.Binary.Blocks;

namespace LibWorkBench.Formats.NW4R.LayoutLib.Animation.Binary
{
    /// <summary>
    /// Layout animation binary block factory
    /// </summary>
    public sealed class AnimationBlockFactory : BinaryBlockFactory
    {
        /// <summary>
        /// Constructor
        /// </summary>
        public AnimationBlockFactory()
        {
            RegisterBlock<AnimationInfoBlock>();
        }
    }
}
