using LibWorkBench.Core.Models.Binary.Details;
using LibWorkBench.IO.Streams;

namespace LibWorkBench.Core.Models.Binary
{
    /// <summary>
    /// Base class for binary-view models with blocks
    /// </summary>
    public abstract class BlockBinaryModel : BinaryModel
    {
        /// <summary>
        /// Block manager
        /// </summary>
        protected readonly BinaryBlockManager _manager;

        /// <summary>
        /// Number of blocks saved during the most recent Write operation
        /// </summary>
        public uint BlocksWritten { get; set; } = 0;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="factory">Factory used for block creation</param>
        public BlockBinaryModel(BinaryBlockFactory factory)
        {
            factory.Model = this;
            _manager = new BinaryBlockManager(factory);
        }

        /// <summary>
        /// Gets the first (eldest) block of the specified type
        /// </summary>
        /// <typeparam name="T">Block type</typeparam>
        /// <param name="create">Whether to create a new block if none exist</param>
        /// <returns>First owned block</returns>
        public T GetOne<T>(bool create = false)
            where T : BinaryBlock, new()
        {
            return _manager.GetOne<T>(create);
        }

        /// <summary>
        /// Gets the first (eldest) block of the specified type
        /// </summary>
        /// <param name="type">Block type</param>
        /// <param name="create">Whether to create a new block if none exist</param>
        /// <returns>First owned block</returns>
        public BinaryBlock GetOne(Type type, bool create = false)
        {
            return _manager.GetOne(type, create);
        }

        /// <summary>
        /// Gets all blocks of the specified type
        /// </summary>
        /// <typeparam name="T">Block type</typeparam>
        /// <param name="create">Whether to create a new block if none exist</param>
        /// <returns>First owned block</returns>
        public List<BinaryBlock> GetAll<T>(bool create = false)
            where T : BinaryBlock, new()
        {
            return _manager.GetAll<T>(create);
        }

        /// <summary>
        /// Gets all blocks of the specified type
        /// </summary>
        /// <param name="type">Block type</param>
        /// <param name="create">Whether to create a new block if none exist</param>
        /// <returns>First owned block</returns>
        public List<BinaryBlock> GetAll(Type type, bool create = false)
        {
            return _manager.GetAll(type, create);
        }

        /// <summary>
        /// Removes all blocks of the specified type
        /// </summary>
        /// <typeparam name="T">Block type</typeparam>
        public void RemoveAll<T>()
            where T : BinaryBlock, new()
        {
            _manager.RemoveAll<T>();
        }

        /// <summary>
        /// Removes all blocks of the specified type
        /// </summary>
        /// <param name="type">Block type</param>
        public void RemoveAll(Type type)
        {
            _manager.RemoveAll(type);
        }

        /// <summary>
        /// Creates a new block of the specified type
        /// </summary>
        /// <typeparam name="T">Block type</typeparam>
        /// <param name="unmanaged">Prevent the model from managing the new block</param>
        /// <returns>New block</returns>
        public T CreateBlock<T>(bool unmanaged = false)
            where T : BinaryBlock, new()
        {
            T block = _manager.CreateBlock<T>(unmanaged);
            block.Model = this;
            return block;
        }

        /// <summary>
        /// Creates a new block of the type matching the specified signature
        /// </summary>
        /// <param name="signature">Block type magic/signature</param>
        /// <param name="unmanaged">Prevent the model from managing the new block</param>
        /// <returns>New block</returns>
        public BinaryBlock CreateBlock(string signature,
                                       bool unmanaged = false)
        {
            BinaryBlock block = _manager.CreateBlock(signature, unmanaged);
            block.Model = this;
            return block;
        }

        /// <summary>
        /// Creates a new block of the specified type
        /// </summary>
        /// <param name="signature">Block type</param>
        /// <param name="unmanaged">Prevent the model from managing the new block</param>
        /// <returns>New block</returns>
        public BinaryBlock CreateBlock(Type type, bool unmanaged = false)
        {
            BinaryBlock block = _manager.CreateBlock(type, unmanaged);
            block.Model = this;
            return block;
        }

        /// <summary>
        /// Allows additional logic after reading each block in the model
        /// </summary>
        /// <param name="reader">Binary stream that contained the block data</param>
        /// <param name="block">Block that was just read</param>
        public virtual void ReadBlockCallback(ReadStream reader, BinaryBlock block)
        {
        }

        /// <summary>
        /// Allows additional logic after writing each block in the model
        /// </summary>
        /// <param name="writer">Binary stream that will contain the block data</param>
        /// <param name="block">Block that was just written</param>
        public virtual void WriteBlockCallback(WriteStream writer, BinaryBlock block)
        {
        }
    }
}
