using LibWorkBench.Core;
using LibWorkBench.IO.Streams;

namespace LibWorkBench.Formats.JSystem.Details
{
    /// <summary>
    /// Binary header for JSYSTEM resources
    /// </summary>
    public sealed class JSystemBinaryFileHeader : IUseBinary
    {
        /// <summary>
        /// Signature/"magic" of this file
        /// </summary>
        public string Signature { get; set; } = "";

        /// <summary>
        /// Size of this resource file, in bytes
        /// </summary>
        public uint FileSize { get; set; } = 0;

        /// <summary>
        /// Number of data blocks contained within this file
        /// </summary>
        public uint DataBlocks { get; set; } = 0;

        /// <summary>
        /// Deserializes the contents of this object from a file
        /// </summary>
        /// <param name="reader">Binary stream to the file</param>
        public void Read(ReadStream reader)
        {
            Signature = reader.ReadString(
                maxlen: JSystemDefine.HEADER_SIGNATURE_LENGTH
            );

            FileSize = reader.ReadU32();
            DataBlocks = reader.ReadU32();
        }

        /// <summary>
        /// Serializes the contents of this object to a file
        /// </summary>
        /// <param name="writer">Binary stream to the file</param>
        public void Write(WriteStream writer)
        {
            writer.WriteString(
                Signature,
                maxlen: JSystemDefine.HEADER_SIGNATURE_LENGTH,
                terminate: false
            );

            writer.WriteU32(FileSize);
            writer.WriteU32(DataBlocks);
        }
    }
}
