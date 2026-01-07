using LibWorkBench.Formats.NW4R.LayoutLib.Layout;

namespace LibWorkBench.Formats.NW4R.LayoutLib.Animation
{
    /// <summary>
    /// Shared layout animation constants
    /// </summary>
    public static class AnimationDefine
    {
        /// <summary>
        /// Animation name target length
        /// </summary>
        public static readonly int TARGET_NAME_LEN =
            // (Target can be either pane/material)
            Math.Max(LayoutDefine.RES_NAME_LEN, LayoutDefine.MAT_NAME_LEN);

        /// <summary>
        /// Animation info block signature lenght
        /// </summary>
        public const int ANIM_INFO_SIGNATURE_LEN = 4;

        /// <summary>
        /// Pane S/R/T transformation animation
        /// </summary>
        public const string SIGNATURE_ANMPANESRT = "RLPA";
        /// <summary>
        /// Pane visibility animation
        /// </summary>
        public const string SIGNATURE_ANMPANEVIS = "RLVI";

        /// <summary>
        /// Vertex color animation
        /// </summary>
        public const string SIGNATURE_ANMVTXCLR = "RLVC";
        /// <summary>
        /// Material color animation
        /// </summary>
        public const string SIGNATURE_ANMMATCLR = "RLMC";

        /// <summary>
        /// Texture S/R/T transformation animation
        /// </summary>
        public const string SIGNATURE_ANMTEXSRT = "RLTS";
        /// <summary>
        /// Texture pattern animation
        /// </summary>
        public const string SIGNATURE_ANMTEXPAT = "RLTP";
        /// <summary>
        /// Indirect texture S/R/T transformation animation
        /// </summary>
        public const string SIGNATURE_ANMINDTEXSRT = "RLIM";
    }
}
