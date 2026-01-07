using LibWorkBench.Formats.NW4R.LayoutLib.Layout.Types;
using LibWorkBench.Formats.Revolution.GX.Types;

namespace LibWorkBench.Formats.NW4R.LayoutLib.Layout.Data
{
    /// <summary>
    /// Pane material
    /// </summary>
    public sealed class Material
    {
        /// <summary>
        /// Material name
        /// </summary>
        public string Name { get; set; } = "";

        /// <summary>
        /// TEV color register settings
        /// </summary>
        public TevColorSet TevColors { get; set; } = new();

        /// <summary>
        /// TEV constant color register settings
        /// </summary>
        public TevKonstColorSet TevKColors { get; set; } = new();

        /// <summary>
        /// Texture map settings
        /// </summary>
        public List<TexMap> TexMaps { get; set; } = new();

        /// <summary>
        /// Texture S/R/T transformation settings
        /// </summary>
        public List<TexSrt> TexSrts { get; set; } = new();

        /// <summary>
        /// Texture coordinate generator settings
        /// </summary>
        public List<TexCoordGen> TexCoordGens { get; set; } = new();

        /// <summary>
        /// TEV color channel swap settings
        /// </summary>
        public TevSwapTable? TevSwapTable { get; set; } = null;

        /// <summary>
        /// Indirect texture S/R/T transformation settings
        /// </summary>
        public List<TexSrt> IndTexSrts { get; set; } = new();

        /// <summary>
        /// Indirect texture stages
        /// </summary>
        public List<IndirectStage> IndStages { get; set; } = new();

        /// <summary>
        /// TEV stages
        /// </summary>
        public List<TevStage> TevStages { get; set; } = new();

        /// <summary>
        /// Visibility test
        /// </summary>
        public AlphaCompare? AlphaCompare { get; set; } = null;

        /// <summary>
        /// Blend mode settings
        /// </summary>
        public BlendMode? BlendMode { get; set; } = null;

        /// <summary>
        /// Channel control settings
        /// </summary>
        public ChanCtrl? ChanCtrl { get; set; } = null;

        /// <summary>
        /// Material color (GX_COLOR0A0)
        /// </summary>
        public GXColor? MaterialColor { get; set; } = null;
    }
}
