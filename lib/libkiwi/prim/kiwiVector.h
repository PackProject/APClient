#ifndef LIBKIWI_PRIM_VECTOR_H
#define LIBKIWI_PRIM_VECTOR_H
#include <libkiwi/debug/kiwiAssert.h>
#include <libkiwi/k_types.h>

#include <algorithm>

namespace kiwi {
//! @addtogroup libkiwi_prim
//! @{

/**
 * @brief Dynamically-sized array with contiguous elements
 * @details Same concept as std::vector
 */
template <typename T> class TVector {
public:
    /**
     * @brief Vector iterator
     */
    template <typename TValue>
    class IteratorImpl
        : public RandomAccessIterator<IteratorImpl<TValue>, TValue> {
        friend class TVector<T>;

        // Allow promotion to const iterator
        friend class IteratorImpl<typename mp::add_const<TValue>::type>;

    public:
        /**
         * @brief Constructor
         *
         * @param pVector Parent vector
         * @param index Vector position
         */
        IteratorImpl(TVector* pVector, u32 index)
            : mpVector(pVector), mIndex(index) {

            K_ASSERT_PTR(mpVector);
            K_ASSERT(mIndex <= mpVector->Size());
        }
        /**
         * @brief Constructor
         *
         * @param rOther Iterator
         */
        template <typename TOtherValue>
        IteratorImpl(const IteratorImpl<TOtherValue>& rOther)
            : mpVector(rOther.mpVector), mIndex(rOther.mIndex) {

            K_ASSERT_PTR(mpVector);
            K_ASSERT(mIndex <= mpVector->Size());
        }

        /**
         * @brief Increments the iterator once
         */
        void Next() {
            mIndex++;
        }
        /**
         * @brief Decrements the iterator once
         */
        void Prev() {
            mIndex--;
        }

        /**
         * @brief Advances the iterator by a specified amount
         *
         * @param n Amount to move
         */
        void Move(int n) {
            mIndex += n;
        }

        /**
         * @brief Computes the distance between iterators
         *
         * @param other Other iterator
         */
        template <typename TOtherValue>
        int Dist(IteratorImpl<TOtherValue> other) const {
            K_ASSERT(mpVector == other.mpVector);
            return other.mIndex - mIndex;
        }

        /**
         * @brief Accesses the iterator's value
         */
        TValue& Get() {
            K_ASSERT_PTR(mpVector);
            K_ASSERT_EX(mIndex < mpVector->Size(),
                        "Invalid iterator (index: %d)", mIndex);

            return mpVector->At(mIndex);
        }

        /**
         * @brief Tests two iterators for equality
         *
         * @param other Other iterator
         */
        template <typename TOtherValue>
        bool Equals(IteratorImpl<TOtherValue> other) const {
            return mpVector == other.mpVector && mIndex == other.mIndex;
        }

    private:
        //! Parent vector
        TVector* mpVector;
        //! Vector position
        int mIndex;
    };

    // Autogen typedefs and const/reverse getters
    K_GEN_ITERATOR_TYPEDEFS(IteratorImpl, T);
    K_GEN_ITERATOR_METHODS(TVector);

public:
    /**
     * @brief Constructor
     */
    TVector() : mpData(nullptr), mCapacity(0), mSize(0) {}

    /**
     * @brief Constructor
     *
     * @param capacity Buffer capacity
     */
    explicit TVector(u32 capacity) : mpData(nullptr), mCapacity(0), mSize(0) {
        Reserve(capacity);
    }

    /**
     * @brief Constructor
     * @details Copy constructor
     *
     * @param rOther Vector to copy
     */
    TVector(const TVector& rOther) : mpData(nullptr), mCapacity(0), mSize(0) {
        *this = rOther;
    }

    /**
     * @brief Destructor
     */
    ~TVector();

    /**
     * @brief Vector copy assignment
     *
     * @param rOther Vector to copy
     */
    TVector& operator=(const TVector& rOther);

    /**
     * @brief Erases all elements from the vector
     */
    void Clear() {
        Erase(Begin(), End());
    }
    /**
     * @brief Reserves space for elements in the vector
     *
     * @param capacity New capacity
     */
    void Reserve(u32 capacity);

    /**
     * @brief Gets an iterator to beginning of the vector
     */
    Iterator Begin() {
        return Iterator(this, 0);
    }
    /**
     * @brief Gets an iterator to the end of the vector
     */
    Iterator End() {
        return Iterator(this, Size());
    }

    /**
     * @brief Gets the number of elements in the vector
     */
    u32 Size() const {
        return mSize;
    }
    /**
     * @brief Tests whether the vector is empty
     */
    bool Empty() const {
        return Size() == 0;
    }

    /**
     * @brief Erases the last element from the vector
     *
     * @returns The element that was just erased
     */
    T PopBack();
    /**
     * @brief Appends an element to the end of the vector
     *
     * @param rElement New element
     */
    void PushBack(const T& rElement) {
        Insert(End(), rElement);
    }

    /**
     * @brief Gets a reference to the first element of the vector
     */
    T& Front() {
        K_ASSERT_PTR(mpData);
        K_ASSERT(!Empty());
        return Data()[0];
    }
    /**
     * @brief Gets a reference to the first element of the vector (const-view)
     */
    const T& Front() const {
        K_ASSERT_PTR(mpData);
        K_ASSERT(!Empty());
        return Data()[0];
    }

    /**
     * @brief Gets a reference to the last element of the vector
     */
    T& Back() {
        K_ASSERT_PTR(mpData);
        K_ASSERT(!Empty());
        return Data()[Size() - 1];
    }
    /**
     * @brief Gets a reference to the last element of the vector (const-view)
     */
    const T& Back() const {
        K_ASSERT_PTR(mpData);
        K_ASSERT(!Empty());
        return Data()[Size() - 1];
    }

    /**
     * @brief Accesses an element by index
     *
     * @param i Element index
     */
    T& At(u32 i) {
        K_ASSERT(i < Size());
        return Data()[i];
    }
    /**
     * @brief Accesses an element by index (const-view)
     *
     * @param i Element index
     */
    const T& At(u32 i) const {
        K_ASSERT(i < Size());
        return Data()[i];
    }

    /**
     * @brief Accesses the underlying element data
     */
    T* Data() {
        return reinterpret_cast<T*>(mpData);
    }
    /**
     * @brief Accesses the underlying element data (const-view)
     */
    const T* Data() const {
        return reinterpret_cast<const T*>(mpData);
    }

    /**
     * @brief Removes the first occurrence of an element from the vector
     *
     * @param rElement Element to remove
     * @return Whether the element was found and removed
     */
    bool Remove(const T& rElement);

    /**
     * @brief Removes an element at the specified position
     *
     * @param pos Element position
     */
    void RemoveAt(u32 pos) {
        K_ASSERT(pos < Size());
        Erase(Begin() + pos);
    }

    /**
     * @brief Removes all elements from the list satisfying the condition
     *
     * @param pPredicate Function to test if the element should be removed
     * @return How many elements were removed
     */
    u32 RemoveIf(bool (*pPredicate)(const T&));

    /**
     * @brief Inserts a new element at the specified position
     * @details Value is inserted before the given iterator
     *
     * @param it Iterator at which to insert the element
     * @param rElement Element to insert
     * @returns Iterator to the new element
     */
    Iterator Insert(Iterator it, const T& rElement);

    /**
     * @brief Erases the element at the specified iterator's position
     *
     * @param it Iterator at which to erase element
     * @return Iterator to the next element after the erased element
     */
    Iterator Erase(Iterator it) {
        Iterator copy(it);
        return Erase(it, ++copy);
    }

    /**
     * @brief Erases range of nodes
     *
     * @param begin Beginning of range (inclusive)
     * @param end End of range (exclusive)
     * @return Iterator to end of range
     */
    Iterator Erase(Iterator begin, Iterator end);

    /**
     * @brief Sorts elements in the vector using the specified comparator
     * function
     * @details The sort order defaults to ascending order when a comparator is
     * not specified.
     *
     * @param pComparator Function used to compare two elements. Returns true
     * when the first element is less-than the second element.
     */
    void Sort(bool (*pComparator)(const T&, const T&) = kiwi::Less) {
        kiwi::Sort(Begin(), End(), pComparator);
    }

    // clang-format off
    T&       operator[](u32 i)       { return At(i); }
    T&       operator()(u32 i)       { return At(i); }
    const T& operator[](u32 i) const { return At(i); }
    const T& operator()(u32 i) const { return At(i); }
    // clang-format on

private:
    //! Number of elements in the vector
    u32 mSize;
    //! Maximum number of elements
    u32 mCapacity;

    //! Element data buffer
    u8* mpData;
};

//! @}
} // namespace kiwi

// Implementation header
#ifndef LIBKIWI_PRIM_VECTOR_IMPL_HPP
#include <libkiwi/prim/kiwiVectorImpl.hpp>
#endif

#endif
