using LibWorkBench.Formats.Revolution.GX.Types;

namespace LibWorkBench.Formats.NW4R.LayoutLib.Layout.Data
{
    /// <summary>
    /// Material texture map (data-view)
    /// </summary>
    public sealed class TexMap
    {
        /// <summary>
        /// Texture name
        /// </summary>
        public string TextureName { get; set; } = "";

        /// <summary>
        /// Texture wrap mode (S)
        /// </summary>
        public GXTexWrapMode WrapS { get; set; } = GXTexWrapMode.GX_CLAMP;

        /// <summary>
        /// Texture wrap mode (T)
        /// </summary>
        public GXTexWrapMode WrapT { get; set; } = GXTexWrapMode.GX_CLAMP;
    }
}
