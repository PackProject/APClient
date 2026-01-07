namespace LibWorkBench.Formats.NW4R
{
    /// <summary>
    /// Byte-order mark
    /// </summary>
    public enum ByteOrder
    {
        /// <summary>
        /// The resource is stored in big endian
        /// </summary>
        Big = 0xFEFF,

        /// <summary>
        /// The resource is stored in little endian
        /// </summary>
        Little = 0xFFFE
    }
}
