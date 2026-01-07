#ifndef LIBKIWI_PRIM_LIST_H
#define LIBKIWI_PRIM_LIST_H
#include <libkiwi/debug/kiwiAssert.h>
#include <libkiwi/k_types.h>
#include <libkiwi/prim/kiwiAlgorithm.h>
#include <libkiwi/prim/kiwiIterator.h>
#include <libkiwi/prim/kiwiMeta.h>
#include <libkiwi/prim/kiwiOptional.h>
#include <libkiwi/util/kiwiNonCopyable.h>

#include <algorithm>

namespace kiwi {
//! @addtogroup libkiwi_prim
//! @{

// Forward declarations
template <typename T> class TListNode;

/**
 * @brief Templated linked-list
 * @details Same concept as std::list
 */
template <typename T> class TList {
public:
    /**
     * @brief Linked-list iterator
     */
    template <typename TValue>
    class IteratorImpl
        : public BiDirectionalIterator<IteratorImpl<TValue>, TValue> {
        friend class TList<T>;

    public:
        // Constness of TValue is moved to the TListNode
        typedef typename mp::move_const<                       //
            TValue,                                            //
            TListNode<typename mp::remove_const<TValue>::type> //
            >::type NodeType;

        // Allow promotion to const iterator
        friend class IteratorImpl<typename mp::add_const<TValue>::type>;

    public:
        /**
         * @brief Constructor
         *
         * @param pNode Iterator node
         */
        explicit IteratorImpl(NodeType* pNode) : mpNode(pNode) {
            K_ASSERT_PTR(mpNode);
        }
        /**
         * @brief Constructor
         *
         * @param rOther Iterator
         */
        template <typename TOtherValue>
        IteratorImpl(const IteratorImpl<TOtherValue>& rOther)
            : mpNode(rOther.mpNode) {

            K_ASSERT_PTR(mpNode);
        }

        /**
         * @brief Increments the iterator once
         */
        void Next() {
            K_ASSERT_PTR(mpNode);
            mpNode = mpNode->mpNext;
        }
        /**
         * @brief Decrements the iterator once
         */
        void Prev() {
            K_ASSERT_PTR(mpNode);
            mpNode = mpNode->mpPrev;
        }

        /**
         * @brief Accesses the iterator's value
         */
        TValue& Get() {
            K_ASSERT_PTR(mpNode);
            K_ASSERT_EX(mpNode->mElement.HasValue(), "Invalid iterator");
            return *mpNode->mElement;
        }

        /**
         * @brief Tests two iterators for equality
         *
         * @param other Other iterator
         */
        template <typename TOtherValue>
        bool Equals(IteratorImpl<TOtherValue> other) const {
            return mpNode == other.mpNode;
        }

    private:
        //! Underlying list node
        NodeType* mpNode;
    };

    // Autogen typedefs and const/reverse getters
    K_GEN_ITERATOR_TYPEDEFS(IteratorImpl, T);
    K_GEN_ITERATOR_METHODS(TList);

public:
    /**
     * @brief Constructor
     */
    TList() {
        Init();
    }

    /**
     * @brief Constructor
     * @details Copy constructor
     *
     * @param rOther List to copy
     */
    TList(const TList& rOther) {
        Init();
        *this = rOther;
    }

    /**
     * @brief Destructor
     */
    ~TList() {
        Clear();
    }

    /**
     * @brief Assignment operator
     * @details Copy assignment
     *
     * @param rOther List to copy from
     */
    TList& operator=(const TList& rOther);

    /**
     * @brief Erases all elements from the list
     */
    void Clear() {
        Erase(Begin(), End());
    }

    /**
     * @brief Gets an iterator to the beginning of the list
     */
    Iterator Begin() {
        return Iterator(mEndNode.mpNext);
    }
    /**
     * @brief Gets an iterator to the end of the list
     */
    Iterator End() {
        return Iterator(&mEndNode);
    }

    /**
     * @brief Gets the number of elements in the list
     */
    u32 Size() const {
        return mSize;
    }
    /**
     * @brief Tests whether the list is empty
     */
    bool Empty() const {
        return Size() == 0;
    }

    /**
     * @brief Erases the first element from the list
     *
     * @return The element that was just erased
     */
    T PopFront();
    /**
     * @brief Erases the last element from the list
     *
     * @returns The element that was just erased
     */
    T PopBack();

    /**
     * @brief Prepends an element to the front of the list
     *
     * @param rElement New element
     */
    void PushFront(const T& rElement) {
        Insert(Begin(), rElement);
    }
    /**
     * @brief Appends an element to the end of the list
     *
     * @param rElement New element
     */
    void PushBack(const T& rElement) {
        Insert(End(), rElement);
    }

    /**
     * @brief Gets a reference to the first element of the list
     */
    T& Front() {
        K_ASSERT(!Empty());
        return *Begin();
    }
    /**
     * @brief Gets reference to the first element of the list (const-view)
     */
    const T& Front() const {
        K_ASSERT(!Empty());
        return *Begin();
    }

    /**
     * @brief Gets reference to the last element of the list
     */
    T& Back() {
        K_ASSERT(!Empty());
        return *--End();
    }
    /**
     * @brief Gets reference to the last element of the list (const-view)
     */
    const T& Back() const {
        K_ASSERT(!Empty());
        return *--End();
    }

    /**
     * @brief Removes the first occurrence of an element from the list
     *
     * @param rElement Element to remove
     * @return Whether the element was found and removed
     */
    bool Remove(const T& rElement);

    /**
     * @brief Removes all elements from the list satisfying the condition
     *
     * @param pPredicate Function to test if the element should be removed
     * @return How many elements were removed
     */
    u32 RemoveIf(bool (*pPredicate)(const T&));

    /**
     * @brief Inserts an element at the specified iterator's position
     * @details Value is inserted before the given iterator
     *
     * @param it Iterator at which to insert the element
     * @param rElement Element to insert
     * @return Iterator to the new element
     */
    Iterator Insert(Iterator it, const T& rElement) {
        return InsertNode(it, new TListNode<T>(rElement));
    }

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
     * @brief Sorts elements in the list using the specified comparator function
     * @details The sort order defaults to ascending order when a comparator is
     * not specified.
     *
     * @param pComparator Function used to compare two elements. Returns true
     * when the first element is less-than the second element.
     */
    void Sort(bool (*pComparator)(const T&, const T&) = kiwi::Less) {
        kiwi::Sort(Begin(), End(), pComparator);
    }

private:
    /**
     * @brief Inserts node at iterator
     *
     * @param it Iterator at which to insert node
     * @param pNode Node to insert
     * @return Iterator to new node
     */
    Iterator InsertNode(Iterator it, TListNode<T>* pNode);

    /**
     * @brief Erases node from list
     *
     * @param pNode Node to erase
     * @return Iterator to next node
     */
    Iterator EraseNode(TListNode<T>* pNode);

    /**
     * @brief Initializes the list's size/end node
     */
    void Init() {
        mSize = 0;
        mEndNode.mpNext = &mEndNode;
        mEndNode.mpPrev = &mEndNode;
    }

private:
    //! Number of elements in the list
    u32 mSize;
    //! List end node
    TListNode<T> mEndNode;
};

/**
 * @brief Templated linked-list node
 */
template <typename T> class TListNode : private NonCopyable {
    friend class TList<T>;
    friend class TList<T>::Iterator;
    friend class TList<T>::ConstIterator;

private:
    /**
     * @brief Constructor
     */
    TListNode() : mpNext(nullptr), mpPrev(nullptr) {}

    /**
     * @brief Constructor
     *
     * @param element Node element
     */
    explicit TListNode(const T& rElement)
        : mpNext(nullptr), mpPrev(nullptr), mElement(rElement) {}

private:
    //! Next node in the linked-list
    TListNode<T>* mpNext;
    //! Previous node in the linked-list
    TListNode<T>* mpPrev;

    //! Underlying element
    Optional<T> mElement;
};

//! @}
} // namespace kiwi

// Implementation header
#ifndef LIBKIWI_PRIM_LIST_IMPL_HPP
#include <libkiwi/prim/kiwiListImpl.hpp>
#endif

#endif
