using LibWorkBench.Core;
using LibWorkBench.IO.Streams;
using LibWorkBench.Formats.JSystem;

namespace LibWorkBench.Formats.JSystem.Details
{
    /// <summary>
    /// Binary header for JSYSTEM blocks
    /// </summary>
    public sealed class JSystemBinaryBlockHeader : IUseBinary
    {
        /// <summary>
        /// Signature/"magic" associated with this binary block
        /// </summary>
        public string Signature { get; set; } = "";

        /// <summary>
        /// Size of this binary block, in bytes
        /// </summary>
        public uint Size { get; set; } = 0;

        /// <summary>
        /// Deserializes the contents of this object from a file
        /// </summary>
        /// <param name="reader">Binary stream to the file</param>
        public void Read(ReadStream reader)
        {
            Signature = reader.ReadString(
                maxlen: JSystemDefine.BLOCK_SIGNATURE_LENGTH,
                exact: true
            );

            Size = reader.ReadU32();
        }

        /// <summary>
        /// Serializes the contents of this object to a file
        /// </summary>
        /// <param name="writer">Binary stream to the file</param>
        public void Write(WriteStream writer)
        {
            writer.WriteString(
                Signature,
                maxlen: JSystemDefine.BLOCK_SIGNATURE_LENGTH,
                terminate: false,
                exact: true
            );

            writer.WriteU32(Size);
        }
    }
}
