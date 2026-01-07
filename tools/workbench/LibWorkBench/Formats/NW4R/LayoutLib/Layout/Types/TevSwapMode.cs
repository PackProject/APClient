using LibWorkBench.Core;
using LibWorkBench.IO.Streams;
using LibWorkBench.Formats.Revolution.GX.Types;

namespace LibWorkBench.Formats.NW4R.LayoutLib.Layout.Types
{
    /// <summary>
    /// TEV color channel swap configuration
    /// </summary>
    public sealed class TevSwapMode : IUseBinary
    {
        /// <summary>
        /// Color component to use instead of the red component
        /// </summary>
        public GXTevColorChan R { get; set; } = GXTevColorChan.GX_CH_RED;

        /// <summary>
        /// Color component to use instead of the green component
        /// </summary>
        public GXTevColorChan G { get; set; } = GXTevColorChan.GX_CH_GREEN;

        /// <summary>
        /// Color component to use instead of the blue component
        /// </summary>
        public GXTevColorChan B { get; set; } = GXTevColorChan.GX_CH_BLUE;

        /// <summary>
        /// Color component to use instead of the alpha component
        /// </summary>
        public GXTevColorChan A { get; set; } = GXTevColorChan.GX_CH_ALPHA;

        /// <summary>
        /// Deserializes the contents of this object from a file
        /// </summary>
        /// <param name="reader">Binary stream to the file</param>
        public void Read(ReadStream reader)
        {
            byte packed = reader.ReadU8();

            R = (GXTevColorChan)(packed >> 0 & 0b11);
            G = (GXTevColorChan)(packed >> 2 & 0b11);
            B = (GXTevColorChan)(packed >> 4 & 0b11);
            A = (GXTevColorChan)(packed >> 6 & 0b11);
        }

        /// <summary>
        /// Serializes the contents of this object to a file
        /// </summary>
        /// <param name="writer">Binary stream to the file</param>
        public void Write(WriteStream writer)
        {
            byte packed = 0;

            packed |= (byte)(((int)R & 0b11) << 0);
            packed |= (byte)(((int)G & 0b11) << 2);
            packed |= (byte)(((int)B & 0b11) << 4);
            packed |= (byte)(((int)A & 0b11) << 6);

            writer.WriteU8(packed);
        }
    }
}
