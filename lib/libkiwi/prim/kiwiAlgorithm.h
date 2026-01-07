#ifndef LIBKIWI_PRIM_ALGORITHM_H
#define LIBKIWI_PRIM_ALGORITHM_H
#include <libkiwi/debug/kiwiAssert.h>
#include <libkiwi/k_types.h>
#include <libkiwi/prim/kiwiIterator.h>

#include <algorithm>

namespace kiwi {
//! @addtogroup libkiwi_prim
//! @{

namespace detail {
//! @addtogroup libkiwi_prim
//! @{

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
                       RandomAccessIteratorTag);

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
                       BiDirectionalIteratorTag);

//! @}
} // namespace detail

/**
 * @brief Comparator function for sorting containers in ascending order
 *
 * @tparam T Container element type
 * @param rLhs Left-hand side element
 * @param rRhs Right-hand side element
 * @return Whether the left-hand side element should appear first in the order
 */
template <typename T> K_INLINE bool Less(const T& rLhs, const T& rRhs) {
    return rLhs < rRhs;
}

/**
 * @brief Comparator function for sorting containers in ascending order
 *
 * @tparam T Container element type
 * @param rLhs Left-hand side element
 * @param rRhs Right-hand side element
 * @return Whether the left-hand side element should appear first in the order
 */
template <typename T> K_INLINE bool Greater(const T& rLhs, const T& rRhs) {
    return rLhs > rRhs;
}

/**
 * @brief Sorts the specified range of a collection using the provided
 * comparator function to order elements
 * @details The sort order defaults to ascending order when a comparator is not
 * specified.
 *
 * @tparam TIterator Container iterator type (only random-access is supported)
 * @tparam TComparator Iterator comparator type
 * @param begin Beginning of the range
 * @param end End of the range
 * @param comparator Iterator comparator function
 */
template <typename TIterator, typename TComparator>
K_INLINE void Sort(TIterator begin, TIterator end,
                   TComparator comparator = kiwi::Less) {

    detail::SortImpl(begin, end, comparator, typename TIterator::TagType());
}

//! @}
} // namespace kiwi

// Implementation header
#ifndef LIBKIWI_PRIM_ALGORITHM_IMPL_HPP
#include <libkiwi/prim/kiwiAlgorithmImpl.hpp>
#endif

#endif
