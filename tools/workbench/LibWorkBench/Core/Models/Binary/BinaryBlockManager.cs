using LibWorkBench.Core.Models.Binary.Details;

namespace LibWorkBench.Core.Models.Binary
{
    /// <summary>
    /// Binary block manager
    /// </summary>
    public class BinaryBlockManager
    {
        /// <summary>
        /// Factory used for block creation
        /// </summary>
        private readonly BinaryBlockFactory _factory;

        /// <summary>
        /// Blocks owned by this manager.
        /// This maps a block type to all known instances.
        /// </summary>
        public OrderedDictionary<Type, List<BinaryBlock>> Blocks { get; } = new();

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="factory">Factory used for block creation</param>
        public BinaryBlockManager(BinaryBlockFactory factory)
        {
            _factory = factory;
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
            return (T)GetAll<T>(create).First();
        }

        /// <summary>
        /// Gets the first (eldest) block of the specified type
        /// </summary>
        /// <param name="type">Block type</param>
        /// <param name="create">Whether to create a new block if none exist</param>
        /// <returns>First owned block</returns>
        public BinaryBlock GetOne(Type type, bool create = false)
        {
            return GetAll(type, create).First();
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
            return GetAll(typeof(T), create);
        }

        /// <summary>
        /// Gets all blocks of the specified type
        /// </summary>
        /// <param name="type">Block type</param>
        /// <param name="create">Whether to create a new block if none exist</param>
        /// <returns>First owned block</returns>
        public List<BinaryBlock> GetAll(Type type, bool create = false)
        {
            // No blocks of this type have ever been created
            bool noList = !Blocks.ContainsKey(type);
            // All blocks of this type have been removed somehow
            bool noBlocks = noList || Blocks[type].Count == 0;

            if ((noList || noBlocks) && !create)
            {
                throw new InvalidOperationException(
                    $"No blocks of type {type.FullName}, and we can't create");
            }

            // Need to create a list if this is the first block ever
            if (noList)
            {
                Blocks[type] = new List<BinaryBlock>();
            }

            List<BinaryBlock> blockList = Blocks[type];

            // Create the first block only if requested to do so
            if (noList && create)
            {
                blockList.Add(_factory.CreateBlock(type));
            }

            return blockList;
        }

        /// <summary>
        /// Removes all blocks of the specified type
        /// </summary>
        /// <typeparam name="T">Block type</typeparam>
        public void RemoveAll<T>()
            where T : BinaryBlock, new()
        {
            Blocks.Remove(typeof(T));
        }

        /// <summary>
        /// Removes all blocks of the specified type
        /// </summary>
        /// <param name="type">Block type</param>
        public void RemoveAll(Type type)
        {
            Blocks.Remove(type);
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
            T block = _factory.CreateBlock<T>();

            if (!unmanaged)
            {
                RegisterBlock(block);
            }

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
            BinaryBlock block = _factory.CreateBlock(signature);

            if (!unmanaged)
            {
                RegisterBlock(block);
            }

            return block;
        }

        /// <summary>
        /// Creates a new block of the specified type
        /// </summary>
        /// <param name="type">Block type</param>
        /// <param name="unmanaged">Prevent the model from managing the new block</param>
        /// <returns>New block</returns>
        public BinaryBlock CreateBlock(Type type, bool unmanaged = false)
        {
            BinaryBlock block = _factory.CreateBlock(type);

            if (!unmanaged)
            {
                RegisterBlock(block);
            }

            return block;
        }

        /// <summary>
        /// Registers a new block with this model
        /// </summary>
        /// <param name="block">New block</param>
        private void RegisterBlock(BinaryBlock block)
        {
            // Gets the derived type (even through a base class handle)
            Type blockType = block.GetType();

            // Need to create a list if this is the first block ever
            if (!Blocks.ContainsKey(blockType))
            {
                Blocks[blockType] = new List<BinaryBlock>();
            }

            Blocks[blockType].Add(block);
        }
    }
}
