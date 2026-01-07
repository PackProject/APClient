using LibWorkBench.Attributes;
using LibWorkBench.Core.Models;
using LibWorkBench.Formats.Pack.Party.Pnp.LevelTable;
using LibWorkBench.Formats.Pack.Party.Pnp.LevelTable.Types;

namespace LibWorkBench.API.Pack.Party.Pnp
{
    /// <summary>
    /// Table Tennis level table file
    /// </summary>
    [ResourceProfile(name: "pnplevel", extension: "bin")]
    public sealed class LevelTableFile : TResource<LevelTableBinaryModel, LevelTableDataModel>
    {
        /// <summary>
        /// Level table entries
        /// </summary>
        public List<LevelEntry> Levels
        {
            get => DataModel.Levels;
            set { DataModel.Levels = value; }
        }
    }
}
