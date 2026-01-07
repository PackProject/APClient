namespace LibWorkBench.IO.Sources
{
    /// <summary>
    /// Interface for stream data source types
    /// </summary>
    public interface IDataSource : IDisposable
    {
        /// <summary>
        /// Reads a specified amount of data from the data source
        /// </summary>
        /// <param name="size">Number of bytes to read</param>
        /// <returns>Data block as an array of bytes</returns>
        public abstract byte[] Read(ulong size);

        /// <summary>
        /// Writes a specified block of data to the data source
        /// </summary>
        /// <param name="data">Data contents to write</param>
        /// <param name="size">Number of bytes to write (optional)</param>
        public abstract void Write(byte[] data, ulong? size = null);

        /// <summary>
        /// Seeks to the specified position in the data source
        /// </summary>
        /// <param name="offset">Offset (relative to the origin)</param>
        /// <param name="origin">Origin position</param>
        public abstract void Seek(long offset, SeekOrigin origin);

        /// <summary>
        /// Flushes the data source contents
        /// </summary>
        public abstract void Close();

        /// <summary>
        /// Gets the current position in the data source
        /// </summary>
        public abstract ulong Position { get; }
        /// <summary>
        /// Gets the length of the data source
        /// </summary>
        public abstract ulong Length { get; }
        /// <summary>
        /// Tests whether the data source has hit the end-of-file mark
        /// </summary>
        public abstract bool EOF { get; }
    }
}
