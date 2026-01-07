namespace LibWorkBench.Attributes
{
    /// <summary>
    /// Attribute for describing binary model types
    /// </summary>
    [AttributeUsage(AttributeTargets.Class)]
    public sealed class BinaryModelProfileAttribute : Attribute
    {
        /// <summary>
        /// Signature ("magic") used to identify this model in binary files
        /// </summary>
        public readonly string Signature;

        /// <summary>
        /// Versions of this model that are supported by WorkBench
        /// </summary>
        public readonly uint[] Versions;

        /// <summary>
        /// Required byte-alignment for blocks in this model
        /// </summary>
        public readonly ulong Alignment;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="signature">Model type signature</param>
        /// <param name="versions">Supported model versions</param>
        /// <param name="alignment">Required byte-alignment for blocks</param>
        public BinaryModelProfileAttribute(string signature,
                                           uint[]? versions = null,
                                           ulong alignment = 4)
        {
            Signature = signature;
            Versions = versions != null ? versions : [];
            Alignment = alignment;
        }
    }
}
