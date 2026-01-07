namespace LibWorkBench.Exceptions
{
    /// <summary>
    /// Thrown when a binary file does not match its expected signature / "magic"
    /// </summary>
    public sealed class FileSignatureException : WorkBenchException
    {
        /// <summary>
        /// Constructor
        /// </summary>
        public FileSignatureException()
        {
        }

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="message">Exception error message</param>
        public FileSignatureException(string message)
            : base(message)
        {
        }
    }
}
