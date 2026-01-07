using LibWorkBench.Formats.NW4R.LayoutLib.Layout.Types;

namespace LibWorkBench.Formats.NW4R.LayoutLib.Layout.Data
{
    /// <summary>
    /// Window frame pane
    /// </summary>
    public sealed class Window : Pane
    {
        /// <summary>
        /// Window content
        /// </summary>
        public WindowContent Content { get; set; } = new();

        /// <summary>
        /// Content inflation
        /// </summary>
        public WindowInflation Inflation { get; set; } = new();

        /// <summary>
        /// Window frames
        /// </summary>
        public List<WindowFrame> Frames { get; set; } = new();
    }
}
