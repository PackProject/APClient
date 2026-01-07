using LibWorkBench.Exceptions;
using LibWorkBench.Formats.NW4R.LayoutLib.Animation;
using LibWorkBench.Formats.NW4R.LayoutLib.Animation.Types;

namespace LibWorkBench.Formats.NW4R.LayoutLib.Animation.Utility
{
    /// <summary>
    /// Animation utilities
    /// </summary>
    public static class AnimationUtil
    {
        /// <summary>
        /// Converts the specified animation info block signature into the corresponding enum value
        /// </summary>
        /// <param name="signature">Animation info block signature</param>
        /// <returns>Animation info kind</returns>
        /// <exception cref="OperationException">Block signature is unknown</exception>
        public static AnimInfoKind GetAnimInfoKind(string signature)
        {
            switch (signature)
            {
                case AnimationDefine.SIGNATURE_ANMPANESRT:
                    return AnimInfoKind.PaneSrt;

                case AnimationDefine.SIGNATURE_ANMPANEVIS:
                    return AnimInfoKind.PaneVis;

                case AnimationDefine.SIGNATURE_ANMVTXCLR:
                    return AnimInfoKind.VtxClr;

                case AnimationDefine.SIGNATURE_ANMMATCLR:
                    return AnimInfoKind.MatClr;

                case AnimationDefine.SIGNATURE_ANMTEXSRT:
                    return AnimInfoKind.TexSrt;

                case AnimationDefine.SIGNATURE_ANMTEXPAT:
                    return AnimInfoKind.TexPat;

                case AnimationDefine.SIGNATURE_ANMINDTEXSRT:
                    return AnimInfoKind.IndTexSrt;

                default:
                    throw new OperationException("Unknown signature");
            }
        }

        /// <summary>
        /// Converts the specified animation info kind into the corresponding block signature
        /// </summary>
        /// <param name="kind">Animation info kind</param>
        /// <returns>Animation info block signature</returns>
        /// <exception cref="OperationException">Animation info kind is invalid</exception>
        public static string GetAnimInfoSignature(AnimInfoKind kind)
        {
            switch (kind)
            {
                case AnimInfoKind.PaneSrt:
                    return AnimationDefine.SIGNATURE_ANMPANESRT;

                case AnimInfoKind.PaneVis:
                    return AnimationDefine.SIGNATURE_ANMPANEVIS;

                case AnimInfoKind.VtxClr:
                    return AnimationDefine.SIGNATURE_ANMVTXCLR;

                case AnimInfoKind.MatClr:
                    return AnimationDefine.SIGNATURE_ANMMATCLR;

                case AnimInfoKind.TexSrt:
                    return AnimationDefine.SIGNATURE_ANMTEXSRT;

                case AnimInfoKind.TexPat:
                    return AnimationDefine.SIGNATURE_ANMTEXPAT;

                case AnimInfoKind.IndTexSrt:
                    return AnimationDefine.SIGNATURE_ANMINDTEXSRT;

                default:
                    throw new OperationException("Invalid animation info kind");
            }
        }
    }
}
