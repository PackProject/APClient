using LibWorkBench.Formats.NW4R.LayoutLib.Layout.Types;

namespace LibWorkBench.Formats.NW4R.LayoutLib.Layout.Data
{
    /// <summary>
    /// Image pane
    /// </summary>
    public sealed class Picture : Pane
    {
        /// <summary>
        /// Material name
        /// </summary>
        public string MaterialName { get; set; } = "";

        /// <summary>
        /// Vertex colors
        /// </summary>
        public VertexColorSet VertexColors { get; set; } = new();

        /// <summary>
        /// Texture coordinates
        /// </summary>
        public List<TexCoord> TexCoords { get; set; } = new();
    }
}
