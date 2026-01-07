using LibWorkBench.API.NW4R.LayoutLib;
using LibWorkBench.Utility;
using LibWorkBenchTests.Integrity.Details;

namespace LibWorkBenchTests.Integrity.NW4R.LayoutLib
{
    /// <summary>
    /// Layout resource integrity test
    /// </summary>
    [TestClass]
    public sealed class LayoutIntegrityTest : IntegrityTestImpl<LayoutFile, TestFile>
    {
        /// <summary>
        /// Test case files
        /// </summary>
        private static readonly List<TestFile> TEST_FILES = [
            // Version 8 layout (Wii Sports)
            new TestFile(
                path: "Data/NW4R/LayoutLib/Layout/golf_00.json",
                endian: EndianUtil.Type.Big,
                hash: "53bfd5b4cf8099edf2341f4b57e572481798faa1e64589685e2cc21dee79b0fa"
            ),

            // Version 10 layout (Wii Sports Resort)
            new TestFile(
                path: "Data/NW4R/LayoutLib/Layout/60200_general_opening_score.json",
                endian: EndianUtil.Type.Big,
                hash: "5038f83465421e7265d758c64849c6204af875d6d705eacd448abcf8422e5f0e"
            ),
        ];

        [TestMethod]
        public void TestMethod()
        {
            Run(TEST_FILES);
        }
    }
}
