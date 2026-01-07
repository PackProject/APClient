using System.Numerics;

namespace LibWorkBench.Utility
{
    /// <summary>
    /// Bitflag set
    /// </summary>
    /// <typeparam name="TValue">Bitfield type</typeparam>
    /// <typeparam name="TEnum">Enum type</typeparam>
    public sealed class BitFlag<TValue, TEnum>
        where TValue : unmanaged, IEqualityOperators<TValue, TValue, bool>, IBitwiseOperators<TValue, TValue, TValue>
        where TEnum : Enum
    {
        /// <summary>
        /// Bitfield value
        /// </summary>
        private TValue _value;

        /// <summary>
        /// Constructor
        /// </summary>
        public BitFlag()
        {
            MakeAllZero();
        }

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="value">Initial value</param>
        public BitFlag(TValue value)
        {
            SetDirect(value);
        }

        /// <summary>
        /// Clears all bits in the bitfield
        /// </summary>
        public void MakeAllZero()
        {
            SetDirect(default);
        }

        /// <summary>
        /// Sets the bitfield value directly
        /// </summary>
        /// <param name="value">New value</param>
        public void SetDirect(TValue value)
        {
            _value = value;
        }

        /// <summary>
        /// Gets the bitfield value directly
        /// </summary>
        /// <returns></returns>
        public TValue GetDirect()
        {
            return _value;
        }

        /// <summary>
        /// Sets the specified bit
        /// </summary>
        /// <param name="idx">Bit index</param>
        public void SetBit(TEnum idx)
        {
            _value |= MakeMask(idx);
        }

        /// <summary>
        /// Clears the specified bit
        /// </summary>
        /// <param name="idx">Bit index</param>
        public void ResetBit(TEnum idx)
        {
            _value &= ~MakeMask(idx);
        }

        /// <summary>
        /// Toggles the specified bit
        /// </summary>
        /// <param name="idx">Bit index</param>
        public void ToggleBit(TEnum idx)
        {
            _value ^= MakeMask(idx);
        }

        /// <summary>
        /// Changes the value of the specified bit
        /// </summary>
        /// <param name="idx">Bit index</param>
        /// <param name="value">Bit value</param>
        public void ChangeBit(TEnum idx, bool value)
        {
            if (value)
            {
                SetBit(idx);
            }
            else
            {
                ResetBit(idx);
            }
        }

        /// <summary>
        /// Tests whether the specified bit is set
        /// </summary>
        /// <param name="idx">Bit index</param>
        /// <returns>Value of the specified bit</returns>
        public bool GetBit(TEnum idx)
        {
            return (_value & MakeMask(idx)) != default;
        }

        /// <summary>
        /// Creates a mask to access the specified bit
        /// </summary>
        /// <param name="idx">Bit index</param>
        /// <returns>Bitmask</returns>
        private static TValue MakeMask(TEnum idx)
        {
            return (TValue)(dynamic)(1 << (int)(dynamic)idx);
        }
    }
}
