namespace LibWorkBench.Exceptions
{
    /// <summary>
    /// Base class for all WorkBench exception types
    /// </summary>
    public abstract class WorkBenchException : Exception
    {
        /// <summary>
        /// Constructor
        /// </summary>
        public WorkBenchException()
        {
        }

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="message">Exception error message</param>
        public WorkBenchException(string message)
            : base(message)
        {
        }
    }
}
