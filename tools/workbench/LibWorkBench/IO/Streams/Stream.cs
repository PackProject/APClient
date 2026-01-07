using LibWorkBench.IO.Encodings;
using LibWorkBench.IO.Sources;
using LibWorkBench.Utility;

namespace LibWorkBench.IO.Streams
{
    /// <summary>
    /// Base class for stream types
    /// </summary>
    public abstract class Stream : IDisposable
    {
        /// <summary>
        /// Whether the Dispose method has been called
        /// </summary>
        private bool _disposed = false;

        /// <summary>
        /// Data source used by this stream
        /// </summary>
        public IDataSource Source { get; }
        /// <summary>
        /// Primitive format used by this stream
        /// </summary>
        public IPrimEncoding PrimEncoding { get; set; }
        /// <summary>
        /// Character format used by this stream
        /// </summary>
        public ICharEncoding CharEncoding { get; set; }
        /// <summary>
        /// Endianness (byte-order) used by this stream
        /// </summary>
        public EndianUtil.Type Endian { get; set; }

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="source">Stream data source</param>
        /// <param name="primEncoding">Stream primitive format</param>
        /// <param name="charEncoding">Stream character format</param>
        /// <param name="endian">Stream endianness (byte-order)</param>
        public Stream(IDataSource source, IPrimEncoding primEncoding,
                      ICharEncoding charEncoding, EndianUtil.Type endian)
        {
            Source = source;
            PrimEncoding = primEncoding;
            CharEncoding = charEncoding;
            Endian = endian;
        }

        /// <summary>
        /// Destructor
        /// </summary>
        ~Stream()
        {
            Dispose(disposing: false);
        }

        /// <summary>
        /// Releases and finalizes resources
        /// </summary>
        public void Dispose()
        {
            Dispose(disposing: true);
            GC.SuppressFinalize(this);
        }

        /// <summary>
        /// Seeks to the specified position in the stream
        /// </summary>
        /// <param name="offset">Offset (relative to the origin)</param>
        /// <param name="origin">Origin position</param>
        public void Seek(long offset, SeekOrigin origin)
        {
            Source.Seek(offset, origin);
        }

        /// <summary>
        /// Seeks relative to the current stream position
        /// </summary>
        /// <param name="offset">Offset (relative to the current position)</param>
        public void Skip(long offset)
        {
            Seek(offset, SeekOrigin.Current);
        }

        /// <summary>
        /// Closes the stream, flushing the data source contents
        /// </summary>
        public void Close()
        {
            Source.Close();
        }

        /// <summary>
        /// Gets the stream's current position
        /// </summary>
        public ulong Position => Source.Position;
        /// <summary>
        /// Gets the stream's data length
        /// </summary>
        public ulong Length => Source.Length;
        /// <summary>
        /// Tests whether the stream has hit the end-of-file mark
        /// </summary>
        public bool EOF => Source.EOF;

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
                Source.Dispose();
            }

            _disposed = true;
            Close();
        }
    }
}
