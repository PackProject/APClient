namespace LibWorkBench.Formats.NW4R.LayoutLib.Layout.Types
{
    /// <summary>
    /// Window texture flip configuration
    /// </summary>
    public enum TextureFlip
    {
        /// <summary>
        /// Frame is not flipped
        /// </summary>
        None,

        /// <summary>
        /// Frame is mirrored horizontally
        /// </summary>
        FlipH,

        /// <summary>
        /// Frame is mirrored vertically
        /// </summary>
        FlipV,

        /// <summary>
        /// Frame is rotated 90 degrees
        /// </summary>
        Flip90,

        /// <summary>
        /// Frame is rotated 180 degrees
        /// </summary>
        Flip180,

        /// <summary>
        /// Frame is rotated 270 degrees
        /// </summary>
        Flip270
    }
}
