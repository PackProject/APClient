namespace LibWorkBench.Exceptions
{
    /// <summary>
    /// Thrown when a generic operation is not possible or has failed
    /// </summary>
    public sealed class OperationException : WorkBenchException
    {
        /// <summary>
        /// Constructor
        /// </summary>
        public OperationException()
        {
        }

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="message">Exception error message</param>
        public OperationException(string message)
            : base(message)
        {
        }
    }
}
