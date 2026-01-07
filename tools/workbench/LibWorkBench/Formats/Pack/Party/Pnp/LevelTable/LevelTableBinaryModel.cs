using LibWorkBench.API.Pack.Party.Pnp;
using LibWorkBench.Formats.Pack.Details;
using LibWorkBench.Formats.Pack.Party.Pnp.LevelTable.Types;
using LibWorkBench.IO.Streams;

namespace LibWorkBench.Formats.Pack.Party.Pnp.LevelTable
{
    /// <summary>
    /// Level table binary-view model
    /// </summary>
    public sealed class LevelTableBinaryModel : TExcelBinBinaryModel<LevelTableFile>
    {
        /// <summary>
        /// Level table entries
        /// </summary>
        public List<LevelEntry> Levels { get; set; } = new();

        /// <summary>
        /// Deserializes the contents of this model from a file
        /// </summary>
        /// <param name="reader">Binary stream to the file</param>
        public override void Read(ReadStream reader)
        {
            // Level count is dynamically calculated
            ulong levelNum = reader.Length / LevelEntry.STRUCT_SIZE;

            for (ulong i = 0; i < levelNum; i++)
            {
                LevelEntry level = new();
                level.Read(reader);
                Levels.Add(level);
            }
        }

        /// <summary>
        /// Serializes the contents of this model to a file
        /// </summary>
        /// <param name="writer">Binary stream to the file</param>
        public override void Write(WriteStream writer)
        {
            Levels.ForEach(it => it.Write(writer));
        }

        /// <summary>
        /// Updates this model to match the contents of the data-view model (derived implementation)
        /// </summary>
        /// <param name="dataModel">Data-view model</param>
        public override void OnSync(ExcelBinDataModel dataModel)
        {
            LevelTableDataModel src = (LevelTableDataModel)dataModel;

            Levels = src.Levels;
        }
    }
}
