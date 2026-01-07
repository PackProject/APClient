using LibWorkBench.Core;
using LibWorkBench.IO.Streams;

namespace LibWorkBench.Formats.Pack.Common.MapData.Binary
{
    /// <summary>
    /// Map data path (binary-view)
    /// </summary>
    public sealed class ResMapDataPath : IUseBinary
    {
        /// <summary>
        /// Deserializes the contents of this object from a file
        /// </summary>
        /// <param name="reader">Binary stream to the file</param>
        public void Read(ReadStream reader)
        {
        }

        /// <summary>
        /// Serializes the contents of this object to a file
        /// </summary>
        /// <param name="writer">Binary stream to the file</param>
        public void Write(WriteStream writer)
        {
        }
    }
}
