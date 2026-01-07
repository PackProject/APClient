using LibWorkBench.Formats.JSystem.JMessage.Tag;

namespace LibWorkBench.API.Pack
{
    /// <summary>
    /// Tag processor for tag codes used by the original Pack Project (RP) games
    /// </summary>
    public sealed class RPSysTagProcessor : TagProcessorBase
    {
        /// <summary>
        /// Number of variadic argument tags to support
        /// </summary>
        private const uint TAG_VAR_NUM = 10;

        /// <summary>
        /// Constructor
        /// </summary>
        public RPSysTagProcessor()
        {
            for (uint i = 0; i < TAG_VAR_NUM; i++)
            {
                RegisterTag(0x00_0000 + i, $"VAR_{i}");
            }

            RegisterTag(0x01_0000, "GRAMMAR_BEGIN_SENTENCE");

            RegisterTag(0x02_0000, "WINDOW_DELAY");
            RegisterTag(0x02_0001, "WINDOW_DEFAULT_CURSOR");
            RegisterTag(0x02_0002, "WINDOW_CANCEL_SE");
            RegisterTag(0x02_0003, "WINDOW_ALIGN");

            RegisterTag(0xFF_0000, "COMMON_FONT_COLOR");
            RegisterTag(0xFF_0001, "COMMON_FONT_SIZE");
            RegisterTag(0xFF_0007, "COMMON_RUBY");
        }
    }
}
