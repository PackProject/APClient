#ifndef LIBKIWI_UTIL_BIT_UTIL_H
#define LIBKIWI_UTIL_BIT_UTIL_H
#include <libkiwi/k_types.h>

namespace kiwi {
//! @addtogroup libkiwi_util
//! @{

/**
 * @brief Bit utilities
 *
 * @tparam T Bitfield type
 */
template <typename T> class BitUtil {
public:
    //! Size of the bitfield type, in bits
    static const int BIT_SIZE = sizeof(T) * 8;

public:
    /**
     * @brief Counts the number of set bits in the bitfield
     *
     * @param bits Bitfield
     */
    static u32 CountOne(T bits);
    /**
     * @brief Counts the number of unset bits in the bitfield
     *
     * @param bits Bitfield
     */
    static u32 CountZero(T bits);

    /**
     * @brief Counts the number of leading zeroes in the bitfield
     *
     * @param bits Bitfield
     */
    static u32 CountLeftZero(T bits);
    /**
     * @brief Counts the number of leading ones in the bitfield
     *
     * @param bits Bitfield
     */
    static u32 CountLeftOne(T bits);

    /**
     * @brief Counts the number of trailing zeroes in the bitfield
     *
     * @param bits Bitfield
     */
    static u32 CountRightZero(T bits);
    /**
     * @brief Counts the number of trailing ones in the bitfield
     *
     * @param bits Bitfield
     */
    static u32 CountRightOne(T bits);

    /**
     * @brief Picks a random set bit from the bitfield
     *
     * @param bits Bitfield
     */
    static T PickRandom(T bits);

    /**
     * @brief Creates a random bitfield
     */
    static T MakeRandom();

    /**
     * @brief Sets the first (left-to-right) unset bit
     *
     * @param bits Bitfield
     */
    static T SetFirstUnset(T bits);
    /**
     * @brief Sets the last (right-to-left) unset bit
     *
     * @param bits Bitfield
     */
    static T SetLastUnset(T bits);
};

//! @}
} // namespace kiwi

#endif
