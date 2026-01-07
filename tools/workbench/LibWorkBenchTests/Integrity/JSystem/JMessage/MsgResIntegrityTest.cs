using LibWorkBench.API.JSystem.JMessage;
using LibWorkBench.API.Pack;
using LibWorkBench.Formats.JSystem.JMessage.Tag;
using LibWorkBench.Utility;
using LibWorkBenchTests.Integrity.Details;

namespace LibWorkBenchTests.Integrity.JSystem.JMessage
{
    /// <summary>
    /// File for use in a MsgRes integrity test
    /// </summary>
    public class MsgResTestFile : TestFile
    {
        /// <summary>
        /// Message tag processor
        /// </summary>
        public TagProcessorBase TagProcessor { get; init; }

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="path">Path to the JSON file</param>
        /// <param name="endian">Endianness in which to save the binary file</param>
        /// <param name="hash">Expected SHA-256 hash of the binary file</param>
        /// <param name="tagProcessor">Message tag processor</param>
        public MsgResTestFile(string path, EndianUtil.Type endian, string hash,
                              TagProcessorBase tagProcessor)
            : base(path, endian, hash)
        {
            TagProcessor = tagProcessor;
        }
    }

    /// <summary>
    /// MsgRes resource integrity test
    /// </summary>
    [TestClass]
    public sealed class MsgResIntegrityTest : IntegrityTestImpl<MsgResFile, MsgResTestFile>
    {
        /// <summary>
        /// Test case files
        /// </summary>
        private static readonly List<TestFile> TEST_FILES = [
            // Pack Project common messages
            new MsgResTestFile(
                path: "Data/JSystem/JMessage/MsgRes/common_message.json",
                endian: EndianUtil.Type.Big,
                hash: "6a4e4873d0c4bd5964fd0f284cfa8bdfb1673b892c1b812b2e1485cee7c9a32c",
                tagProcessor: new RPSysTagProcessor()
            ),

            // Wii Sports messages
            new MsgResTestFile(
                path: "Data/JSystem/JMessage/MsgRes/sports_message.json",
                endian: EndianUtil.Type.Big,
                hash: "8b96a50108e624318be6f48b2214e1b237ce0e3c52825e7f1014d7459ce6597b",
                tagProcessor: new RPSysTagProcessor()
            ),

            // Wii Play messages
            new MsgResTestFile(
                path: "Data/JSystem/JMessage/MsgRes/party_message.json",
                endian: EndianUtil.Type.Big,
                hash: "6d56cc3685e793ee7b24ac9240b1926ef83e36938bd050081c2da0b5e0a87b46",
                tagProcessor: new RPSysTagProcessor()
            ),

            // Wii Sports Resort messages
            new MsgResTestFile(
                path: "Data/JSystem/JMessage/MsgRes/Sports2.json",
                endian: EndianUtil.Type.Big,
                hash: "74431582ab8e45d665700dd3925a8775ad1f83533d20deaccea252c0a0299930",
                tagProcessor: new WS2TagProcessor()
            ),
        ];

        /// <summary>
        /// Performs any logic necessary before running the current test
        /// </summary>
        /// <param name="resource">WorkBench resource</param>
        /// <param name="file">Test case file</param>
        public override void BeforeTest(MsgResFile resource, MsgResTestFile file)
        {
            resource.TagProcessor = file.TagProcessor;
        }

        [TestMethod]
        public void TestMethod()
        {
            Run(TEST_FILES);
        }
    }
}
