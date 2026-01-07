namespace LibWorkBench.IO.Sources
{
    /// <summary>
    /// Stream data source for a physical file
    /// </summary>
    public class FileDataSource : IDataSource
    {
        /// <summary>
        /// Whether the Dispose method has been called
        /// </summary>
        protected bool _disposed = false;

        /// <summary>
        /// Underlying file stream
        /// </summary>
        public FileStream BaseStream { get; }

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="path">File path to open</param>
        /// <param name="writable">Whether the file is writable</param>
        public FileDataSource(string path, bool writable)
        {
            BaseStream = new FileStream(
                path,
                writable ? FileMode.Create : FileMode.Open,
                writable ? FileAccess.Write : FileAccess.Read
            );
        }

        /// <summary>
        /// Destructor
        /// </summary>
        ~FileDataSource()
        {
            Dispose(disposing: false);
        }

        /// <summary>
        /// Releases resources
        /// </summary>
        public void Dispose()
        {
            Dispose(disposing: true);
            GC.SuppressFinalize(this);
        }

        /// <summary>
        /// Reads a specified amount of data from the data source
        /// </summary>
        /// <param name="size">Number of bytes to read</param>
        /// <returns>Data block as an array of bytes</returns>
        public byte[] Read(ulong size)
        {
            byte[] buffer = new byte[size];
            BaseStream.ReadExactly(buffer, 0, buffer.Length);
            return buffer;
        }

        /// <summary>
        /// Writes a specified block of data to the data source
        /// </summary>
        /// <param name="data">Data contents to write</param>
        /// <param name="size">Number of bytes to write (optional)</param>
        public void Write(byte[] data, ulong? size = null)
        {
            BaseStream.Write(data, 0, size != null ? (int)size : data.Length);
        }

        /// <summary>
        /// Seeks to the specified position in the data source
        /// </summary>
        /// <param name="offset">Offset (relative to the origin)</param>
        /// <param name="origin">Origin position</param>
        public void Seek(long offset, SeekOrigin origin)
        {
            BaseStream.Seek(offset, origin);
        }

        /// <summary>
        /// Flushes the data source contents
        /// </summary>
        public void Close()
        {
            BaseStream.Close();
        }

        /// <summary>
        /// Gets the current position in the data source
        /// </summary>
        public ulong Position => (ulong)BaseStream.Position;
        /// <summary>
        /// Gets the length of the data source
        /// </summary>
        public ulong Length => (ulong)BaseStream.Length;
        /// <summary>
        /// Tests whether the data source has hit the end-of-file mark
        /// </summary>
        public bool EOF => Position >= Length;

        /// <summary>
        /// Releases resources
        /// </summary>
        /// <param name="disposing">Whether this method has been called from a dispose context</param>
        protected virtual void Dispose(bool disposing)
        {
            if (_disposed)
            {
                return;
            }

            if (disposing)
            {
                BaseStream.Dispose();
            }

            _disposed = true;
        }
    }
}
