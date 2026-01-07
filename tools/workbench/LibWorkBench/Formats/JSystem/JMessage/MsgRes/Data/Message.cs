using LibWorkBench.Converters;
using System.Text.Json.Serialization;

namespace LibWorkBench.Formats.JSystem.JMessage.MsgRes.Data
{
    /// <summary>
    /// API representation of a single message
    /// </summary>
    public class Message
    {
        /// <summary>
        /// Message group ID
        /// </summary>
        public uint Group { get; set; } = 0;

        /// <summary>
        /// Message index within its group
        /// </summary>
        public uint Index { get; set; } = 0;

        /// <summary>
        /// Message text string
        /// </summary>
        public string Text { get; set; } = "";

        /// <summary>
        /// Message attributes
        /// </summary>
        [JsonConverter(typeof(HexUInt32JsonConverter))]
        public uint Attributes { get; set; } = 0;

        /// <summary>
        /// Message extra attributes (per user spec.)
        /// </summary>
        [JsonConverter(typeof(HexByteArrayJsonConverter))]
        public byte[] ExAttributes { get; set; } = [];

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="group">Group ID</param>
        /// <param name="index">Index</param>
        /// <param name="text">Text string</param>
        /// <param name="attributes">Message attributes</param>
        /// <param name="exAttributes">Extra attributes (per user spec.)</param>
        public Message(uint group, uint index, string text, uint attributes,
                       byte[] exAttributes)
        {
            Group = group;
            Index = index;
            Text = text;
            Attributes = attributes;
            ExAttributes = exAttributes;
        }
    }
}
