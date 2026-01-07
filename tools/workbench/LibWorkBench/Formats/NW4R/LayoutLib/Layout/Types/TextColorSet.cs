using LibWorkBench.Core;
using LibWorkBench.IO.Streams;
using LibWorkBench.Formats.Revolution.GX.Types;

namespace LibWorkBench.Formats.NW4R.LayoutLib.Layout.Types
{
    /// <summary>
    /// Textbox vertex color set
    /// </summary>
    public sealed class TextColorSet : IUseBinary
    {
        /// <summary>
        /// Top-left/top-right vertex color
        /// </summary>
        public GXColor Top { get; set; } = new();

        /// <summary>
        /// Bottom-left/bottom-right vertex color
        /// </summary>
        public GXColor Bottom { get; set; } = new();

        /// <summary>
        /// Deserializes the contents of this object from a file
        /// </summary>
        /// <param name="reader">Binary stream to the file</param>
        public void Read(ReadStream reader)
        {
            Top.Read(reader);
            Bottom.Read(reader);
        }

        /// <summary>
        /// Serializes the contents of this object to a file
        /// </summary>
        /// <param name="writer">Binary stream to the file</param>
        public void Write(WriteStream writer)
        {
            Top.Write(writer);
            Bottom.Write(writer);
        }
    }
}
