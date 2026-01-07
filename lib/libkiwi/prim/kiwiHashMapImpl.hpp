// Implementation header
#ifndef LIBKIWI_PRIM_HASH_MAP_IMPL_HPP
#define LIBKIWI_PRIM_HASH_MAP_IMPL_HPP

// Declaration header
#ifndef LIBKIWI_PRIM_HASH_MAP_H
#include <libkiwi/prim/kiwiHashMap.h>
#endif

namespace kiwi {

/******************************************************************************
 *
 * IteratorImpl
 *
 ******************************************************************************/

/**
 * @brief Constructor
 *
 * @param pHashMap Parent hash map
 * @param index Bucket index
 */
template <typename TKey, typename TValue>
template <typename TItemValue>
K_INLINE THashMap<TKey, TValue>::IteratorImpl<TItemValue>::IteratorImpl(
    THashMap* pHashMap, u32 index)
    : mpHashMap(pHashMap), mIndex(index), mpBucket(nullptr) {

    K_ASSERT_PTR(mpHashMap);
    K_ASSERT(mIndex <= mpHashMap->Capacity());

    // Grab the targeted bucket
    if (mIndex < mpHashMap->Capacity()) {
        mpBucket = &mpHashMap->mpBuckets[mIndex];
    }

    // Advance to the first non-empty bucket
    if (mpBucket != nullptr && !mpBucket->item.HasValue()) {
        Next();
    }
}

/**
 * @brief Increments the iterator once
 */
template <typename TKey, typename TValue>
template <typename TItemValue>
K_INLINE void THashMap<TKey, TValue>::IteratorImpl<TItemValue>::Next() {
    K_ASSERT_PTR(mpHashMap);

    // Ignore end/invalid iterators
    if (mpBucket == nullptr || mIndex >= mpHashMap->Capacity()) {
        return;
    }

    // Find the next available bucket with a key
    do {
        // Try the separate chaining buckets first
        mpBucket = mpBucket->pNext;

        for (; mpBucket != nullptr; mpBucket = mpBucket->pNext) {
            if (mpBucket->item.HasValue()) {
                return;
            }
        }

        // Move to the next top-level bucket if the chains had nothing
        if (++mIndex >= mpHashMap->Capacity()) {
            // Ignore end/invalid iterators
            return;
        }

        mpBucket = &mpHashMap->mpBuckets[mIndex];

    } while (mpBucket == nullptr || !mpBucket->item.HasValue());
}

/******************************************************************************
 *
 * THashMap
 *
 ******************************************************************************/

/**
 * @brief Assignment operator
 * @details Copy assignment
 *
 * @param rOther Map to copy from
 */
template <typename TKey, typename TValue>
K_INLINE THashMap<TKey, TValue>&
THashMap<TKey, TValue>::operator=(const THashMap& rOther) {
    K_ASSERT(rOther.mCapacity > 0);
    K_ASSERT(rOther.mCapacity < HASH_MAX);

    // Release old data
    Clear();

    mCapacity = rOther.mCapacity;
    mpBuckets = new HashBucket[mCapacity];
    K_ASSERT_PTR(mpBuckets);

    K_FOREACH (it, rOther) {
        Insert(it->key, it->value);
    }

    return *this;
}

/**
 * @brief Erases all elements from the map
 */
template <typename TKey, typename TValue>
K_INLINE void THashMap<TKey, TValue>::Clear() {
    for (u32 i = 0; i < mCapacity; i++) {
        mpBuckets[i].Destroy();
    }

    mSize = 0;
}

/**
 * @brief Removes an element by key
 *
 * @param rKey Key
 * @param[out] pRemoved Removed value
 * @return Success
 */
template <typename TKey, typename TValue>
K_INLINE bool THashMap<TKey, TValue>::Remove(const TKey& rKey,
                                             TValue* pRemoved) {
    HashBucket* pBucket = Search(rKey);

    if (pBucket == nullptr) {
        return false;
    }

    if (pRemoved != nullptr) {
        *pRemoved = (*pBucket->item).value;
    }

    // Clear key/value pair for later re-use
    pBucket->item.Reset();

    mSize--;
    return true;
}

/**
 * @brief Removes all elements from the map satisfying the condition
 *
 * @param pPredicate Function to test if the element should be removed
 * @return How many elements were removed
 */
template <typename TKey, typename TValue>
K_INLINE u32
THashMap<TKey, TValue>::RemoveIf(bool (*pPredicate)(const HashItem&)) {
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
 * @brief Erases the element at the specified iterator's position
 *
 * @param it Iterator at which to erase the element
 * @return Iterator to the next element after the erased element
 */
template <typename TKey, typename TValue>
K_INLINE typename THashMap<TKey, TValue>::Iterator
THashMap<TKey, TValue>::Erase(Iterator it) {
    // Ignore invalid iterators
    if (it.mpBucket == nullptr) {
        return it;
    }

    it.mpBucket->item.Reset();

    mSize--;
    return ++it;
}

/**
 * @brief Searches for an existing element by key
 *
 * @param rKey Key
 * @return Value if it exists
 */
template <typename TKey, typename TValue>
TValue* THashMap<TKey, TValue>::Find(const TKey& rKey) const {
    HashBucket* pBucket = Search(rKey);

    if (pBucket == nullptr) {
        return nullptr;
    }

    return &(*pBucket->item).value;
}

/**
 * @brief Accesses an element by key
 * @details If the element doesn't exist, the provided default value is
 * returned.
 *
 * @param rKey Key
 * @param rDefault Default value
 * @return Existing element, or default value
 */
template <typename TKey, typename TValue>
TValue THashMap<TKey, TValue>::Get(const TKey& rKey,
                                   const TValue& rDefault) const {
    HashBucket* pBucket = Search(rKey);

    if (pBucket == nullptr) {
        return rDefault;
    }

    return (*pBucket->item).value;
}

/**
 * @brief Gets list of keys in the map
 */
template <typename TKey, typename TValue>
K_INLINE TVector<TKey> THashMap<TKey, TValue>::Keys() const {
    TVector<TKey> keys;

    K_FOREACH (it, *this) {
        keys.PushBack((*it).key);
    }

    return keys;
}

/**
 * @brief Gets list of values in the map
 */
template <typename TKey, typename TValue>
K_INLINE TVector<TValue> THashMap<TKey, TValue>::Values() const {
    TVector<TValue> values;

    K_FOREACH (it, *this) {
        values.PushBack((*it).value);
    }

    return values;
}

/**
 * @brief Searches for an existing element by key
 *
 * @param rKey Key
 * @returns Bucket that contains the element
 */
template <typename TKey, typename TValue>
K_INLINE typename THashMap<TKey, TValue>::HashBucket*
THashMap<TKey, TValue>::Search(const TKey& rKey) const {
    // Hash function calculates the bucket index
    u32 idx = Hash(rKey) % mCapacity;
    HashBucket* pBucket = &mpBuckets[idx];

    // Check separate chained buckets to allow hash collisions
    for (; pBucket != nullptr; pBucket = pBucket->pNext) {
        if (!pBucket->item.HasValue()) {
            continue;
        }

        if ((*pBucket->item).key == rKey) {
            return pBucket;
        }
    }

    return nullptr;
}

/**
 * @brief Inserts a key if it does not already exist
 *
 * @param rKey Key
 * @return Bucket that contains the key
 */
template <typename TKey, typename TValue>
K_INLINE typename THashMap<TKey, TValue>::HashBucket&
THashMap<TKey, TValue>::Create(const TKey& rKey) {
    // Hash function calculates the bucket index
    u32 idx = Hash(rKey) % mCapacity;
    HashBucket* pBucket = &mpBuckets[idx];

    // The key may already exist
    for (HashBucket* pIt = pBucket; pIt != nullptr; pIt = pIt->pNext) {
        if (!pIt->item.HasValue()) {
            continue;
        }

        if ((*pIt->item).key == rKey) {
            return *pIt;
        }
    }

    // Re-use empty slots
    HashBucket* pPrev = nullptr;
    for (HashBucket* pIt = pBucket; pIt != nullptr; pIt = pIt->pNext) {
        pPrev = pIt;

        if (pIt->item.HasValue()) {
            continue;
        }

        pIt->Init(rKey);

        mSize++;
        return *pIt;
    }

    // Must create a new bucket
    HashBucket* pNewBucket = new HashBucket();
    K_ASSERT_PTR(pNewBucket);
    pNewBucket->Init(rKey);

    // Continue the chain
    K_ASSERT_PTR(pPrev);
    K_ASSERT(pPrev->item.HasValue());
    pPrev->pNext = pNewBucket;

    mSize++;
    return *pNewBucket;
}

} // namespace kiwi

#endif
