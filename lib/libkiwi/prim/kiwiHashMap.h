#ifndef LIBKIWI_PRIM_HASH_MAP_H
#define LIBKIWI_PRIM_HASH_MAP_H
#include <libkiwi/k_types.h>
#include <libkiwi/prim/kiwiList.h>
#include <libkiwi/prim/kiwiOptional.h>
#include <libkiwi/prim/kiwiVector.h>

namespace kiwi {
//! @addtogroup libkiwi_prim
//! @{

// Forward declarations
namespace detail {
template <typename TKey, typename TValue> struct THashBucket;
} // namespace detail

//! Hash value type
typedef u32 hash_t;
//! Largest representable hash
static const hash_t HASH_MAX = (1 << (sizeof(hash_t) * 8)) - 1;

/**
 * @brief Hashes data of a specified size
 * @details MurmurHash3 algorithm
 *
 * @param pKey Key
 * @param len Key length
 */
hash_t MurmurHash(const void* pKey, s32 len);

/**
 * @brief Hashes a key of any type
 * @note Specialize this for your custom types
 *
 * @param rKey Key
 */
template <typename TKey> K_INLINE hash_t Hash(const TKey& rKey) {
    return MurmurHash(&rKey, sizeof(TKey));
}

/**
 * @brief Hash map item
 *
 * @tparam TKey Item key type
 * @tparam TValue Item value type
 */
template <typename TKey, typename TValue> struct THashItem {
    //! Key storage
    TKey key;
    //! Value storage
    TValue value;

    /**
     * @brief Constructor
     *
     * @param rKey Item key
     */
    THashItem(const TKey& rKey) : key(rKey) {}

    /**
     * @brief Constructor
     *
     * @param rKey Item key
     * @param rValue Item value
     */
    THashItem(const TKey& rKey, const TValue& rValue)
        : key(rKey), value(rValue) {}
};

/**
 * @brief Key/value dictionary
 * @details Same concept as std::unordered_map
 *
 * @tparam TKey Key type
 * @tparam TValue Value type
 */
template <typename TKey, typename TValue> class THashMap {
public:
    // For readability
    typedef detail::THashBucket<const TKey, TValue> HashBucket;
    typedef typename HashBucket::Item HashItem;

    /**
     * @brief Hash map iterator
     */
    template <typename TItem>
    class IteratorImpl : public ForwardIterator<IteratorImpl<TItem>, TItem> {
        friend class THashMap<TKey, TValue>;

        // Allow promotion to const iterator
        friend class IteratorImpl<typename mp::add_const<TItem>::type>;

    public:
        /**
         * @brief Constructor
         *
         * @param pHashMap Parent hash map
         * @param index Bucket index
         */
        IteratorImpl(THashMap* pHashMap, u32 index);

        /**
         * @brief Constructor
         *
         * @param rOther Iterator
         */
        template <typename TOtherValue>
        IteratorImpl(const IteratorImpl<TOtherValue>& rOther)
            : mpHashMap(rOther.mpHashMap),
              mIndex(rOther.mIndex),
              mpBucket(rOther.mpBucket) {

            K_ASSERT_PTR(mpHashMap);
            K_ASSERT(mIndex <= mpHashMap->Capacity());
        }

        /**
         * @brief Increments the iterator once
         */
        void Next();

        /**
         * @brief Accesses the iterator's value
         */
        TItem& Get() {
            K_ASSERT_PTR(mpBucket);
            K_ASSERT_EX(mpBucket->item.HasValue(), "Invalid iterator");

            return *mpBucket->item;
        }

        /**
         * @brief Tests two iterators for equality
         *
         * @param other Other iterator
         */
        template <typename TOtherValue>
        bool Equals(IteratorImpl<TOtherValue> other) const {
            return mpBucket == other.mpBucket;
        }

    private:
        //! Parent hash map
        THashMap* mpHashMap;
        //! Hash map position
        u32 mIndex;

        //! Current bucket object
        HashBucket* mpBucket;
    };

    // Autogen typedefs and const/reverse getters
    K_GEN_ITERATOR_TYPEDEFS(IteratorImpl, HashItem);
    K_GEN_ITERATOR_METHODS(THashMap);

public:
    /**
     * @brief Constructor
     */
    THashMap() : mSize(0), mCapacity(scDefaultCapacity), mpBuckets(nullptr) {
        K_ASSERT(mCapacity > 0);
        K_ASSERT(mCapacity < HASH_MAX);

        mpBuckets = new HashBucket[mCapacity];
        K_ASSERT_PTR(mpBuckets);
    }

    /**
     * @brief Constructor
     * @details Copy constructor
     *
     * @param rOther Map to copy
     */
    THashMap(const THashMap& rOther)
        : mSize(0), mCapacity(0), mpBuckets(nullptr) {

        *this = rOther;
    }

    /**
     * @brief Destructor
     */
    ~THashMap() {
        delete[] mpBuckets;
        mpBuckets = nullptr;
    }

    /**
     * @brief Assignment operator
     * @details Copy assignment
     *
     * @param rOther Map to copy from
     */
    THashMap& operator=(const THashMap& rOther);

    /**
     * @brief Erases all elements from the map
     */
    void Clear();

    /**
     * @brief Gets an iterator to the beginning of the map
     */
    Iterator Begin() {
        return Iterator(this, 0);
    }

    /**
     * @brief Gets an iterator to the end of the map
     */
    Iterator End() {
        return Iterator(this, mCapacity);
    }

    /**
     * @brief Get number of elements in the map
     */
    u32 Size() const {
        return mSize;
    }

    /**
     * @brief Gets the maximum number of elements in the map
     */
    u32 Capacity() const {
        return mCapacity;
    }

    /**
     * @brief Check whether the map contains no elements
     */
    bool Empty() const {
        return Size() == 0;
    }

    /**
     * @brief Inserts a new element or updates an existing element
     *
     * @param rKey Key
     * @param rValue Value
     */
    void Insert(const TKey& rKey, const TValue& rValue) {
        (*Create(rKey).item).value = rValue;
    }

    /**
     * @brief Removes an element by key
     *
     * @param rKey Key
     * @param[out] pRemoved Removed value
     * @return Success
     */
    bool Remove(const TKey& rKey, TValue* pRemoved = nullptr);

    /**
     * @brief Removes all elements from the map satisfying the condition
     *
     * @param pPredicate Function to test if the element should be removed
     * @return How many elements were removed
     */
    u32 RemoveIf(bool (*pPredicate)(const HashItem&));

    /**
     * @brief Erases the element at the specified iterator's position
     *
     * @param it Iterator at which to erase the element
     * @return Iterator to the next element after the erased element
     */
    Iterator Erase(Iterator it);

    /**
     * @brief Accesses an element by key
     * @note Inserts the key if it does not already exist
     *
     * @param rKey Key
     * @return Existing element, or new entry
     */
    TValue& operator[](const TKey& rKey) {
        return (*Create(rKey).item).value;
    }

    /**
     * @brief Searches for an existing element by key
     *
     * @param rKey Key
     * @return Value if it exists
     */
    TValue* Find(const TKey& rKey) const;

    /**
     * @brief Accesses an element by key
     * @details If the element doesn't exist, the provided default value is
     * returned.
     *
     * @param rKey Key
     * @param rDefault Default value
     * @return Existing element, or default value
     */
    TValue Get(const TKey& rKey, const TValue& rDefault = TValue()) const;

    /**
     * @brief Tests whether an element exists with the specified key
     *
     * @param rKey Key
     */
    bool Contains(const TKey& rKey) const {
        return Search(rKey) != nullptr;
    }

    /**
     * @brief Gets a list of all keys in the map
     */
    TVector<TKey> Keys() const;
    /**
     * @brief Gets a list of all values in the map
     */
    TVector<TValue> Values() const;

private:
    //! Default bucket count
    static const u32 scDefaultCapacity = 32;

private:
    /**
     * @brief Searches for an existing element by key
     *
     * @param rKey Key
     * @returns Bucket that contains the element
     */
    HashBucket* Search(const TKey& rKey) const;

    /**
     * @brief Inserts a key if it does not already exist
     *
     * @param rKey Key
     * @return Bucket that contains the key
     */
    HashBucket& Create(const TKey& rKey);

private:
    //! Number of elements in the map
    u32 mSize;
    //! Maximum number of elements
    u32 mCapacity;

    //! Element buckets
    HashBucket* mpBuckets;
};

namespace detail {
//! @addtogroup libkiwi_prim
//! @{

/**
 * @brief Hash map bucket
 */
template <typename TKey, typename TValue> struct THashBucket {
    // Stored item type
    typedef THashItem<TKey, TValue> Item;

    //! Key/value storage
    Optional<Item> item;
    //! Separate chaining list
    THashBucket* pNext;

    /**
     * @brief Constructor
     */
    THashBucket() : pNext(nullptr) {}
    /**
     * @brief Destructor
     */
    ~THashBucket() {
        Destroy();
    }

    /**
     * @brief Initializes this bucket with a new key
     *
     * @param rKey Key
     */
    void Init(const TKey& rKey) {
        item.Reset();
        item = Item(rKey);
    }
    /**
     * @brief Clears this bucket's data
     */
    void Destroy() {
        item.Reset();
        delete pNext;
        pNext = nullptr;
    }
};

//! @}
} // namespace detail

//! @}
} // namespace kiwi

// Implementation header
#ifndef LIBKIWI_PRIM_HASH_MAP_IMPL_HPP
#include <libkiwi/prim/kiwiHashMapImpl.hpp>
#endif

#endif
