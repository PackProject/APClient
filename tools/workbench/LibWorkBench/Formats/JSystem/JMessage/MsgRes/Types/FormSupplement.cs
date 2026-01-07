namespace LibWorkBench.Formats.JSystem.JMessage.MsgRes.Types
{
    /// <summary>
    /// Message ID supplemental format type
    /// </summary>
    public enum FormSupplement
    {
        /// <summary>
        /// Group ID is 32 bits wide
        /// </summary>
        Group32,

        /// <summary>
        /// Group ID is 24 bits wide
        /// </summary>
        Group24,

        /// <summary>
        /// Group ID is 16 bits wide
        /// </summary>
        Group16,

        /// <summary>
        /// Group ID is 8 bits wide
        /// </summary>
        Group8,

        /// <summary>
        /// No group ID is provided
        /// </summary>
        Group0,
    }
}
