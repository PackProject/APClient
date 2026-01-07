using LibWorkBench.API.JSystem.JMessage;
using LibWorkBench.Exceptions;
using LibWorkBench.Formats.JSystem.Details;
using LibWorkBench.Formats.JSystem.JMessage.MsgRes.Binary;
using LibWorkBench.Formats.JSystem.JMessage.MsgRes.Binary.Blocks;
using LibWorkBench.Formats.JSystem.JMessage.MsgRes.Types;
using LibWorkBench.Formats.JSystem.JMessage.Utility;
using LibWorkBench.IO.Streams;

namespace LibWorkBench.Formats.JSystem.JMessage.MsgRes.Data
{
    /// <summary>
    /// MsgRes data-view model
    /// </summary>
    public sealed class MsgResDataModel : TJSystemDataModel<MsgResFile>
    {
        /// <summary>
        /// Text encoding format used by this model
        /// </summary>
        public TextEncoding Encoding { get; set; } = TextEncoding.UTF16;

        /// <summary>
        /// Message info group ID
        /// </summary>
        public ushort GroupID { get; set; } = 0;

        /// <summary>
        /// Message ID format
        /// </summary>
        public Form Form { get; set; } = Form.Main;

        /// <summary>
        /// Message ID supplemental format
        /// </summary>
        public FormSupplement FormSupplement { get; set; } = FormSupplement.Group24;

        /// <summary>
        /// Messages contained in this model
        /// </summary>
        public List<Message> Messages { get; set; } = new();

        /// <summary>
        /// Deserializes the contents of this model from a file
        /// </summary>
        /// <param name="reader">Stream to the JSON file</param>
        public override void Load(JsonFileReader reader)
        {
            Messages.Clear();

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
        public override void OnSync(JSystemBinaryModel binaryModel)
        {
            MsgResBinaryModel src = (MsgResBinaryModel)binaryModel;

            MsgInfoBlock msgInfo = src.GetOne<MsgInfoBlock>();
            MsgDataBlock msgData = src.GetOne<MsgDataBlock>();
            MsgIDBlock msgID = src.GetOne<MsgIDBlock>();

            Encoding = src.Encoding;
            GroupID = msgInfo.GroupID;
            Form = msgID.Form;
            FormSupplement = msgID.FormSupplement;

            Messages.Clear();

            // Message info should always line up with the ID table
            if (msgInfo.Contents.Count != msgID.Contents.Count)
            {
                throw new FileBrokenException("Message count mismatch");
            }

            for (int i = 0; i < msgInfo.Contents.Count; i++)
            {
                MsgInfoBlock.Entry entry = msgInfo.Contents[i];

                uint group, index;
                MessageUtil.SplitID(msgID.Contents[i], FormSupplement,
                                    out group, out index);

                Messages.Add(new(
                    group, index,
                    text: msgData.Contents[entry.Offset],
                    attributes: entry.Attributes,
                    exAttributes: entry.ExAttributes
                ));
            }
        }
    }
}
