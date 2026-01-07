using LibWorkBench.Formats.Revolution.GX.Types;

namespace LibWorkBench.Formats.NW4R.LayoutLib.Layout
{
    /// <summary>
    /// Shared layout constants
    /// </summary>
    public static class LayoutDefine
    {
        /// <summary>
        /// Resource name string length
        /// </summary>
        public const int RES_NAME_LEN = 16;

        /// <summary>
        /// Material name string length
        /// </summary>
        public const int MAT_NAME_LEN = 20;

        /// <summary>
        /// Pane userdata string length
        /// </summary>
        public const int USERDATA_LEN = 8;

        /// <summary>
        /// Maximum number of texture S/R/T transformations
        /// </summary>
        public const int MAX_TEX_SRT =
            (GXTexMtx.GX_TEXMTX9 - GXTexMtx.GX_TEXMTX0) / 3 + 1;

        /// <summary>
        /// Maximum number of indirect texture S/R/T transformations
        /// </summary>
        public const int MAX_IND_SRT =
            GXIndTexMtxID.GX_ITM_2 - GXIndTexMtxID.GX_ITM_0 + 1;
    }
}
