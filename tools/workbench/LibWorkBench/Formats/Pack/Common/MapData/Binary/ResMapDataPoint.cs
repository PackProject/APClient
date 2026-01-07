using LibWorkBench.Core;
using LibWorkBench.Formats.NW4R.SystemLib.Types;
using LibWorkBench.IO.Streams;

namespace LibWorkBench.Formats.Pack.Common.MapData.Binary
{
    /// <summary>
    /// Map data path point (binary-view)
    /// </summary>
    public sealed class ResMapDataPoint : IUseBinary
    {
        /// <summary>
        /// Point position
        /// </summary>
        public VEC3 Position { get; set; } = new();

        /// <summary>
        /// User-specific data
        /// </summary>
        public byte[] UserData { get; set; } = [];

        /// <summary>
        /// Deserializes the contents of this object from a file
        /// </summary>
        /// <param name="reader">Binary stream to the file</param>
        public void Read(ReadStream reader)
        {
            Position.Read(reader);
            UserData = reader.Read(MapDataDefine.POINT_USERDATA_LEN);
        }

        /// <summary>
        /// Serializes the contents of this object to a file
        /// </summary>
        /// <param name="writer">Binary stream to the file</param>
        public void Write(WriteStream writer)
        {
            Position.Write(writer);
            writer.Write(UserData);
        }
    }
}
