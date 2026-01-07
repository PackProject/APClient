using LibWorkBench.Formats.NW4R.LayoutLib.Layout.Types;

namespace LibWorkBench.Formats.NW4R.LayoutLib.Layout.Data
{
    /// <summary>
    /// Text pane
    /// </summary>
    public sealed class TextBox : Pane
    {
        /// <summary>
        /// Material name
        /// </summary>
        public string MaterialName { get; set; } = "";

        /// <summary>
        /// Font name
        /// </summary>
        public string FontName { get; set; } = "";

        /// <summary>
        /// Font size
        /// </summary>
        public Size FontSize { get; set; } = new();

        /// <summary>
        /// Spacing between characters
        /// </summary>
        public float CharSpace { get; set; } = 0.0f;

        /// <summary>
        /// Spacing between lines
        /// </summary>
        public float LineSpace { get; set; } = 0.0f;

        /// <summary>
        /// Text string contents
        /// </summary>
        public string TextContent { get; set; } = "";

        /// <summary>
        /// Text string maximum size.
        /// If the text content overflows, the capacity is automatically updated.
        /// </summary>
        public ushort TextCapacity { get; set; } = 0;

        /// <summary>
        /// Text position origin settings
        /// </summary>
        public BasePosition TextPosition { get; set; } = new();

        /// <summary>
        /// Text alignment type
        /// </summary>
        public TextAlignment TextAlignment { get; set; } = TextAlignment.Left;

        /// <summary>
        /// Text vertex colors
        /// </summary>
        public TextColorSet TextColors { get; set; } = new();
    }
}
