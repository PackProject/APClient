using LibWorkBench.Attributes;
using LibWorkBench.Exceptions;
using LibWorkBench.Formats.JSystem.Details;
using LibWorkBench.Formats.JSystem.JMessage.MsgRes.Data;
using LibWorkBench.IO.Streams;
using LibWorkBench.Utility;

namespace LibWorkBench.Formats.JSystem.JMessage.MsgRes.Binary.Blocks
{
    /// <summary>
    /// MsgRes message info block
    /// </summary>
    [BinaryBlockProfile(signature: "INF1")]
    public sealed class MsgInfoBlock : TJSystemBinaryBlock<MsgResBinaryModel>
    {
        /// <summary>
        /// Minimum entry size (must include offset & attribute)
        /// </summary>
        private const int ENTRY_SIZE_MIN = 8;

        /// <summary>
        /// Message info block entry
        /// </summary>
        public sealed class Entry
        {
            /// <summary>
            /// Offset into the message data block
            /// </summary>
            public uint Offset = 0;

            /// <summary>
            /// Message attributes
            /// </summary>
            public uint Attributes = 0;

            /// <summary>
            /// Message extra attributes (per user spec.)
            /// </summary>
            public byte[] ExAttributes = [];

            /// <summary>
            /// Constructor
            /// </summary>
            /// <param name="offset">Offset into the message data block</param>
            /// <param name="attributes">Message attributes</param>
            /// <param name="exAttributes">Message extra attributes (per user spec.)</param>
            public Entry(uint offset, uint attributes, byte[] exAttributes)
            {
                Offset = offset;
                Attributes = attributes;
                ExAttributes = exAttributes;
            }
        }

        /// <summary>
        /// Message info group ID
        /// </summary>
        public ushort GroupID { get; set; } = 0;

        /// <summary>
        /// Message info contents
        /// </summary>
        public List<Entry> Contents { get; set; } = new();

        /// <summary>
        /// Deserializes the contents of this object from a file (derived implementation)
        /// </summary>
        /// <param name="reader">Binary stream to the file</param>
        public override void DoRead(ReadStream reader)
        {
            Contents.Clear();

            ushort entryNum = reader.ReadU16();
            ushort entrySize = reader.ReadU16();

            if (entrySize % 4 != 0)
            {
                throw new FileBrokenException(
                    "Message info entry size must be aligned to 4 bytes");
            }

            if (entrySize < ENTRY_SIZE_MIN)
            {
                throw new FileBrokenException("Message info entry size is too small");
            }

            GroupID = reader.ReadU16();
            reader.Align(4);

            // Block data is a table of these entries
            for (uint i = 0; i < entryNum; i++)
            {
                uint offset = reader.ReadU32();
                uint attributes = reader.ReadU32();

                // Message tools allow custom attributes
                uint exSize = (uint)(entrySize - ENTRY_SIZE_MIN);
                byte[] exAttributes = reader.Read(exSize);

                Contents.Add(new(offset, attributes, exAttributes));
            }
        }

        /// <summary>
        /// Serializes the contents of this object to a file (derived implementation)
        /// </summary>
        /// <param name="writer">Binary stream to the file</param>
        /// <exception cref="FileBrokenException">There are too many messages</exception>
        public override void DoWrite(WriteStream writer)
        {
            if (Contents.Count > ushort.MaxValue)
            {
                throw new FileBrokenException("Too many messages");
            }

            if (Contents.Any(it =>
                it.ExAttributes.Length != Contents.First().ExAttributes.Length))
            {
                throw new FileBrokenException("Ex-attribute size mismatch");
            }

            ushort entryNum = (ushort)Contents.Count;
            ushort entrySize = ENTRY_SIZE_MIN;

            // Include ex-attributes in the entry size
            if (entryNum > 0)
            {
                entrySize += (ushort)Contents.First().ExAttributes.Length;
                entrySize = Util.RoundUp(entrySize, 4);
            }

            writer.WriteU16(entryNum);
            writer.WriteU16(entrySize);
            writer.WriteU16(GroupID);
            writer.Align(4);

            foreach (var it in Contents)
            {
                writer.WriteU32(it.Offset);
                writer.WriteU32(it.Attributes);

                writer.Write(it.ExAttributes);
                writer.Align(4);
            }
        }

        /// <summary>
        /// Updates this block to match the contents of the data-view model (derived implementation)
        /// </summary>
        /// <param name="dataModel">Data-view model</param>
        public override void DoSync(JSystemDataModel dataModel)
        {
            MsgResDataModel src = (MsgResDataModel)dataModel;

            MsgDataBlock msgData = Model!.GetOne<MsgDataBlock>();

            GroupID = src.GroupID;

            Contents.Clear();

            foreach (var it in src.Messages)
            {
                Contents.Add(new(
                    msgData.ContentsInv[it.Text],
                    it.Attributes,
                    it.ExAttributes
                ));
            }
        }
    }
}
