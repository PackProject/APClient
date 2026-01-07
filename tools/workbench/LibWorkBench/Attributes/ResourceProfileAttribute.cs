namespace LibWorkBench.Attributes
{
    /// <summary>
    /// Attribute for describing resource types
    /// </summary>
    [AttributeUsage(AttributeTargets.Class)]
    public sealed class ResourceProfileAttribute : Attribute
    {
        /// <summary>
        /// Internal name of this resource
        /// </summary>
        public readonly string Name;

        /// <summary>
        /// File extension associated with this resource
        /// </summary>
        public readonly string Extension;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="name">Resource name</param>
        public ResourceProfileAttribute(string name, string extension)
        {
            Name = name;
            Extension = extension;
        }
    }
}
