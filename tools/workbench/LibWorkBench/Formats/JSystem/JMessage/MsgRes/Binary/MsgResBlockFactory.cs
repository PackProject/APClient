using LibWorkBench.Core.Models.Binary;
using LibWorkBench.Formats.JSystem.JMessage.MsgRes.Binary.Blocks;

namespace LibWorkBench.Formats.JSystem.JMessage.MsgRes.Binary
{
    /// <summary>
    /// MsgRes binary block factory
    /// </summary>
    public sealed class MsgResBlockFactory : BinaryBlockFactory
    {
        /// <summary>
        /// Constructor
        /// </summary>
        public MsgResBlockFactory()
        {
            RegisterBlock<FlowChartBlock>();
            RegisterBlock<FlowLabelBlock>();
            RegisterBlock<MsgDataBlock>();
            RegisterBlock<MsgIDBlock>();
            RegisterBlock<MsgInfoBlock>();
            RegisterBlock<StrAttrBlock>();
        }
    }
}
