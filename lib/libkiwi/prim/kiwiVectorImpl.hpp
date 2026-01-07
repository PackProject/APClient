// Implementation header
#ifndef LIBKIWI_PRIM_VECTOR_IMPL_HPP
#define LIBKIWI_PRIM_VECTOR_IMPL_HPP

// Declaration header
#ifndef LIBKIWI_PRIM_VECTOR_H
#include <libkiwi/prim/kiwiVector.h>
#endif

#include <cstring>

namespace kiwi {

/**
 * @brief Destructor
 */
template <typename T> K_INLINE TVector<T>::~TVector() {
    Clear();

    delete mpData;
    mpData = nullptr;
}

/**
 * @brief Vector copy assignment
 *
 * @param rOther Vector to copy
 */
template <typename T>
K_INLINE TVector<T>& TVector<T>::operator=(const TVector& rOther) {
    // Release old data
    Clear();
    Reserve(rOther.mSize);

    if (rOther.mSize > 0) {
        K_ASSERT_PTR(rOther.mpData);
        std::memcpy(mpData, rOther.mpData, rOther.mSize * sizeof(T));
    }

    mSize = rOther.mSize;
    return *this;
}

/**
 * @brief Reserves space for elements in the vector
 *
 * @param capacity New capacity
 */
template <typename T> K_INLINE void TVector<T>::Reserve(u32 capacity) {
    if (mCapacity >= capacity) {
        return;
    }

    u8* pBuffer = new u8[capacity * sizeof(T)];
    K_ASSERT_PTR(pBuffer);

    // Copy in old data
    if (mSize > 0) {
        K_ASSERT_PTR(mpData);
        std::memcpy(pBuffer, mpData, mSize * sizeof(T));
        delete mpData;
    }

    mpData = pBuffer;
    mCapacity = capacity;
}

/**
 * @brief Erases the last element from the vector
 *
 * @returns The element that was just erased
 */
template <typename T> K_INLINE T TVector<T>::PopBack() {
    K_ASSERT(!Empty());

    Iterator back = --End();
    T element = *back;

    Erase(back);
    return element;
}

/**
 * @brief Removes the first occurrence of an element from the vector
 *
 * @param rElement Element to remove
 * @return Whether the element was found and removed
 */
template <typename T> K_INLINE bool TVector<T>::Remove(const T& rElement) {
    K_FOREACH (it, *this) {
        if (*it == rElement) {
            Erase(it);
            return true;
        }
    }

    return false;
}

/**
 * @brief Removes all elements from the list satisfying the condition
 *
 * @param pPredicate Function to test if the element should be removed
 * @return How many elements were removed
 */
template <typename T>
K_INLINE u32 TVector<T>::RemoveIf(bool (*pPredicate)(const T&)) {
    K_ASSERT_PTR(pPredicate);

    Iterator it = Begin();
    u32 eraseNum = 0;

    while (it != End()) {
        if (!pPredicate(*it)) {
            ++it;
            continue;
        }

        it = Erase(it);
        eraseNum++;
    }

    return eraseNum;
}

/**
 * @brief Inserts a new element at the specified position
 * @details Value is inserted before the given iterator
 *
 * @param it Iterator at which to insert the element
 * @param rElement Element to insert
 * @returns Iterator to the new element
 */
template <typename T>
K_INLINE typename TVector<T>::Iterator TVector<T>::Insert(Iterator it,
                                                          const T& rElement) {
    // Fit one more element
    Reserve(mSize + 1);
    K_ASSERT_PTR(mpData);

    // Front/middle insert requires copying forward
    if (it.mIndex < mSize) {
        std::memcpy(Data() + it.mIndex + 1, //
                    Data() + it.mIndex,     //
                    (mSize - it.mIndex) * sizeof(T));
    }

    // Construct in-place
    new (&Data()[it.mIndex]) T(rElement);
    mSize++;

    // Input iterator will end up pointing at the new element
    return it;
}

/**
 * @brief Erases range of nodes
 *
 * @param begin Beginning of range (inclusive)
 * @param end End of range (exclusive)
 * @return Iterator to end of range
 */
template <typename T>
K_INLINE typename TVector<T>::Iterator TVector<T>::Erase(Iterator begin,
                                                         Iterator end) {
    K_ASSERT(begin <= end);

    // Destroy objects
    for (Iterator it = begin; it != end; ++it) {
        (*it).~T();
    }

    // Front/middle erase requires copying back
    if (end.mIndex < mSize) {
        std::memcpy(Data() + begin.mIndex, //
                    Data() + end.mIndex,   //
                    (mSize - end.mIndex) * sizeof(T));
    }

    mSize -= end - begin;

    // Next element will end up at the range start
    return begin;
}

} // namespace kiwi

#endif
