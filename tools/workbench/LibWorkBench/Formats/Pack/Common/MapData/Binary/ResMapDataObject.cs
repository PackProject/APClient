using LibWorkBench.Core;
using LibWorkBench.Formats.NW4R.SystemLib.Types;
using LibWorkBench.IO.Streams;

namespace LibWorkBench.Formats.Pack.Common.MapData.Binary
{
    /// <summary>
    /// Map data object (binary-view)
    /// </summary>
    public sealed class ResMapDataObject : IUseBinary
    {
        /// <summary>
        /// Object group ID
        /// </summary>
        public ushort Group { get; set; } = 0;

        /// <summary>
        /// Object ID
        /// </summary>
        public ushort ID { get; set; } = 0;

        /// <summary>
        /// Object layer ID
        /// </summary>
        public byte Layer { get; set; } = 0;

        /// <summary>
        /// Object position
        /// </summary>
        public VEC3 Position { get; set; } = new();

        /// <summary>
        /// Object scale
        /// </summary>
        public VEC3 Scale { get; set; } = new();

        /// <summary>
        /// Object transformation matrix
        /// </summary>
        public MTX33 Transform { get; set; } = new();

        /// <summary>
        /// Index of the path associated with this object
        /// </summary>
        public int PathIndex { get; set; } = -1;

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
            Group = reader.ReadU16();
            ID = reader.ReadU16();
            Layer = reader.ReadU8();
            reader.Align(4);

            Position.Read(reader);
            Scale.Read(reader);
            Transform.Read(reader);

            PathIndex = reader.ReadS32();
            UserData = reader.Read(MapDataDefine.OBJECT_USERDATA_LEN);
        }

        /// <summary>
        /// Serializes the contents of this object to a file
        /// </summary>
        /// <param name="writer">Binary stream to the file</param>
        public void Write(WriteStream writer)
        {
            writer.WriteU16(Group);
            writer.WriteU16(ID);
            writer.WriteU8(Layer);
            writer.Align(4);

            Position.Write(writer);
            Scale.Write(writer);
            Transform.Write(writer);

            writer.WriteS32(PathIndex);
            writer.Write(UserData);
        }
    }
}
