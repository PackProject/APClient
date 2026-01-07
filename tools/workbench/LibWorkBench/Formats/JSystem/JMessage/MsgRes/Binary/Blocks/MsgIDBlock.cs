using LibWorkBench.Attributes;
using LibWorkBench.Exceptions;
using LibWorkBench.Formats.JSystem.Details;
using LibWorkBench.Formats.JSystem.JMessage.MsgRes.Data;
using LibWorkBench.Formats.JSystem.JMessage.MsgRes.Types;
using LibWorkBench.Formats.JSystem.JMessage.Utility;
using LibWorkBench.IO.Streams;

namespace LibWorkBench.Formats.JSystem.JMessage.MsgRes.Binary.Blocks
{
    /// <summary>
    /// MsgRes message ID block
    /// </summary>
    [BinaryBlockProfile(signature: "MID1")]
    public sealed class MsgIDBlock : TJSystemBinaryBlock<MsgResBinaryModel>
    {
        /// <summary>
        /// Message ID format
        /// </summary>
        public Form Form { get; set; } = Form.Main;

        /// <summary>
        /// Message ID supplemental format
        /// </summary>
        public FormSupplement FormSupplement { get; set; } = FormSupplement.Group24;

        /// <summary>
        /// Message ID contents (list of IDs)
        /// </summary>
        public List<uint> Contents { get; set; } = new();

        /// <summary>
        /// Deserializes the contents of this object from a file (derived implementation)
        /// </summary>
        /// <param name="reader">Binary stream to the file</param>
        public override void DoRead(ReadStream reader)
        {
            ushort entryNum = reader.ReadU16();

            // Should always be 1:1 with the info table
            MsgInfoBlock msgInfo = Model!.GetOne<MsgInfoBlock>();
            if (entryNum != msgInfo.Contents.Count)
            {
                throw new FileBrokenException("Message ID block is too small");
            }

            // Upper 4 bits is whether IDs are stored in sorted order,
            // lower 4 bits is the message ID format
            byte packed = reader.ReadU8();
            bool isOrdered = (packed & 0xF0) != 0;
            byte form = (byte)(packed & 0x0F);

            Form = (Form)form;
            FormSupplement = (FormSupplement)reader.ReadU8();

            // Padding/unknown data
            reader.Skip(4);

            for (uint i = 0; i < entryNum; i++)
            {
                Contents.Add(reader.ReadU32());
            }
        }

        /// <summary>
        /// Serializes the contents of this object to a file (derived implementation)
        /// </summary>
        /// <param name="writer">Binary stream to the file</param>
        public override void DoWrite(WriteStream writer)
        {
            if (Contents.Count > ushort.MaxValue)
            {
                throw new FileBrokenException("Too many message IDs");
            }

            writer.WriteU16((ushort)Contents.Count);

            // Always clear the isOrdered bit since EGG ignores it
            writer.WriteU8((byte)Form);
            writer.WriteU8((byte)FormSupplement);

            // Padding/unknown data
            writer.Skip(4);

            // Write message IDs
            Contents.ForEach(writer.WriteU32);
        }

        /// <summary>
        /// Updates this block to match the contents of the data-view model (derived implementation)
        /// </summary>
        /// <param name="dataModel">Data-view model</param>
        public override void DoSync(JSystemDataModel dataModel)
        {
            MsgResDataModel src = (MsgResDataModel)dataModel;

            Form = src.Form;
            FormSupplement = src.FormSupplement;

            Contents.Clear();

            Contents = src.Messages.Select(it =>
                MessageUtil.JoinID(FormSupplement, it.Group, it.Index)).ToList();
        }
    }
}
