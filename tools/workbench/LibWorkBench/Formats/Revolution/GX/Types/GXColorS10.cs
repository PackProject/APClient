using LibWorkBench.Core;
using LibWorkBench.IO.Streams;

namespace LibWorkBench.Formats.Revolution.GX.Types
{
    /// <summary>
    /// 16-bit RGBA color
    /// </summary>
    public sealed class GXColorS10 : IUseBinary
    {
        /// <summary>
        /// Red component
        /// </summary>
        public short R { get; set; } = 0;

        /// <summary>
        /// Green component
        /// </summary>
        public short G { get; set; } = 0;

        /// <summary>
        /// Blue component
        /// </summary>
        public short B { get; set; } = 0;

        /// <summary>
        /// Alpha component
        /// </summary>
        public short A { get; set; } = 0;

        /// <summary>
        /// Deserializes the contents of this object from a file
        /// </summary>
        /// <param name="reader">Binary stream to the file</param>
        public void Read(ReadStream reader)
        {
            R = reader.ReadS16();
            G = reader.ReadS16();
            B = reader.ReadS16();
            A = reader.ReadS16();
        }

        /// <summary>
        /// Serializes the contents of this object to a file
        /// </summary>
        /// <param name="writer">Binary stream to the file</param>
        public void Write(WriteStream writer)
        {
            writer.WriteS16(R);
            writer.WriteS16(G);
            writer.WriteS16(B);
            writer.WriteS16(A);
        }
    }
}
