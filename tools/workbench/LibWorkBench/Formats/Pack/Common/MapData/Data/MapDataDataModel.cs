using LibWorkBench.API.Pack.Common;
using LibWorkBench.Core.Models.Binary;
using LibWorkBench.Formats.Pack.Common.MapData.Binary;
using LibWorkBench.IO.Streams;

namespace LibWorkBench.Formats.Pack.Common.MapData.Data
{
    /// <summary>
    /// Pack map data data-view model
    /// </summary>
    public sealed class MapDataDataModel : TRawDataModel<MapDataFile>
    {
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
        /// Updates this model to match the contents of the binary-view model (derived implementation)
        /// </summary>
        /// <param name="binaryModel">Binary-view model</param>
        public override void Sync(BinaryModel binaryModel)
        {
            MapDataBinaryModel src = (MapDataBinaryModel)binaryModel;

            // . . .
        }
    }
}
