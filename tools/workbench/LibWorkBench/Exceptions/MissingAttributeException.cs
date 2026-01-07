namespace LibWorkBench.Exceptions
{
    /// <summary>
    /// Thrown when a class type is missing an attribute required by WorkBench
    /// </summary>
    public sealed class MissingAttributeException : WorkBenchException
    {
        /// <summary>
        /// Constructor
        /// </summary>
        public MissingAttributeException()
        {
        }

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="message">Exception error message</param>
        public MissingAttributeException(string message)
            : base(message)
        {
        }
    }
}
