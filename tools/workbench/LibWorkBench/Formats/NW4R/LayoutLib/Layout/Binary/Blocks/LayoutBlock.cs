using LibWorkBench.Attributes;
using LibWorkBench.IO.Streams;
using LibWorkBench.Formats.NW4R;
using LibWorkBench.Formats.NW4R.LayoutLib.Layout.Binary;
using LibWorkBench.Formats.NW4R.LayoutLib.Layout.Data;
using LibWorkBench.Formats.NW4R.LayoutLib.Layout.Types;
using LibWorkBench.Core.Models.Data;

namespace LibWorkBench.Formats.NW4R.LayoutLib.Layout.Binary.Blocks
{
    /// <summary>
    /// Layout main block
    /// </summary>
    [BinaryBlockProfile(signature: "lyt1")]
    public class LayoutBlock : TNW4RBinaryBlock<LayoutBinaryModel>
    {
        /// <summary>
        /// Position origin type
        /// </summary>
        public OriginType OriginType { get; set; } = OriginType.TopLeft;

        /// <summary>
        /// Size of this layout
        /// </summary>
        public Size Size { get; set; } = new();

        /// <summary>
        /// Deserializes the contents of this object from a file (derived implementation)
        /// </summary>
        /// <param name="reader">Binary stream to the file</param>
        public override void DoRead(ReadStream reader)
        {
            OriginType = (OriginType)reader.ReadU8();
            reader.Align(4);

            Size.Read(reader);
        }

        /// <summary>
        /// Serializes the contents of this object to a file (derived implementation)
        /// </summary>
        /// <param name="writer">Binary stream to the file</param>
        public override void DoWrite(WriteStream writer)
        {
            writer.WriteU8((byte)OriginType);
            writer.Align(4);

            Size.Write(writer);
        }

        /// <summary>
        /// Updates this block to match the contents of the data-view model (derived implementation)
        /// </summary>
        /// <param name="dataModel">Data-view model</param>
        public override void DoSync(NW4RDataModel dataModel)
        {
            LayoutDataModel src = (LayoutDataModel)dataModel;

            OriginType = src.OriginType;
            Size = src.Size;
        }
    }
}
