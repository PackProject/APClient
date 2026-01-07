using LibWorkBench.Core.Models.Binary.Details;

namespace LibWorkBench.Core.Models.Binary
{
    /// <summary>
    /// Binary block factory.
    /// Allows creation of block objects from their file signatures ("magic").
    /// </summary>
    public class BinaryBlockFactory
    {
        /// <summary>
        /// Block type registry.
        /// Maps a block's signature ("magic") to its class type
        /// </summary>
        private readonly OrderedDictionary<string, Type> _registry = new();

        /// <summary>
        /// Binary model which owns all created blocks
        /// </summary>
        public BlockBinaryModel? Model = null;

        /// <summary>
        /// Registers a new block type for creation via this factory
        /// </summary>
        /// <typeparam name="T">Binary block type</typeparam>
        /// <exception cref="InvalidOperationException">The block type has already been registered</exception>
        public void RegisterBlock<T>()
            where T : BinaryBlock, new()
        {
            Type blockType = typeof(T);
            string signature = BinaryBlock.GetProfileStatic<T>().Signature;

            if (_registry.ContainsKey(signature))
            {
                throw new InvalidOperationException(
                    $"Block {blockType.FullName} has already been registered");
            }

            _registry[signature] = blockType;
        }

        /// <summary>
        /// Creates a new block of the specified type
        /// </summary>
        /// <typeparam name="T">Binary block type</typeparam>
        /// <returns>New block</returns>
        public T CreateBlock<T>()
            where T : BinaryBlock, new()
        {
            return (T)CreateBlock(typeof(T));
        }

        /// <summary>
        /// Creates a new block of the type matching the specified signature
        /// </summary>
        /// <param name="signature">Block type magic/signature</param>
        /// <returns>New block</returns>
        /// <exception cref="InvalidOperationException">No block type matches the signature</exception>
        /// <exception cref="InvalidOperationException">The block could not be created</exception>
        public BinaryBlock CreateBlock(string signature)
        {
            if (!_registry.ContainsKey(signature))
            {
                throw new InvalidOperationException(
                    $"No block matches the signature {signature}");
            }

            return CreateBlock(_registry[signature]);
        }

        /// <summary>
        /// Creates a new block of the specified type
        /// </summary>
        /// <param name="type">Block type</param>
        /// <returns>New block</returns>
        /// <exception cref="InvalidOperationException">The block could not be created</exception>
        public BinaryBlock CreateBlock(Type type)
        {
            object? obj = Activator.CreateInstance(type);
            if (obj == null)
            {
                throw new InvalidOperationException(
                    $"Failed to instantiate block {type.FullName}");
            }

            BinaryBlock block = (BinaryBlock)obj;
            block.Model = Model;

            return block;
        }
    }
}
