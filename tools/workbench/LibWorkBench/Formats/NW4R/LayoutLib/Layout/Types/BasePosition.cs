using LibWorkBench.Core;
using LibWorkBench.IO.Streams;
using LibWorkBench.Utility;

namespace LibWorkBench.Formats.NW4R.LayoutLib.Layout.Types
{
    /// <summary>
    /// Horizontal position setting
    /// </summary>
    public enum HorizontalPosition
    {
        /// <summary>
        /// Position is relative to the left edge
        /// </summary>
        Left,

        /// <summary>
        /// Position is relative to the center
        /// </summary>
        Center,

        /// <summary>
        /// Position is relative to the right edge
        /// </summary>
        Right
    }

    /// <summary>
    /// Vertical position setting
    /// </summary>
    public enum VerticalPosition
    {
        /// <summary>
        /// Position is relative to the top edge
        /// </summary>
        Top,

        /// <summary>
        /// Position is relative to the center
        /// </summary>
        Center,

        /// <summary>
        /// Position is relative to the bottom edge
        /// </summary>
        Bottom
    }

    /// <summary>
    /// Layout base position configuration
    /// </summary>
    public sealed class BasePosition : IUseBinary
    {
        /// <summary>
        /// Horizontal position origin
        /// </summary>
        public HorizontalPosition H { get; set; } = HorizontalPosition.Left;

        /// <summary>
        /// Vertical position origin
        /// </summary>
        public VerticalPosition V { get; set; } = VerticalPosition.Top;

        /// <summary>
        /// Deserializes the contents of this object from a file
        /// </summary>
        /// <param name="reader">Binary stream to the file</param>
        public void Read(ReadStream reader)
        {
            byte packed = reader.ReadU8();

            H = (HorizontalPosition)
                (packed % Util.EnumCount<HorizontalPosition>());

            V = (VerticalPosition)
                (packed / Util.EnumCount<HorizontalPosition>());
        }

        /// <summary>
        /// Serializes the contents of this object to a file
        /// </summary>
        /// <param name="writer">Binary stream to the file</param>
        public void Write(WriteStream writer)
        {
            byte packed = 0;

            packed += (byte)((int)V * Util.EnumCount<HorizontalPosition>());
            packed += (byte)H;

            writer.WriteU8(packed);
        }
    }
}
