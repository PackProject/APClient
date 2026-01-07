using LibWorkBench.API.NW4R.LayoutLib;
using LibWorkBench.Attributes;
using LibWorkBench.IO.Streams;

namespace LibWorkBench.Formats.NW4R.LayoutLib.Animation.Binary
{
    /// <summary>
    /// Layout animation binary-view model
    /// </summary>
    [BinaryModelProfile(
        signature: "RLAN",
        versions: [8, 10],
        alignment: NW4RDefine.BLOCK_ALIGNMENT
    )]
    public sealed class AnimationBinaryModel
        : TNW4RBinaryModel<AnimationFile, AnimationBlockFactory>
    {
        /// <summary>
        /// Deserializes the contents of this model from a file (derived implementation)
        /// </summary>
        /// <param name="reader">Binary stream to the file</param>
        public override void OnRead(ReadStream reader)
        {
        }

        /// <summary>
        /// Serializes the contents of this model to a file (derived implementation)
        /// </summary>
        /// <param name="writer">Binary stream to the file</param>
        public override void OnWrite(WriteStream writer)
        {
        }

        /// <summary>
        /// Updates this model to match the contents of the data-view model
        /// </summary>
        /// <param name="dataModel">Data-view model</param>
        public override void OnSync(NW4RDataModel dataModel)
        {
        }
    }
}
