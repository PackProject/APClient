using LibWorkBench.API.Pack.Party.Pnp;
using LibWorkBench.Utility;
using LibWorkBenchTests.Integrity.Details;

namespace LibWorkBenchTests.Integrity.Pack.Party.Pnp
{
    /// <summary>
    /// Table Tennis level table resource integrity test
    /// </summary>
    [TestClass]
    public sealed class LevelTableIntegrityTest : IntegrityTestImpl<LevelTableFile, TestFile>
    {
        /// <summary>
        /// Test case files
        /// </summary>
        private static readonly List<TestFile> TEST_FILES = [
            new TestFile(
                path: "Data/Pack/Party/Pnp/LevelTable/leveltable.json",
                endian: EndianUtil.Type.Big,
                hash: "40b79c6031397d7316f794064d1aec48187f9abc668ad44910b45f684d316b58"
            ),
        ];

        [TestMethod]
        public void TestMethod()
        {
            Run(TEST_FILES);
        }
    }
}
