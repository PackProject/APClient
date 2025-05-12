#ifndef LIBKIWI_PRIM_BIT_FLAG_H
#define LIBKIWI_PRIM_BIT_FLAG_H
#include <libkiwi/debug/kiwiAssert.h>
#include <libkiwi/k_types.h>
#include <libkiwi/util/kiwiBitUtil.h>
#include <libkiwi/util/kiwiRandom.h>

namespace kiwi {
//! @addtogroup libkiwi_prim
//! @{

/**
 * @brief Bit flags wrapper
 *
 * @tparam T Value type
 * @tparam N Number of bits to hold (defaults to max)
 */
template <typename T, u32 N = sizeof(T) * 8> class TBitFlag {
public:
    /**
     * @brief Constructor
     *
     * @param value Initial value
     */
    TBitFlag(T value = T()) {
        SetDirect(value);
    }

    operator T() const {
        return GetDirect();
    }
    TBitFlag& operator=(T value) {
        SetDirect(value);
        return *this;
    }

    /**
     * @brief Sets the bitfield directly
     *
     * @param value New bitfield
     */
    void SetDirect(T bits) {
        mValue = bits & MakeMask();
    }
    /**
     * @brief Gets the bitfield directly
     *
     * @return Bitfield
     */
    T GetDirect() const {
        return mValue;
    }

    /**
     * @brief Sets all bits
     */
    void SetAll() {
        SetDirect(static_cast<T>(~0));
    }
    /**
     * @brief Clears all bits
     */
    void ResetAll() {
        SetDirect(T());
    }

    /**
     * @brief Sets the specified bit
     *
     * @param i Bit index
     * @return Self for method chaining
     */
    TBitFlag& SetBit(u32 i) {
        K_ASSERT(i < N);
        mValue |= 1 << i;
        return *this;
    }
    /**
     * @brief Clears the specified bit
     *
     * @param i Bit index
     * @return Self for method chaining
     */
    TBitFlag& ResetBit(u32 i) {
        K_ASSERT(i < N);
        mValue &= ~(1 << i);
        return *this;
    }
    /**
     * @brief Toggles the specified bit
     *
     * @param i Bit index
     * @return Self for method chaining
     */
    TBitFlag& ToggleBit(u32 i) {
        K_ASSERT(i < N);
        mValue ^= 1 << i;
        return *this;
    }

    /**
     * @brief Changes the specified bit
     *
     * @param i Bit index
     * @param value New bit value
     * @return Self for method chaining
     */
    TBitFlag& ChangeBit(u32 i, bool value) {
        K_ASSERT(i < N);

        if (value) {
            SetBit(i);
        } else {
            ResetBit(i);
        }

        return *this;
    }

    /**
     * @brief Tests whether the specified bit is set
     *
     * @param i Bit index
     * @return Bit value
     */
    bool GetBit(u32 i) const {
        K_ASSERT(i < N);
        return mValue & 1 << i;
    }

    /**
     * @brief Counts the number of bits which are set
     *
     * @return Number of bits set
     */
    u32 Count() const {
        return BitUtil::Count(mValue & MakeMask());
    }

    /**
     * @brief Randomizes the bits
     */
    void Randomize() {
        Random rnd;
        u32 value = 0;

        for (u32 i = 0; i < N; i++) {
            value |= rnd.CoinFlip();
            value <<= 1;
        }

        SetDirect(value);
    }

private:
    /**
     * @brief Creates a bitmask for the specified bit count
     */
    static u32 MakeMask() {
        return (1 << N) - 1;
    }

private:
    //! Bits value
    T mValue;
};

//! @}
} // namespace kiwi

#endif
