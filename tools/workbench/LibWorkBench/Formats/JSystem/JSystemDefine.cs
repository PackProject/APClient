namespace LibWorkBench.Formats.JSystem
{
    /// <summary>
    /// Shared JSYSTEM constants
    /// </summary>
    public static class JSystemDefine
    {
        /// <summary>
        /// Maximum length for the Signature field of binary headers
        /// </summary>
        public const int HEADER_SIGNATURE_LENGTH = 8;

        /// <summary>
        /// Maximum length for the Signature field of binary blocks
        /// </summary>
        public const int BLOCK_SIGNATURE_LENGTH = 4;

        /// <summary>
        /// Byte alignment for all binary blocks
        /// </summary>
        public const ulong BLOCK_ALIGNMENT = 32;
    }
}
