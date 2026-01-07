using LibWorkBench.Formats.JSystem.JMessage.Tag;

namespace LibWorkBench.API.Pack
{
    /// <summary>
    /// Tag processor for tag codes used by Wii Sports Resort (WS2)
    /// </summary>
    public sealed class WS2TagProcessor : TagProcessorBase
    {
        /// <summary>
        /// Number of variadic argument tags to support
        /// </summary>
        private const uint TAG_VAR_NUM = 10;

        /// <summary>
        /// Constructor
        /// </summary>
        public WS2TagProcessor()
        {
            for (uint i = 0; i < TAG_VAR_NUM; i++)
            {
                RegisterTag(0x00_0000 + i, $"VAR_{i}");
            }

            RegisterTag(0x01_0000, "GRAMMAR_BEGIN_SENTENCE");

            RegisterTag(0x05_0000, "T05_0000");

            RegisterTag(0x0A_0000, "T0A_0000");
            RegisterTag(0x0A_0001, "T0A_0001");
            RegisterTag(0x0A_0002, "T0A_0002");
            RegisterTag(0x0A_0003, "T0A_0003");
            RegisterTag(0x0A_0004, "T0A_0004");
            RegisterTag(0x0A_0005, "T0A_0005");
            RegisterTag(0x0A_0006, "T0A_0006");
            RegisterTag(0x0A_0007, "T0A_0007");

            RegisterTag(0xFF_0000, "COMMON_FONT_COLOR");
            RegisterTag(0xFF_0001, "COMMON_FONT_SIZE");
            RegisterTag(0xFF_0007, "COMMON_RUBY");
        }
    }
}
