using LibWorkBench.Formats.NW4R.LayoutLib.Layout.Types;

namespace LibWorkBench.Formats.NW4R.LayoutLib.Layout.Data
{
    /// <summary>
    /// Window frame (data-view)
    /// </summary>
    public sealed class WindowFrame
    {
        /// <summary>
        /// Material name
        /// </summary>
        public string MaterialName { get; set; } = "";

        /// <summary>
        /// Texture flip type
        /// </summary>
        public TextureFlip TextureFlip { get; set; } = TextureFlip.None;
    }
}
