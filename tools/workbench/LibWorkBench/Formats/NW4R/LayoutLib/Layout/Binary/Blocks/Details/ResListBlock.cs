using LibWorkBench.Exceptions;
using LibWorkBench.IO.Streams;
using LibWorkBench.Formats.NW4R;
using LibWorkBench.Formats.NW4R.LayoutLib.Layout.Binary;

namespace LibWorkBench.Formats.NW4R.LayoutLib.Layout.Binary.Blocks.Details
{
    /// <summary>
    /// Base class for resource list blocks
    /// </summary>
    public abstract class ResListBlock : TNW4RBinaryBlock<LayoutBinaryModel>
    {
        /// <summary>
        /// Size of the binary resource entries (res::Font, res::Texture, etc.)
        /// </summary>
        private const uint RES_ENTRY_SIZE = 8;

        /// <summary>
        /// Resource entry
        /// </summary>
        public class Entry
        {
            /// <summary>
            /// Resource name
            /// </summary>
            public string Name { get; set; } = "";

            /// <summary>
            /// Resource type
            /// </summary>
            public byte Kind { get; set; } = 0;

            /// <summary>
            /// Constructor
            /// </summary>
            /// <param name="name">Resource name</param>
            /// <param name="kind">Resource type</param>
            public Entry(string name, byte kind = 0)
            {
                Name = name;
                Kind = kind;
            }
        }

        /// <summary>
        /// Resources described within this block
        /// </summary>
        public List<Entry> Resources { get; set; } = new();

        /// <summary>
        /// Deserializes the contents of this object from a file (derived implementation)
        /// </summary>
        /// <param name="reader">Binary stream to the file</param>
        public override void DoRead(ReadStream reader)
        {
            Resources.Clear();

            ushort entryNum = reader.ReadU16();
            reader.Align(4);

            // Start position is the base for name offsets
            ulong startOffset = reader.Position;

            List<uint> offsetList = new();
            List<byte> kindList = new();

            for (ushort i = 0; i < entryNum; i++)
            {
                offsetList.Add(reader.ReadU32());

                kindList.Add(reader.ReadU8());
                reader.Align(4);
            }

            // Resolve name string offsets
            for (ushort i = 0; i < entryNum; i++)
            {
                reader.Seek((long)(startOffset + offsetList[i]),
                            SeekOrigin.Begin);

                Resources.Add(new(
                    name: reader.ReadString(),
                    kind: kindList[i]
                ));
            }
        }

        /// <summary>
        /// Serializes the contents of this object to a file (derived implementation)
        /// </summary>
        /// <param name="writer">Binary stream to the file</param>
        public override void DoWrite(WriteStream writer)
        {
            if (Resources.Count > ushort.MaxValue)
            {
                throw new FileBrokenException("Too many resources");
            }

            writer.WriteU16((ushort)Resources.Count);
            writer.Align(4);

            // Calculate running offset for name strings
            uint offset = (uint)Resources.Count * RES_ENTRY_SIZE;

            // Write resource entries
            foreach (var it in Resources)
            {
                writer.WriteU32(offset);

                writer.WriteU8(it.Kind);
                writer.Align(4);

                // Adjust offset for name (include null terminator)
                offset += (uint)it.Name.Length + 1;
            }

            // Write resource string pool
            Resources.ForEach(it => writer.WriteString(it.Name));
        }
    }
}
