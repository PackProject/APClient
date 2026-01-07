using LibWorkBench.API.Pack.Party.Pnp;
using LibWorkBench.Formats.Pack.Details;
using LibWorkBench.Formats.Pack.Party.Pnp.RallyLevelUpTable.Types;
using LibWorkBench.IO.Streams;

namespace LibWorkBench.Formats.Pack.Party.Pnp.RallyLevelUpTable
{
    /// <summary>
    /// Rally level-up table data-view model
    /// </summary>
    public sealed class RallyLevelUpTableDataModel : TExcelBinDataModel<RallyLevelUpTableFile>
    {
        /// <summary>
        /// Level table entries
        /// </summary>
        public List<RallyLevelUpEntry> Levels { get; set; } = new();

        /// <summary>
        /// Deserializes the contents of this model from a file
        /// </summary>
        /// <param name="reader">Stream to the JSON file</param>
        public override void Load(JsonFileReader reader)
        {
            reader.Deserialize(this);
        }

        /// <summary>
        /// Serializes the contents of this model to a file
        /// </summary>
        /// <param name="writer">Stream to the JSON file</param>
        public override void Dump(JsonFileWriter writer)
        {
            writer.Serialize(this);
        }

        /// <summary>
        /// Updates this model to match the contents of the binary-view model
        /// </summary>
        /// <param name="binaryModel">Binary-view model</param>
        public override void OnSync(ExcelBinBinaryModel binaryModel)
        {
            RallyLevelUpTableBinaryModel src
                = (RallyLevelUpTableBinaryModel)binaryModel;

            Levels = src.Levels;
        }
    }
}
