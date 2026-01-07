using LibWorkBench.Attributes;

namespace LibWorkBench.Formats.NW4R.LayoutLib.Layout.Binary.Blocks
{
    /// <summary>
    /// Layout bounding block
    /// </summary>
    [BinaryBlockProfile(signature: "bnd1")]
    public sealed class BoundingBlock : PaneBlock
    {
        // Bounding provides no additional data beyond the base pane
    }
}
