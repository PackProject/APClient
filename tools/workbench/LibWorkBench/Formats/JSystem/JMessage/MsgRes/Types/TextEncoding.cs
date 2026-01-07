namespace LibWorkBench.Formats.JSystem.JMessage.MsgRes.Types
{
    /// <summary>
    /// Text encoding type
    /// </summary>
    public enum TextEncoding
    {
        /// <summary>
        /// Encoding not set (legacy support)
        /// </summary>
        Undefined,

        /// <summary>
        /// Windows-1252 encoding
        /// </summary>
        CP1252,

        /// <summary>
        /// UTF-16 encoding
        /// </summary>
        UTF16,

        /// <summary>
        /// Shift-JIS encoding
        /// </summary>
        SJIS,

        /// <summary>
        /// UTF-8 encoding
        /// </summary>
        UTF8,
    }
}
