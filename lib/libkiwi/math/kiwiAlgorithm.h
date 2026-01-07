#ifndef LIBKIWI_MATH_ALGORITHM_H
#define LIBKIWI_MATH_ALGORITHM_H
#include <libkiwi/k_types.h>
#include <libkiwi/util/kiwiRandom.h>

#include <nw4r/math.h>

namespace kiwi {
//! @addtogroup libkiwi_math
//! @{
namespace {
//! @addtogroup libkiwi_math
//! @{

/**
 * @brief Gets the minimum of two values
 *
 * @param rA First value
 * @param rB Second value
 */
template <typename T> K_INLINE const T& Min(const T& rA, const T& rB) {
    return rB < rA ? rB : rA;
}
/**
 * @brief Gets the maximum of two values
 *
 * @param rA First value
 * @param rB Second value
 */
template <typename T> K_INLINE const T& Max(const T& rA, const T& rB) {
    return rA < rB ? rB : rA;
}

/**
 * @brief Calculates the absolute value of the specified value
 *
 * @param rX Initial value
 */
template <typename T> K_INLINE T Abs(const T& rX) {
#ifdef LIBKIWI_TARGET_RVL
    return __abs(rX);
#else
    return rX < 0 ? -rX : rX;
#endif
}

/**
 * @brief Calculates the logarithm (base 10) of the specified value
 *
 * @param rX Initial value
 */
template <typename T> K_INLINE T Log(const T& rX) {
    f32 y = nw4r::math::FLog(static_cast<f32>(rX));
    return static_cast<T>(y);
}

/**
 * @brief Clamps value to range
 *
 * @param rValue Initial value
 * @param rMin Range minimum (exclusive)
 * @param rMax Range maximum (exclusive)
 */
template <typename T>
K_INLINE T Clamp(const T& rValue, const T& rMin, const T& rMax) {
    if (rValue < rMin) {
        return rMin;
    }

    if (rValue > rMax) {
        return rMax;
    }

    return rValue;
}

/**
 * @brief Rounds a value up to the specified alignment
 *
 * @param value Initial value
 * @param align Alignment
 */
template <typename T> K_INLINE T RoundUp(T value, u32 align) {
    return (align + value - 1) & ~(align - 1);
}
/**
 * @brief Rounds a pointer up to the specified alignment
 *
 * @param pValue Initial pointer value
 * @param align Alignment
 */
template <typename T> K_INLINE T* RoundUp(T* pValue, u32 align) {
    uintptr_t value = reinterpret_cast<uintptr_t>(pValue);
    return reinterpret_cast<T*>(RoundUp(value, align));
}

/**
 * @brief Rounds a value down to the specified alignment
 *
 * @param value Initial value
 * @param align Alignment
 */
template <typename T> K_INLINE T RoundDown(T value, u32 align) {
    return value & ~(align - 1);
}
/**
 * @brief Rounds a pointer down to the specified alignment
 *
 * @param pValue Initial pointer value
 * @param align Alignment
 */
template <typename T> K_INLINE T* RoundDown(T* pValue, u32 align) {
    uintptr_t value = reinterpret_cast<uintptr_t>(pValue);
    return reinterpret_cast<T*>(RoundDown(value, align));
}

/**
 * @brief Gets the distance between two pointers
 *
 * @param pStart Start pointer
 * @param pEnd End pointer
 */
K_INLINE ptrdiff_t PtrDistance(const void* pStart, const void* pEnd) {
    return reinterpret_cast<uintptr_t>(pEnd) -
           reinterpret_cast<uintptr_t>(pStart);
}

/**
 * @brief Adds offset to pointer
 *
 * @param pAddr Base pointer
 * @param ofs Offset to apply
 */
K_INLINE void* AddToPtr(void* pAddr, ptrdiff_t ofs) {
    return static_cast<char*>(pAddr) + ofs;
}
/**
 * @brief Adds offset to pointer (const-view)
 *
 * @param pAddr Base pointer
 * @param ofs Offset to apply
 */
K_INLINE const void* AddToPtr(const void* pAddr, ptrdiff_t ofs) {
    return static_cast<const char*>(pAddr) + ofs;
}

/**
 * @brief Adds offset to pointer
 *
 * @tparam T Type of resulting pointer
 * @param pAddr Base pointer
 * @param ofs Offset to apply
 */
template <typename T> K_INLINE T* AddToPtr(void* pAddr, ptrdiff_t ofs) {
    return reinterpret_cast<T*>(static_cast<char*>(pAddr) + ofs);
}
/**
 * @brief Adds offset to pointer (const-view)
 *
 * @tparam T Type of resulting pointer
 * @param pAddr Base pointer
 * @param ofs Offset to apply
 */
template <typename T>
K_INLINE const T* AddToPtr(const void* pAddr, ptrdiff_t ofs) {
    return reinterpret_cast<const T*>(static_cast<const char*>(pAddr) + ofs);
}

/**
 * @brief Performs the Fisher-Yates shuffle algorithm to generate a random
 * permutation of the specified values
 *
 * @tparam TElem Shuffled array element type
 * @tparam ElemNum Length of shuffled array
 *
 * @param[in,out] rArray Input array
 */
template <typename TElem, u32 ElemNum>
K_INLINE void Shuffle(TElem (&rArray)[ElemNum]) {
    K_ASSERT(ElemNum > 0);

    Random r;
    for (u32 i = ElemNum - 1; i >= 1; i--) {
        u32 j = r.NextU32(i + 1);
        std::swap(rArray[j], rArray[i]);
    }
}

/**
 * @brief Performs the Fisher-Yates shuffle algorithm to generate a random
 * permutation of numbers in the range [0, {array-length})
 *
 * @tparam TElem Shuffled array element type
 * @tparam ElemNum Length of shuffled array
 *
 * @param[out] rArray Input array
 */
template <typename TElem, u32 ElemNum>
K_INLINE void InitAndShuffle(TElem (&rArray)[ElemNum]) {
    for (u32 i = 0; i < ElemNum; i++) {
        rArray[i] = i;
    }

    Shuffle(rArray);
}

/**
 * @brief "Un-shuffles" a previously shuffled array by moving values matching
 * the specified keys back to their original position in the array.
 *
 * @tparam TKey Key element type
 * @tparam KeyNum Length of keys array
 * @tparam TElem Shuffled array element type
 * @tparam ElemNum Length of shuffled array
 *
 * @param rKeys Keys to unshuffle
 * @param[in, out] rArray Shuffled array
 */
template <typename TKey, u32 KeyNum, typename TElem, u32 ElemNum>
K_INLINE void UnShuffle(const TKey (&rKeys)[KeyNum], TElem (&rArray)[ElemNum]) {
    while (true) {
        bool changed = false;

        for (u32 i = 0; i < ElemNum; i++) {
            if (rArray[i] == i) {
                continue;
            }

            // TODO: Binary search through the keys?
            for (u32 j = 0; j < KeyNum; j++) {
                if (rArray[i] == rKeys[j]) {
                    std::swap(rArray[i], rArray[rArray[i]]);
                    changed = true;
                }
            }
        }

        if (!changed) {
            break;
        }
    }
}

//! @}
} // namespace
//! @}
} // namespace kiwi

#endif
