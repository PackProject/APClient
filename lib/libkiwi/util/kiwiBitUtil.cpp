#include <libkiwi.h>

namespace kiwi {

/**
 * @brief Counts the number of set bits in the bitfield
 *
 * @param bits Bitfield
 */
template <typename T> u32 BitUtil<T>::CountOne(T bits) {
    u32 count = 0;

    for (; bits != 0; bits >>= 1) {
        count += bits & 1;
    }

    return count;
}

/**
 * @brief Counts the number of unset bits in the bitfield
 *
 * @param bits Bitfield
 */
template <typename T> u32 BitUtil<T>::CountZero(T bits) {
    return CountOne(~bits);
}

/**
 * @brief Counts the number of leading zeroes in the bitfield
 *
 * @param bits Bitfield
 */
template <typename T> u32 BitUtil<T>::CountLeftZero(T bits) {
    K_REGISTER u32 count = 0;

#ifdef LIBKIWI_TARGET_RVL
    K_REGISTER u32 bits_ = static_cast<u32>(bits);

    K_ASM(
        cntlzw count, bits_
    )

    // Adjust for GPR size
    count -= 32 - BIT_SIZE;
#else
    u32 mask = 1 << (BIT_SIZE - 1);

    for (; mask != 0 && (bits & mask) == 0; mask >>= 1) {
        ++count;
    }
#endif

    return count;
}

/**
 * @brief Counts the number of leading ones in the bitfield
 *
 * @param bits Bitfield
 */
template <typename T> u32 BitUtil<T>::CountLeftOne(T bits) {
    return CountLeftZero(~bits);
}

/**
 * @brief Counts the number of trailing zeroes in the bitfield
 *
 * @param bits Bitfield
 */
template <typename T> u32 BitUtil<T>::CountRightZero(T bits) {
    u32 count = 0;
    u32 mask = 1 << 0;

    for (; (bits & mask) == 0; mask <<= 1) {
        if (++count >= BIT_SIZE) {
            break;
        }
    }

    return count;
}

/**
 * @brief Counts the number of trailing ones in the bitfield
 *
 * @param bits Bitfield
 */
template <typename T> u32 BitUtil<T>::CountRightOne(T bits) {
    return CountRightZero(~bits);
}

/**
 * @brief Picks a random set bit from the bitfield
 *
 * @param bits Bitfield
 */
template <typename T> T BitUtil<T>::PickRandom(T bits) {
    u32 max = CountOne(bits);

    // No set bits
    if (max == 0) {
        return 0;
    }

    // Choice means n'th set bit
    u32 choice = 1 + Random().NextU32(max);

    u32 mask = 1 << 0;

    for (u32 i = 0; i < choice; mask <<= 1) {
        if (bits & mask) {
            if (++i >= choice) {
                break;
            }
        }
    }

    return mask;
}

/**
 * @brief Creates a random bitfield
 */
template <typename T> T BitUtil<T>::MakeRandom() {
    T bits = static_cast<T>(0);
    Random r;

    for (u32 i = 0; i < BIT_SIZE; i++, bits <<= 1) {
        bits |= r.CoinFlip();
    }

    return bits;
}

/**
 * @brief Sets the first (left-to-right) unset bit
 *
 * @param bits Bitfield
 */
template <typename T> T BitUtil<T>::SetFirstUnset(T bits) {
    u32 mask = 1 << (BIT_SIZE - 1);

    for (; mask != 0; mask >>= 1) {
        if ((bits & mask) == 0) {
            return bits | mask;
        }
    }

    return bits;
}

/**
 * @brief Sets the last (right-to-left) unset bit
 *
 * @param bits Bitfield
 */
template <typename T> T BitUtil<T>::SetLastUnset(T bits) {
    u32 count = 0;
    u32 mask = 1 << 0;

    for (; count++ < BIT_SIZE; mask <<= 1) {
        if ((bits & mask) == 0) {
            return bits | mask;
        }
    }

    return bits;
}

// Instantiate functions for supported bitfield types
template class BitUtil<u8>;
template class BitUtil<u16>;
template class BitUtil<u32>;

} // namespace kiwi
