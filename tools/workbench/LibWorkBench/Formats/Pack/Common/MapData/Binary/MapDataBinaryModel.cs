using LibWorkBench.API.Pack.Common;
using LibWorkBench.Attributes;
using LibWorkBench.Core.Models.Data;
using LibWorkBench.IO.Streams;
using LibWorkBench.Utility;

namespace LibWorkBench.Formats.Pack.Common.MapData.Binary
{
    /// <summary>
    /// Pack map data binary-view model
    /// </summary>
    [BinaryModelProfile(signature: "PMPF")]
    public sealed class MapDataBinaryModel : TRawBinaryModel<MapDataFile>
    {
        /// <summary>
        /// Bit flag indices
        /// </summary>
        public enum Flag
        {
            /// <summary>
            /// Whether this file has been unpacked at runtime
            /// </summary>
            Unpacked,
        }

        /// <summary>
        /// Bitflags
        /// </summary>
        public BitFlag<ushort, Flag> Flags { get; set; } = new();

        /// <summary>
        /// Map objects
        /// </summary>
        public List<ResMapDataObject> Objects { get; set; } = new();

        /// <summary>
        /// Map paths
        /// </summary>
        public List<ResMapDataPath> Paths { get; set; } = new();

        /// <summary>
        /// Map path points
        /// </summary>
        public List<ResMapDataPoint> Points { get; set; } = new();

        /// <summary>
        /// Deserializes the contents of this model from a file
        /// </summary>
        /// <param name="reader">Binary stream to the file</param>
        public override void OnRead(ReadStream reader)
        {
            // Unknown data
            reader.Skip(4);

            Flags.SetDirect(reader.ReadU16());
            reader.Align(4);

            // Header is 16-byte aligned
            reader.Align(16);

            ushort objectNum = reader.ReadU16();
            ushort pathNum = reader.ReadU16();
            ushort pointNum = reader.ReadU16();

            // Why is the section 64-byte aligned?
            reader.Align(64);

            uint objectOffset = reader.ReadU32();
            uint pathOffset = reader.ReadU32();
            uint pointOffset = reader.ReadU32();

            // Why is the section 64-byte aligned?
            reader.Align(64);

            // Read object data
            reader.Seek(objectOffset, SeekOrigin.Begin);
            for (uint i = 0; i < objectNum; i++)
            {
                ResMapDataObject obj = new();
                obj.Read(reader);
                Objects.Add(obj);
            }

            // Read path data
            reader.Seek(pathOffset, SeekOrigin.Begin);
            for (uint i = 0; i < pathNum; i++)
            {
                ResMapDataPath path = new();
                path.Read(reader);
                Paths.Add(path);
            }

            // Read point data
            reader.Seek(pointOffset, SeekOrigin.Begin);
            for (uint i = 0; i < pointNum; i++)
            {
                ResMapDataPoint point = new();
                point.Read(reader);
                Points.Add(point);
            }
        }

        /// <summary>
        /// Serializes the contents of this model to a file
        /// </summary>
        /// <param name="writer">Binary stream to the file</param>
        public override void OnWrite(WriteStream writer)
        {
            // Unknown data
            writer.Skip(4);
        }

        /// <summary>
        /// Updates this model to match the contents of the data-view model (derived implementation)
        /// </summary>
        /// <param name="dataModel">Data-view model</param>
        public override void Sync(DataModel dataModel)
        {
        }
    }
}
