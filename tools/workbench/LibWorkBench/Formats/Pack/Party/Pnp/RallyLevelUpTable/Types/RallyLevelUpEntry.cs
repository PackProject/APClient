using LibWorkBench.Core;
using LibWorkBench.IO.Streams;

namespace LibWorkBench.Formats.Pack.Party.Pnp.RallyLevelUpTable.Types
{
    /// <summary>
    /// Rally level-up table entry
    /// </summary>
    public sealed class RallyLevelUpEntry : IUseBinary
    {
        /// <summary>
        /// Size of this structure when saved in binary form
        /// </summary>
        public const int STRUCT_SIZE = 12;

        /// <summary>
        /// Minimum rally count required to reach this level-up
        /// </summary>
        public uint Rally { get; set; } = 0;

        /// <summary>
        /// AI control level to use (index into the LevelTable)
        /// </summary>
        public uint LevelIndex { get; set; } = 0;

        /// <summary>
        /// Speed at which the ball will move
        /// </summary>
        public float Power { get; set; } = 0.0f;

        /// <summary>
        /// Deserializes the contents of this object from a file
        /// </summary>
        /// <param name="reader">Binary stream to the file</param>
        public void Read(ReadStream reader)
        {
            Rally = reader.ReadU32();
            LevelIndex = reader.ReadU32();
            Power = reader.ReadF32();
        }

        /// <summary>
        /// Serializes the contents of this object to a file
        /// </summary>
        /// <param name="writer">Binary stream to the file</param>
        public void Write(WriteStream writer)
        {
            writer.WriteU32(Rally);
            writer.WriteU32(LevelIndex);
            writer.WriteF32(Power);
        }
    }
}
