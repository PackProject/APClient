using LibWorkBench.Core;
using LibWorkBench.IO.Streams;
using LibWorkBench.Formats.NW4R.LayoutLib.Animation.Types;
using System.Text.Json.Serialization;

namespace LibWorkBench.Formats.NW4R.LayoutLib.Animation.Types.Details
{
    /// <summary>
    /// Base class for layout animation targets
    /// </summary>
    [JsonPolymorphic(TypeDiscriminatorPropertyName = "kind")]
    [JsonDerivedType(typeof(AnimationTargetPaneSrt), typeDiscriminator: "pane_srt")]
    [JsonDerivedType(typeof(AnimationTargetPaneVis), typeDiscriminator: "pane_vis")]
    [JsonDerivedType(typeof(AnimationTargetVtxClr), typeDiscriminator: "vertex_color")]
    [JsonDerivedType(typeof(AnimationTargetMatClr), typeDiscriminator: "material_color")]
    [JsonDerivedType(typeof(AnimationTargetTexSrt), typeDiscriminator: "texture_srt")]
    [JsonDerivedType(typeof(AnimationTargetTexPat), typeDiscriminator: "texture_pattern")]
    [JsonDerivedType(typeof(AnimationTargetIndTexSrt), typeDiscriminator: "indirect_texture_srt")]
    public abstract class AnimationTargetImpl : IUseBinary
    {
        /// <summary>
        /// Target element index
        /// </summary>
        [JsonPropertyOrder(int.MinValue)]
        public byte TargetID { get; set; } = 0;

        /// <summary>
        /// Deserializes the contents of this object from a file
        /// </summary>
        /// <param name="reader">Binary stream to the file</param>
        public abstract void Read(ReadStream reader);

        /// <summary>
        /// Serializes the contents of this object to a file
        /// </summary>
        /// <param name="writer">Binary stream to the file</param>
        public abstract void Write(WriteStream writer);
    }
}
