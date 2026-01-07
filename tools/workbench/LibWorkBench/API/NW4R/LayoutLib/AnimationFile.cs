using LibWorkBench.Attributes;
using LibWorkBench.Formats.NW4R;
using LibWorkBench.Formats.NW4R.LayoutLib.Animation.Binary;
using LibWorkBench.Formats.NW4R.LayoutLib.Animation.Data;

namespace LibWorkBench.API.NW4R.LayoutLib
{
    /// <summary>
    /// Layout animation file (BRLAN)
    /// </summary>
    [ResourceProfile(name: "lytanim", extension: "brlan")]
    public sealed class AnimationFile : TNW4RResource<AnimationBinaryModel, AnimationDataModel>
    {
    }
}
