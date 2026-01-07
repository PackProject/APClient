using LibWorkBench.Attributes;
using LibWorkBench.Exceptions;
using LibWorkBench.IO.Streams;
using LibWorkBench.Formats.NW4R;
using LibWorkBench.Formats.NW4R.LayoutLib.Layout.Binary;
using LibWorkBench.Core.Models.Data;

namespace LibWorkBench.Formats.NW4R.LayoutLib.Layout.Binary.Blocks
{
    /// <summary>
    /// Layout userdata block
    /// </summary>
    [BinaryBlockProfile(signature: "usd1")]
    public class UserDataBlock : TNW4RBinaryBlock<LayoutBinaryModel>
    {
        /// <summary>
        /// Deserializes the contents of this object from a file (derived implementation)
        /// </summary>
        /// <param name="reader">Binary stream to the file</param>
        public override void DoRead(ReadStream reader)
        {
            throw new FileNotSupportedException(
                "Userdata block is not yet supported");
        }

        /// <summary>
        /// Serializes the contents of this object to a file (derived implementation)
        /// </summary>
        /// <param name="writer">Binary stream to the file</param>
        public override void DoWrite(WriteStream writer)
        {
            throw new FileNotSupportedException(
                "Userdata block is not yet supported");
        }

        /// <summary>
        /// Updates this block to match the contents of the data-view model (derived implementation)
        /// </summary>
        /// <param name="dataModel">Data-view model</param>
        public override void DoSync(NW4RDataModel dataModel)
        {
            throw new FileNotSupportedException(
                "Userdata block is not yet supported");
        }
    }
}
