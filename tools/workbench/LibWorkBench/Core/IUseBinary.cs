using LibWorkBench.IO.Streams;

namespace LibWorkBench.Core
{
    /// <summary>
    /// Interface for objects serialized as binary data
    /// </summary>
    public interface IUseBinary
    {
        /// <summary>
        /// Deserializes the contents of this object from a file
        /// </summary>
        /// <param name="reader">Binary stream to the file</param>
        public abstract void Read(ReadStream reader);

        /// <summary>
        /// Serializes the contents of this object to a file
        /// </summary>
        /// <param name="writer">Binary stream to the file</param>
        public abstract void Write(WriteStream writer);
    }
}
