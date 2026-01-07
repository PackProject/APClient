using LibWorkBench.API.Pack;
using LibWorkBench.Attributes;
using LibWorkBench.Formats.JSystem;
using LibWorkBench.Formats.JSystem.JMessage.MsgRes.Binary;
using LibWorkBench.Formats.JSystem.JMessage.MsgRes.Data;
using LibWorkBench.Formats.JSystem.JMessage.MsgRes.Types;
using LibWorkBench.Formats.JSystem.JMessage.Tag;

namespace LibWorkBench.API.JSystem.JMessage
{
    /// <summary>
    /// Message resource (BMG)
    /// </summary>
    [ResourceProfile(name: "msgres", extension: "bmg")]
    public sealed class MsgResFile : TJSystemResource<MsgResBinaryModel, MsgResDataModel>
    {
        /// <summary>
        /// Tag processor to use for special character sequences in messages
        /// </summary>
        public TagProcessorBase TagProcessor { get; set; } = new RPSysTagProcessor();

        /// <summary>
        /// Text encoding format
        /// </summary>
        public TextEncoding Encoding
        {
            get => DataModel.Encoding;
            set { DataModel.Encoding = value; }
        }

        /// <summary>
        /// Message info group ID
        /// </summary>
        public ushort GroupID
        {
            get => DataModel.GroupID;
            set { DataModel.GroupID = value; }
        }

        /// <summary>
        /// Message ID format
        /// </summary>
        public Form Form
        {
            get => DataModel.Form;
            set { DataModel.Form = value; }
        }

        /// <summary>
        /// Message ID supplemental format
        /// </summary>
        public FormSupplement FormSupplement
        {
            get => DataModel.FormSupplement;
            set { DataModel.FormSupplement = value; }
        }

        /// <summary>
        /// Messages contained within this resource
        /// </summary>
        public List<Message> Messages => DataModel.Messages;
    }
}
