using LibWorkBench.Attributes;
using LibWorkBench.Exceptions;
using LibWorkBench.Formats.JSystem.Details;
using LibWorkBench.Formats.JSystem.JMessage.MsgRes.Data;
using LibWorkBench.Formats.JSystem.JMessage.Tag;
using LibWorkBench.IO.Streams;

namespace LibWorkBench.Formats.JSystem.JMessage.MsgRes.Binary.Blocks
{
    /// <summary>
    /// MsgRes message data block
    /// </summary>
    [BinaryBlockProfile(signature: "DAT1")]
    public sealed class MsgDataBlock : TJSystemBinaryBlock<MsgResBinaryModel>
    {
        /// <summary>
        /// Mapping of message offsets to strings
        /// </summary>
        public OrderedDictionary<uint, string> Contents { get; set; } = new();

        /// <summary>
        /// Mapping of message strings to offsets
        /// </summary>
        public Dictionary<string, uint> ContentsInv { get; set; } = new();

        /// <summary>
        /// Deserializes the contents of this object from a file (derived implementation)
        /// </summary>
        /// <param name="reader">Binary stream to the file</param>
        public override void DoRead(ReadStream reader)
        {
            Contents.Clear();

            // Dummy empty string, so an offset of zero is valid
            Contents[0] = "";

            // Message info offsets are relative to the stream position
            ulong startOffset = reader.Position;

            // Use message info to determine the string boundaries
            MsgInfoBlock msgInfo = Model!.GetOne<MsgInfoBlock>();
            foreach (var info in msgInfo.Contents)
            {
                // Multiple messages can point at the same string
                if (Contents.ContainsKey(info.Offset))
                {
                    continue;
                }

                // Ignore the empty string (we manage this ourselves)
                if (info.Offset == 0)
                {
                    continue;
                }

                if (info.Offset + startOffset >= reader.Length)
                {
                    throw new FileBrokenException("Message offset is invalid");
                }

                reader.Seek((long)(info.Offset + startOffset), SeekOrigin.Begin);

                // Convert any tag sequences to human-readable text
                string s = Model!.Resource!.TagProcessor.Decode(reader, Model.Encoding);

                Contents[info.Offset] = s;
                ContentsInv[s] = info.Offset;
            }
        }

        /// <summary>
        /// Serializes the contents of this object to a file (derived implementation)
        /// </summary>
        /// <param name="writer">Binary stream to the file</param>
        public override void DoWrite(WriteStream writer)
        {
            foreach (var it in Contents.Values)
            {
                Model!.Resource!.TagProcessor.Encode(writer, Model.Encoding, it);
            }
        }

        /// <summary>
        /// Updates this block to match the contents of the data-view model (derived implementation)
        /// </summary>
        /// <param name="dataModel">Data-view model</param>
        public override void DoSync(JSystemDataModel dataModel)
        {
            MsgResDataModel src = (MsgResDataModel)dataModel;
            TagProcessorBase tagPro = Model!.Resource!.TagProcessor;

            Contents.Clear();
            ContentsInv.Clear();

            // Calculate running offset for each string
            ulong offset = 0;

            // Always hold the empty string at offset zero
            Contents[0] = "";
            ContentsInv[""] = 0;
            offset += tagPro.CalcStringSize(src.Encoding, "");

            foreach (var it in src.Messages)
            {
                if (offset > uint.MaxValue)
                {
                    throw new FileBrokenException(
                        "Message data is too big (over 32-bit limit)");
                }

                // Duplicate strings only waste space
                if (ContentsInv.ContainsKey(it.Text))
                {
                    continue;
                }

                Contents[(uint)offset] = it.Text;
                ContentsInv[it.Text] = (uint)offset;

                offset += tagPro.CalcStringSize(src.Encoding, it.Text);
            }
        }
    }
}
