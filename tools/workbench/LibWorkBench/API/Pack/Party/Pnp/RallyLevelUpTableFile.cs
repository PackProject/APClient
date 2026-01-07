using LibWorkBench.Attributes;
using LibWorkBench.Core.Models;
using LibWorkBench.Formats.Pack.Party.Pnp.RallyLevelUpTable;
using LibWorkBench.Formats.Pack.Party.Pnp.RallyLevelUpTable.Types;

namespace LibWorkBench.API.Pack.Party.Pnp
{
    /// <summary>
    /// Table Tennis rally level-up table file
    /// </summary>
    [ResourceProfile(name: "pnprally", extension: "bin")]
    public sealed class RallyLevelUpTableFile : TResource<RallyLevelUpTableBinaryModel, RallyLevelUpTableDataModel>
    {
        /// <summary>
        /// Level-up table entries
        /// </summary>
        public List<RallyLevelUpEntry> Levels
        {
            get => DataModel.Levels;
            set { DataModel.Levels = value; }
        }
    }
}
