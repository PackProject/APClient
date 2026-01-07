using LibWorkBench.Core;
using LibWorkBench.IO.Streams;

namespace LibWorkBench.Formats.Revolution.GX.Types
{
    /// <summary>
    /// 8-bit RGBA color
    /// </summary>
    public sealed class GXColor : IUseBinary
    {
        /// <summary>
        /// Red component
        /// </summary>
        public byte R { get; set; } = 0;

        /// <summary>
        /// Green component
        /// </summary>
        public byte G { get; set; } = 0;

        /// <summary>
        /// Blue component
        /// </summary>
        public byte B { get; set; } = 0;

        /// <summary>
        /// Alpha component
        /// </summary>
        public byte A { get; set; } = 0;

        /// <summary>
        /// Deserializes the contents of this object from a file
        /// </summary>
        /// <param name="reader">Binary stream to the file</param>
        public void Read(ReadStream reader)
        {
            R = reader.ReadU8();
            G = reader.ReadU8();
            B = reader.ReadU8();
            A = reader.ReadU8();
        }

        /// <summary>
        /// Serializes the contents of this object to a file
        /// </summary>
        /// <param name="writer">Binary stream to the file</param>
        public void Write(WriteStream writer)
        {
            writer.WriteU8(R);
            writer.WriteU8(G);
            writer.WriteU8(B);
            writer.WriteU8(A);
        }
    }
}
