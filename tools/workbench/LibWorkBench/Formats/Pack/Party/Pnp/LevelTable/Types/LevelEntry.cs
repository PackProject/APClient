using LibWorkBench.Core;
using LibWorkBench.IO.Streams;

namespace LibWorkBench.Formats.Pack.Party.Pnp.LevelTable.Types
{
    /// <summary>
    /// Level table entry
    /// </summary>
    public sealed class LevelEntry : IUseBinary
    {
        /// <summary>
        /// Size of this structure when saved in binary form
        /// </summary>
        public const int STRUCT_SIZE = 12;

        /// <summary>
        /// Probability of returning the ball in the "easy" difficulty direction
        /// </summary>
        public uint EasyChance { get; set; } = 0;

        /// <summary>
        /// Probability of returning the ball in the "medium" difficulty direction
        /// </summary>
        public uint MediumChance { get; set; } = 0;

        /// <summary>
        /// Probability of returning the ball in the "hard" difficulty direction
        /// </summary>
        public uint HardChance { get; set; } = 0;

        /// <summary>
        /// Deserializes the contents of this object from a file
        /// </summary>
        /// <param name="reader">Binary stream to the file</param>
        public void Read(ReadStream reader)
        {
            EasyChance = reader.ReadU32();
            MediumChance = reader.ReadU32();
            HardChance = reader.ReadU32();
        }

        /// <summary>
        /// Serializes the contents of this object to a file
        /// </summary>
        /// <param name="writer">Binary stream to the file</param>
        public void Write(WriteStream writer)
        {
            writer.WriteU32(EasyChance);
            writer.WriteU32(MediumChance);
            writer.WriteU32(HardChance);
        }
    }
}
