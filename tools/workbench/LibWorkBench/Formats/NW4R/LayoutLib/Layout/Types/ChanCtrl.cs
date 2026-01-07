using LibWorkBench.Core;
using LibWorkBench.IO.Streams;
using LibWorkBench.Formats.Revolution.GX.Types;

namespace LibWorkBench.Formats.NW4R.LayoutLib.Layout.Types
{
    /// <summary>
    /// Channel control configuration
    /// </summary>
    public sealed class ChanCtrl : IUseBinary
    {
        /// <summary>
        /// Channel color source
        /// </summary>
        public GXColorSrc ColorSrc { get; set; } = GXColorSrc.GX_SRC_VTX;

        /// <summary>
        /// Channel alpha source
        /// </summary>
        public GXColorSrc AlphaSrc { get; set; } = GXColorSrc.GX_SRC_VTX;

        /// <summary>
        /// Deserializes the contents of this object from a file
        /// </summary>
        /// <param name="reader">Binary stream to the file</param>
        public void Read(ReadStream reader)
        {
            ColorSrc = (GXColorSrc)reader.ReadU8();
            AlphaSrc = (GXColorSrc)reader.ReadU8();
            reader.Align(4);
        }

        /// <summary>
        /// Serializes the contents of this object to a file
        /// </summary>
        /// <param name="writer">Binary stream to the file</param>
        public void Write(WriteStream writer)
        {
            writer.WriteU8((byte)ColorSrc);
            writer.WriteU8((byte)AlphaSrc);
            writer.Align(4);
        }
    }
}
