#ifndef LIBKIWI_PRIM_ARRAY_H
#define LIBKIWI_PRIM_ARRAY_H
#include <libkiwi/debug/kiwiAssert.h>
#include <libkiwi/k_types.h>
#include <libkiwi/prim/kiwiAlgorithm.h>
#include <libkiwi/prim/kiwiIterator.h>
#include <libkiwi/prim/kiwiMeta.h>

namespace kiwi {
//! @addtogroup libkiwi_prim
//! @{

namespace detail {
//! @addtogroup libkiwi_prim
//! @{

/**
 * @brief Common array implementation
 *
 * @tparam T Array value type
 * @tparam N Array size
 */
template <typename T, int N> class TArrayImpl {
public:
    /**
     * @brief Array iterator
     */
    template <typename TValue>
    class IteratorImpl
        : public RandomAccessIterator<IteratorImpl<TValue>, TValue> {

        // Allow promotion to const iterator
        friend class IteratorImpl<typename mp::add_const<TValue>::type>;

    public:
        /**
         * @brief Constructor
         *
         * @param pArray Parent array
         * @param index Array position
         */
        IteratorImpl(TArrayImpl* pArray, int index)
            : mpArray(pArray), mIndex(index) {

            K_ASSERT_PTR(mpArray);
            K_ASSERT(mIndex >= 0);
            K_ASSERT(mIndex <= mpArray->Size());
        }
        /**
         * @brief Constructor
         *
         * @param rOther Iterator
         */
        template <typename TOtherValue>
        IteratorImpl(const IteratorImpl<TOtherValue>& rOther)
            : mpArray(rOther.mpArray), mIndex(rOther.mIndex) {

            K_ASSERT_PTR(mpArray);
            K_ASSERT(mIndex >= 0);
            K_ASSERT(mIndex <= mpArray->Size());
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
            K_ASSERT(mpArray == other.mpArray);
            return other.mIndex - mIndex;
        }

        /**
         * @brief Accesses the iterator's value
         */
        TValue& Get() {
            K_ASSERT_PTR(mpArray);
            K_ASSERT_EX(mIndex >= 0 && mIndex < mpArray->Size(),
                        "Invalid iterator (index: %d)", mIndex);

            return mpArray->At(mIndex);
        }

        /**
         * @brief Tests two iterators for equality
         *
         * @param other Other iterator
         */
        template <typename TOtherValue>
        bool Equals(IteratorImpl<TOtherValue> other) const {
            return mpArray == other.mpArray && mIndex == other.mIndex;
        }

    private:
        //! Parent array
        TArrayImpl* mpArray;
        //! Array position
        int mIndex;
    };

    // Autogen typedefs and const/reverse getters
    K_GEN_ITERATOR_TYPEDEFS(IteratorImpl, T);
    K_GEN_ITERATOR_METHODS(TArrayImpl);

public:
    /**
     * @brief Gets an iterator to the beginning of the array
     */
    Iterator Begin() {
        return Iterator(this, 0);
    }
    /**
     * @brief Gets an iterator to the end of the array
     */
    Iterator End() {
        return Iterator(this, Size());
    }

    /**
     * @brief Accesses the array's size
     */
    int Size() const {
        return N;
    }

    /**
     * @brief Gets a reference to the first element of the array
     */
    T& Front() {
        return mData[0];
    }
    /**
     * @brief Gets a reference to the first element of the array (const-view)
     */
    const T& Front() const {
        return mData[0];
    }

    /**
     * @brief Gets a reference to the last element of the array
     */
    T& Back() {
        return mData[Size() - 1];
    }
    /**
     * @brief Gets a reference to the last element of the array (const-view)
     */
    const T& Back() const {
        return mData[Size() - 1];
    }

    /**
     * @brief Accesses an array element by index
     *
     * @param i Element index
     */
    T& At(int i) {
        K_ASSERT(i >= 0 && i < Size());
        return mData[i];
    }
    /**
     * @brief Accesses an array element by index (read-only)
     *
     * @param i Element index
     */
    const T& At(int i) const {
        K_ASSERT(i >= 0 && i < Size());
        return mData[i];
    }

    /**
     * @brief Accesses the underlying element data
     */
    T* Data() {
        return mData;
    }
    /**
     * @brief Accesses the underlying element data (const-view)
     */
    const T* Data() const {
        return mData;
    }

    // clang-format off
    T&       operator[](int i)       { return At(i); }
    T&       operator()(int i)       { return At(i); }
    const T& operator[](int i) const { return At(i); }
    const T& operator()(int i) const { return At(i); }
    // clang-format on

protected:
    //! Underlying array data
    T mData[N];
};

//! @}
} // namespace detail

/**
 * @brief 1D array of fixed size
 * @details Same concept as std::array
 *
 * @tparam T Array element type
 * @tparam N Array size
 */
template <typename T, int N> class TArray : public detail::TArrayImpl<T, N> {
public:
    typedef detail::TArrayImpl<T, N> BaseType;

    // Propogate iterator types up
    typedef typename BaseType::Iterator Iterator;
    typedef typename BaseType::ConstIterator ConstIterator;
    typedef typename BaseType::RevIterator RevIterator;
    typedef typename BaseType::ConstRevIterator ConstRevIterator;

public:
    /**
     * @brief Sorts elements in the list using the specified comparator function
     * @details The sort order defaults to ascending order when a comparator is
     * not specified.
     *
     * @param pComparator Function used to compare two elements. Returns true
     * when the first element is less-than the second element.
     */
    void Sort(bool (*pComparator)(const T&, const T&) = kiwi::Less) {
        kiwi::Sort(BaseType::Begin(), BaseType::End(), pComparator);
    }
};

/**
 * @brief 2D array of fixed size
 *
 * @tparam T Array element type
 * @tparam M Outer array size (number of rows)
 * @tparam N Inner array size (number of columns)
 */
template <typename T, int M, int N>
class TArray2D : public detail::TArrayImpl<TArray<T, N>, M> {
public:
    typedef detail::TArrayImpl<TArray<T, N>, M> BaseType;

    // Propogate iterator types up
    typedef typename BaseType::Iterator Iterator;
    typedef typename BaseType::ConstIterator ConstIterator;
    typedef typename BaseType::RevIterator RevIterator;
    typedef typename BaseType::ConstRevIterator ConstRevIterator;

public:
    /**
     * @brief Gets the inner arrays' size
     */
    int InnerSize() const {
        return N;
    }

    /**
     * @brief Accesses an array element by index
     *
     * @param i Element row
     * @param j Element column
     */
    T& At(int i, int j) {
        K_ASSERT(i >= 0 && i < BaseType::Size());
        K_ASSERT(j >= 0 && j < InnerSize());
        return BaseType::mData[i][j];
    }
    /**
     * @brief Accesses an array element by index (read-only)
     *
     * @param i Element row
     * @param j Element column
     */
    const T& At(int i, int j) const {
        K_ASSERT(i >= 0 && i < BaseType::Size());
        K_ASSERT(j >= 0 && j < InnerSize());
        return BaseType::mData[i][j];
    }

    // clang-format off
    T&       operator()(int i, int j)       { return At(i, j); }
    const T& operator()(int i, int j) const { return At(i, j); }
    // clang-format on
};

//! @}
} // namespace kiwi

#endif
