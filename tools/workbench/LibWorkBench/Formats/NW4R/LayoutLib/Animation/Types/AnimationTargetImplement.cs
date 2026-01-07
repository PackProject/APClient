using LibWorkBench.Formats.NW4R.LayoutLib.Animation.Types.Details;

namespace LibWorkBench.Formats.NW4R.LayoutLib.Animation.Types
{
    /// <summary>
    /// Pane S/R/T transformation animation target
    /// </summary>
    public sealed class AnimationTargetPaneSrt
        : AnimationTarget<AnimTargetElementPaneSrt, HermiteKey>
    {
    }

    /// <summary>
    /// Pane visibility animation target
    /// </summary>
    public sealed class AnimationTargetPaneVis
        : AnimationTarget<AnimTargetElementPaneVis, StepKey>
    {
    }

    /// <summary>
    /// Pane vertex color animation target
    /// </summary>
    public sealed class AnimationTargetVtxClr
        : AnimationTarget<AnimTargetElementVtxClr, HermiteKey>
    {
    }

    /// <summary>
    /// Pane material color animation target
    /// </summary>
    public sealed class AnimationTargetMatClr
        : AnimationTarget<AnimTargetElementMatClr, HermiteKey>
    {
    }

    /// <summary>
    /// Pane texture S/R/T transformation animation target
    /// </summary>
    public sealed class AnimationTargetTexSrt
        : AnimationTarget<AnimTargetElementTexSrt, HermiteKey>
    {
    }

    /// <summary>
    /// Pane texture pattern animation target
    /// </summary>
    public sealed class AnimationTargetTexPat
        : AnimationTarget<AnimTargetElementTexPat, StepKey>
    {
    }

    /// <summary>
    /// Pane indirect texture S/R/T transformation animation target
    /// </summary>
    public sealed class AnimationTargetIndTexSrt
        : AnimationTarget<AnimTargetElementTexSrt, HermiteKey>
    {
    }
}
