using LibWorkBench.Core;
using LibWorkBench.IO.Streams;
using LibWorkBench.Formats.NW4R.SystemLib.Types;

namespace LibWorkBench.Formats.NW4R.LayoutLib.Layout.Types
{
    /// <summary>
    /// Texture S/R/T transformation
    /// </summary>
    public sealed class TexSrt : IUseBinary
    {
        /// <summary>
        /// Texture translation
        /// </summary>
        public VEC2 Translate { get; set; } = new();

        /// <summary>
        /// Texture rotation
        /// </summary>
        public float Rotate { get; set; } = 0.0f;

        /// <summary>
        /// Texture scale
        /// </summary>
        public VEC2 Scale { get; set; } = new();

        /// <summary>
        /// Deserializes the contents of this object from a file
        /// </summary>
        /// <param name="reader">Binary stream to the file</param>
        public void Read(ReadStream reader)
        {
            Translate.Read(reader);
            Rotate = reader.ReadF32();
            Scale.Read(reader);
        }

        /// <summary>
        /// Serializes the contents of this object to a file
        /// </summary>
        /// <param name="writer">Binary stream to the file</param>
        public void Write(WriteStream writer)
        {
            Translate.Write(writer);
            writer.WriteF32(Rotate);
            Scale.Write(writer);
        }
    }
}
