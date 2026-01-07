using LibWorkBench.Core;
using LibWorkBench.IO.Streams;
using LibWorkBench.Formats.NW4R;

namespace LibWorkBench.Formats.NW4R.Details
{
    /// <summary>
    /// Binary header for NW4R resources
    /// </summary>
    public sealed class NW4RBinaryFileHeader : IUseBinary
    {
        /// <summary>
        /// Size of this structure when saved in binary form
        /// </summary>
        public const int STRUCT_SIZE = 16;

        /// <summary>
        /// Signature/"magic" of this file
        /// </summary>
        public string Signature { get; set; } = "";

        /// <summary>
        /// Byte-order/endianness of this file
        /// </summary>
        public ByteOrder ByteOrder { get; set; } = ByteOrder.Big;

        /// <summary>
        /// Version of this file's specification
        /// </summary>
        public ushort Version { get; set; } = 0;

        /// <summary>
        /// Size of this file, in bytes
        /// </summary>
        public uint FileSize { get; set; } = 0;

        /// <summary>
        /// Size of this file's header, in bytes
        /// </summary>
        public ushort HeaderSize { get; set; } = 0;

        /// <summary>
        /// Number of data blocks contained within this file
        /// </summary>
        public ushort DataBlocks { get; set; } = 0;

        /// <summary>
        /// Deserializes the contents of this object from a file
        /// </summary>
        /// <param name="reader">Binary stream to the file</param>
        public void Read(ReadStream reader)
        {
            Signature = reader.ReadString(
                maxlen: NW4RDefine.HEADER_SIGNATURE_LENGTH,
                exact: true
            );

            ByteOrder = (ByteOrder)reader.ReadU16();
            Version = reader.ReadU16();
            FileSize = reader.ReadU32();
            HeaderSize = reader.ReadU16();
            DataBlocks = reader.ReadU16();
        }

        /// <summary>
        /// Serializes the contents of this object to a file
        /// </summary>
        /// <param name="writer">Binary stream to the file</param>
        public void Write(WriteStream writer)
        {
            writer.WriteString(
                Signature,
                maxlen: NW4RDefine.HEADER_SIGNATURE_LENGTH,
                terminate: false,
                exact: true
            );

            writer.WriteU16((ushort)ByteOrder);
            writer.WriteU16(Version);
            writer.WriteU32(FileSize);
            writer.WriteU16(HeaderSize);
            writer.WriteU16(DataBlocks);
        }
    }
}
