using System.Security.Cryptography;
using System.Text;

namespace LibWorkBenchTests.Integrity
{
    /// <summary>
    /// Integrity test utilities
    /// </summary>
    internal static class IntegrityUtil
    {
        /// <summary>
        /// Computes the SHA-256 hash of the specified file
        /// </summary>
        /// <param name="path">File path</param>
        /// <returns>SHA-256 hash hex digest</returns>
        public static string GetSha256Hash(string path)
        {
            SHA256 sha = SHA256.Create();
            byte[] digest = sha.ComputeHash(File.ReadAllBytes(path));

            StringBuilder builder = new();
            foreach (var it in digest)
            {
                builder.Append(it.ToString("x2"));
            }

            return builder.ToString();
        }
    }
}
