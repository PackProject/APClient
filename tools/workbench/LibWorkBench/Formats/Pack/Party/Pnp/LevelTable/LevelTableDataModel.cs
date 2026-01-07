using LibWorkBench.API.Pack.Party.Pnp;
using LibWorkBench.Formats.Pack.Details;
using LibWorkBench.Formats.Pack.Party.Pnp.LevelTable.Types;
using LibWorkBench.IO.Streams;

namespace LibWorkBench.Formats.Pack.Party.Pnp.LevelTable
{
    /// <summary>
    /// Level table data-view model
    /// </summary>
    public sealed class LevelTableDataModel : TExcelBinDataModel<LevelTableFile>
    {
        /// <summary>
        /// Level table entries
        /// </summary>
        public List<LevelEntry> Levels { get; set; } = new();

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
            LevelTableBinaryModel src = (LevelTableBinaryModel)binaryModel;

            Levels = src.Levels;
        }
    }
}
