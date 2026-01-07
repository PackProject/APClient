namespace LibWorkBench.Exceptions
{
    /// <summary>
    /// Thrown when a binary file describes a version or resource that is not supported by WorkBench
    /// </summary>
    public sealed class FileNotSupportedException : WorkBenchException
    {
        /// <summary>
        /// Constructor
        /// </summary>
        public FileNotSupportedException()
        {
        }

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="message">Exception error message</param>
        public FileNotSupportedException(string message)
            : base(message)
        {
        }
    }
}
