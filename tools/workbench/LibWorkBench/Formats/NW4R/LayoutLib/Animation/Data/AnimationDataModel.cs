using LibWorkBench.API.NW4R.LayoutLib;
using LibWorkBench.Formats.NW4R.Details;
using LibWorkBench.Formats.NW4R.LayoutLib.Animation.Binary;
using LibWorkBench.Formats.NW4R.LayoutLib.Animation.Binary.Blocks;
using LibWorkBench.IO.Streams;

namespace LibWorkBench.Formats.NW4R.LayoutLib.Animation.Data
{
    /// <summary>
    /// Layout animation data-view model
    /// </summary>
    public sealed class AnimationDataModel : TNW4RDataModel<AnimationFile>
    {
        /// <summary>
        /// Number of frames in this animation
        /// </summary>
        public ushort Length { get; set; } = 0;

        /// <summary>
        /// Whether this animation should loop
        /// </summary>
        public bool Loop { get; set; } = false;

        /// <summary>
        /// Names of all texture resources required by this animation
        /// </summary>
        public List<string> TextureNames { get; set; } = new();

        /// <summary>
        /// Animation contents
        /// </summary>
        public List<AnimationContent> Contents { get; set; } = new();

        /// <summary>
        /// Deserializes the contents of this model from a file
        /// </summary>
        /// <param name="reader">Stream to the JSON file</param>
        public override void Load(JsonFileReader reader)
        {
            reader.Deserialize(this);
        }

        /// <summary>
        /// Serializes the contents of this model to a file
        /// </summary>
        /// <param name="writer">Stream to the JSON file</param>
        public override void Dump(JsonFileWriter writer)
        {
            writer.Serialize(this);
        }

        /// <summary>
        /// Updates this model to match the contents of the binary-view model
        /// </summary>
        /// <param name="binaryModel">Binary-view model</param>
        public override void OnSync(NW4RBinaryModel binaryModel)
        {
            AnimationBinaryModel src = (AnimationBinaryModel)binaryModel;

            AnimationInfoBlock animInfo = src.GetOne<AnimationInfoBlock>();
            Length = animInfo.Length;
            Loop = animInfo.Loop;
            Contents = animInfo.Contents;
            TextureNames = animInfo.TextureNames;
        }
    }
}