using LibWorkBench.Utility;

namespace LibWorkBenchTests.Integrity
{
    /// <summary>
    /// File for use in an integrity test
    /// </summary>
    public class TestFile
    {
        /// <summary>
        /// Path to the JSON file
        /// </summary>
        public string Path { get; init; } = "";

        /// <summary>
        /// Endianness in which to save the binary file
        /// </summary>
        public EndianUtil.Type Endian { get; set; } = EndianUtil.Type.Big;

        /// <summary>
        /// Expected SHA-256 hash of the binary file
        /// </summary>
        public string Hash { get; init; } = "";

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="path">Path to the JSON file</param>
        /// <param name="endian">Endianness in which to save the binary file</param>
        /// <param name="hash">Expected SHA-256 hash of the binary file</param>
        public TestFile(string path, EndianUtil.Type endian, string hash)
        {
            Path = path;
            Endian = endian;
            Hash = hash;
        }
    }
}
