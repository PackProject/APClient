using LibWorkBench.Core;
using LibWorkBench.IO.Streams;

namespace LibWorkBench.Formats.NW4R.SystemLib.Types
{
    /// <summary>
    /// 3D vector
    /// </summary>
    public sealed class VEC3 : IUseBinary
    {
        /// <summary>
        /// X-axis component
        /// </summary>
        public float X { get; set; } = 0.0f;

        /// <summary>
        /// Y-axis component
        /// </summary>
        public float Y { get; set; } = 0.0f;

        /// <summary>
        /// Z-axis component
        /// </summary>
        public float Z { get; set; } = 0.0f;

        /// <summary>
        /// Deserializes the contents of this object from a file
        /// </summary>
        /// <param name="reader">Binary stream to the file</param>
        public void Read(ReadStream reader)
        {
            X = reader.ReadF32();
            Y = reader.ReadF32();
            Z = reader.ReadF32();
        }

        /// <summary>
        /// Serializes the contents of this object to a file
        /// </summary>
        /// <param name="writer">Binary stream to the file</param>
        public void Write(WriteStream writer)
        {
            writer.WriteF32(X);
            writer.WriteF32(Y);
            writer.WriteF32(Z);
        }
    }
}
