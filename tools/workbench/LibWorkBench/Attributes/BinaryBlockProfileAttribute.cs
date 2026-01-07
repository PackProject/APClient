namespace LibWorkBench.Attributes
{
    /// <summary>
    /// Attribute for describing binary block types
    /// </summary>
    [AttributeUsage(AttributeTargets.Class)]
    public sealed class BinaryBlockProfileAttribute : Attribute
    {
        /// <summary>
        /// Signature ("magic") used to identify this block in binary files
        /// </summary>
        public readonly string Signature;

        /// <summary>
        /// Minimum model version required for this block
        /// </summary>
        public readonly uint MinVersion;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="signature">Block type signature</param>
        /// <param name="minVersion">Minimum required model version</param>
        public BinaryBlockProfileAttribute(string signature,
                                           uint minVersion = 0)
        {
            Signature = signature;
            MinVersion = minVersion;
        }
    }
}
