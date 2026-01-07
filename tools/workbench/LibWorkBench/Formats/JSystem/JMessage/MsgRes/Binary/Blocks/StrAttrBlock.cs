using LibWorkBench.Attributes;
using LibWorkBench.Exceptions;
using LibWorkBench.Formats.JSystem.Details;
using LibWorkBench.IO.Streams;

namespace LibWorkBench.Formats.JSystem.JMessage.MsgRes.Binary.Blocks
{
    /// <summary>
    /// MsgRes string attribute block
    /// </summary>
    [BinaryBlockProfile(signature: "STR1")]
    public sealed class StrAttrBlock : TJSystemBinaryBlock<MsgResBinaryModel>
    {
        /// <summary>
        /// Deserializes the contents of this object from a file (derived implementation)
        /// </summary>
        /// <param name="reader">Binary stream to the file</param>
        public override void DoRead(ReadStream reader)
        {
            throw new FileNotSupportedException(
                "StrAttr block is not yet supported");
        }

        /// <summary>
        /// Serializes the contents of this object to a file (derived implementation)
        /// </summary>
        /// <param name="writer">Binary stream to the file</param>
        public override void DoWrite(WriteStream writer)
        {
            throw new FileNotSupportedException(
                "StrAttr block is not yet supported");
        }

        /// <summary>
        /// Updates this block to match the contents of the data-view model (derived implementation)
        /// </summary>
        /// <param name="dataModel">Data-view model</param>
        public override void DoSync(JSystemDataModel dataModel)
        {
            throw new FileNotSupportedException(
                "StrAttr block is not yet supported");
        }
    }
}
