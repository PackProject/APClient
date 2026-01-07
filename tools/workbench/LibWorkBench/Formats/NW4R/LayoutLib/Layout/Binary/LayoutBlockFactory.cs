using LibWorkBench.Core.Models.Binary;
using LibWorkBench.Formats.NW4R.LayoutLib.Layout.Binary.Blocks;

namespace LibWorkBench.Formats.NW4R.LayoutLib.Layout.Binary
{
    /// <summary>
    /// Layout binary block factory
    /// </summary>
    public sealed class LayoutBlockFactory : BinaryBlockFactory
    {
        /// <summary>
        /// Constructor
        /// </summary>
        public LayoutBlockFactory()
        {
            RegisterBlock<BoundingBlock>();
            RegisterBlock<FontListBlock>();
            RegisterBlock<GroupBlock>();
            RegisterBlock<GroupEndBlock>();
            RegisterBlock<GroupStartBlock>();
            RegisterBlock<LayoutBlock>();
            RegisterBlock<MaterialListBlock>();
            RegisterBlock<PaneBlock>();
            RegisterBlock<PaneEndBlock>();
            RegisterBlock<PaneStartBlock>();
            RegisterBlock<PictureBlock>();
            RegisterBlock<TextBoxBlock>();
            RegisterBlock<TextureListBlock>();
            RegisterBlock<UserDataBlock>();
            RegisterBlock<WindowBlock>();
        }
    }
}
