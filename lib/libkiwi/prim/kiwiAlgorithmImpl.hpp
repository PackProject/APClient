// Implementation header
#ifndef LIBKIWI_PRIM_ALGORITHM_IMPL_HPP
#define LIBKIWI_PRIM_ALGORITHM_IMPL_HPP

// Declaration header
#ifndef LIBKIWI_PRIM_ALGORITHM_H
#include <libkiwi/prim/kiwiAlgorithm.h>
#endif

namespace kiwi {
namespace detail {

/**
 * @brief Sorts the specified range of random-access iterators (internal
 * implementation)
 *
 * @tparam TIterator Container iterator type (only random-access is supported)
 * @tparam TComparator Iterator comparator type
 * @param begin Beginning of the range
 * @param end End of the range
 * @param comparator Iterator comparator function
 */
template <typename TIterator, typename TComparator>
K_INLINE void SortImpl(TIterator begin, TIterator end, TComparator comparator,
                       RandomAccessIteratorTag) {

    // Standard library implements random-access sort
    std::sort(begin, end, comparator);
}

/**
 * @brief Sorts the specified range of bi-directional iterators (internal
 * implementation)
 *
 * @tparam TIterator Container iterator type (only random-access is supported)
 * @tparam TComparator Iterator comparator type
 * @param begin Beginning of the range
 * @param end End of the range
 * @param comparator Iterator comparator function
 */
template <typename TIterator, typename TComparator>
K_INLINE void SortImpl(TIterator begin, TIterator end, TComparator comparator,
                       BiDirectionalIteratorTag) {

    // Simple bubble sort
    while (true) {
        bool changed = false;

        for (TIterator it = begin; it != end; ++it) {
            TIterator check = it;
            ++check;

            for (; check != end; ++check) {
                if (comparator(*check, *it)) {
                    std::swap(*it, *check);
                    changed = true;
                    break;
                }
            }
        }

        if (!changed) {
            break;
        }
    }
}

} // namespace detail
} // namespace kiwi

#endif
