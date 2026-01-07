namespace LibWorkBench.Exceptions
{
    /// <summary>
    /// Thrown when a binary file holds invalid or corrupted state
    /// </summary>
    public sealed class FileBrokenException : WorkBenchException
    {
        /// <summary>
        /// Constructor
        /// </summary>
        public FileBrokenException()
        {
        }

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="message">Exception error message</param>
        public FileBrokenException(string message)
            : base(message)
        {
        }
    }
}
