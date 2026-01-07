using LibWorkBench.API.JSystem.JMessage;
using LibWorkBench.Attributes;
using LibWorkBench.Exceptions;
using LibWorkBench.Formats.JSystem.Details;
using LibWorkBench.Formats.JSystem.JMessage.MsgRes.Binary.Blocks;
using LibWorkBench.Formats.JSystem.JMessage.MsgRes.Data;
using LibWorkBench.Formats.JSystem.JMessage.MsgRes.Types;
using LibWorkBench.IO.Streams;

namespace LibWorkBench.Formats.JSystem.JMessage.MsgRes.Binary
{
    /// <summary>
    /// MsgRes binary-view model
    /// </summary>
    [BinaryModelProfile(
        signature: "MESGbmg1",
        alignment: JSystemDefine.BLOCK_ALIGNMENT
    )]
    public sealed class MsgResBinaryModel
        : TJSystemBinaryModel<MsgResFile, MsgResBlockFactory>
    {
        /// <summary>
        /// Text encoding format used by this model
        /// </summary>
        public TextEncoding Encoding { get; set; } = TextEncoding.UTF16;

        /// <summary>
        /// Deserializes the contents of this model from a file (derived implementation)
        /// </summary>
        /// <param name="reader">Binary stream to the file</param>
        public override void OnRead(ReadStream reader)
        {
            Encoding = (TextEncoding)reader.ReadU8();

            // GC-era files are known to use Undefined sometimes
            if (Encoding == TextEncoding.Undefined)
            {
                Encoding = TextEncoding.CP1252;
            }

            // TODO(kiwi) Streams need to support Shift-JIS
            if (Encoding == TextEncoding.SJIS)
            {
                throw new FileNotSupportedException(
                    "Shift-JIS not yet supported");
            }
        }

        /// <summary>
        /// Serializes the contents of this model to a file (derived implementation)
        /// </summary>
        /// <param name="writer">Binary stream to the file</param>
        public override void OnWrite(WriteStream writer)
        {
            writer.WriteU8((byte)Encoding);
        }

        /// <summary>
        /// Updates this model to match the contents of the data-view model
        /// </summary>
        /// <param name="dataModel">Data-view model</param>
        public override void OnSync(JSystemDataModel dataModel)
        {
            MsgResDataModel src = (MsgResDataModel)dataModel;

            Encoding = src.Encoding;

            // Create any missing blocks in the order they should be written
            MsgInfoBlock msgInfo = GetOne<MsgInfoBlock>(create: true);
            MsgDataBlock msgData = GetOne<MsgDataBlock>(create: true);
            MsgIDBlock msgId = GetOne<MsgIDBlock>(create: true);

            // Sync string pool first to allow deduplication
            msgData.Sync(src);
            msgInfo.Sync(src);
            msgId.Sync(src);
        }
    }
}
