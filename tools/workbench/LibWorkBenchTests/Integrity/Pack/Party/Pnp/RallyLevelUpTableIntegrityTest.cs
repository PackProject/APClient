using LibWorkBench.API.Pack.Party.Pnp;
using LibWorkBench.Utility;
using LibWorkBenchTests.Integrity.Details;

namespace LibWorkBenchTests.Integrity.Pack.Party.Pnp
{
    /// <summary>
    /// Table Tennis rally level-up table resource integrity test
    /// </summary>
    [TestClass]
    public sealed class RallyLevelUpTableIntegrityTest : IntegrityTestImpl<RallyLevelUpTableFile, TestFile>
    {
        /// <summary>
        /// Test case files
        /// </summary>
        private static readonly List<TestFile> TEST_FILES = [
            new TestFile(
                path: "Data/Pack/Party/Pnp/RallyLevelUpTable/rallyleveluptable.json",
                endian: EndianUtil.Type.Big,
                hash: "76fe4ad9cf2478aa169e6ab411ec14520a1f6d16a06a1033d7e9817e12698d40"
            ),

            new TestFile(
                path: "Data/Pack/Party/Pnp/RallyLevelUpTable/rallyleveluptable2.json",
                endian: EndianUtil.Type.Big,
                hash: "5ba3c4d8fcc211606713b8bb77497fdd5cf8a979b96ac09c0ad406b3bee24103"
            ),
        ];

        [TestMethod]
        public void TestMethod()
        {
            Run(TEST_FILES);
        }
    }
}
