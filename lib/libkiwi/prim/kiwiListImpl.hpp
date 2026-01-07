// Implementation header
#ifndef LIBKIWI_PRIM_LIST_IMPL_HPP
#define LIBKIWI_PRIM_LIST_IMPL_HPP

// Declaration header
#ifndef LIBKIWI_PRIM_LIST_H
#include <libkiwi/prim/kiwiList.h>
#endif

namespace kiwi {

/**
 * @brief Assignment operator
 * @details Copy assignment
 *
 * @param rOther List to copy from
 */
template <typename T>
K_INLINE TList<T>& TList<T>::operator=(const TList& rOther) {
    // Release old data
    Clear();
    Init();

    K_FOREACH (it, rOther) {
        PushBack(*it);
    }

    return *this;
}

/**
 * @brief Erases the first element from the list
 *
 * @return The element that was just erased
 */
template <typename T> K_INLINE T TList<T>::PopFront() {
    K_ASSERT(!Empty());

    Iterator front = Begin();
    T element = *front;

    Erase(front);
    return element;
}

/**
 * @brief Erases the last element from the list
 *
 * @returns The element that was just erased
 */
template <typename T> K_INLINE T TList<T>::PopBack() {
    K_ASSERT(!Empty());

    Iterator back = --End();
    T element = *back;

    Erase(back);
    return element;
}

/**
 * @brief Removes first occurrence of element from list
 *
 * @param rElement Element to remove
 * @return Whether the element was found and removed
 */
template <typename T> K_INLINE bool TList<T>::Remove(const T& rElement) {
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
K_INLINE u32 TList<T>::RemoveIf(bool (*pPredicate)(const T&)) {
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
 * @brief Erases range of nodes
 *
 * @param begin Beginning of range (inclusive)
 * @param end End of range (exclusive)
 * @return Iterator to end of range
 */
template <typename T>
K_INLINE typename TList<T>::Iterator TList<T>::Erase(Iterator begin,
                                                     Iterator end) {
    TListNode<T>* pCurr = begin.mpNode;
    TListNode<T>* pEnd = end.mpNode;

    while (pCurr != pEnd) {
        // Preserve next node before erasing pointers
        TListNode<T>* pNext = pCurr->mpNext;

        EraseNode(pCurr);
        pCurr = pNext;
    }

    return end;
}

/**
 * @brief Inserts node at iterator
 *
 * @param iter Iterator at which to insert node
 * @param pNode Node to insert
 * @return Iterator to new node
 */
template <typename T>
K_INLINE typename TList<T>::Iterator TList<T>::InsertNode(Iterator iter,
                                                          TListNode<T>* pNode) {
    K_ASSERT_PTR(pNode);

    TListNode<T>* pNext = iter.mpNode;
    TListNode<T>* pPrev = pNext->mpPrev;

    // pPrev <- pNode -> pNext
    pNode->mpNext = pNext;
    pNode->mpPrev = pPrev;
    // pPrev <-> pNode <-> pNext
    pNext->mpPrev = pNode;
    pPrev->mpNext = pNode;

    mSize++;

    return Iterator(pNode);
}

/**
 * @brief Erases node from list
 *
 * @param pNode Node to erase
 * @return Iterator to next node
 */
template <typename T>
K_INLINE typename TList<T>::Iterator TList<T>::EraseNode(TListNode<T>* pNode) {
    K_ASSERT_PTR(pNode);

    TListNode<T>* pNext = pNode->mpNext;
    TListNode<T>* pPrev = pNode->mpPrev;

    // Remove connections to node
    pNext->mpPrev = pPrev;
    pPrev->mpNext = pNext;
    // Isolate node
    pNode->mpNext = nullptr;
    pNode->mpPrev = nullptr;
    // Free memory
    delete pNode;

    mSize--;

    return Iterator(pNext);
}

} // namespace kiwi

#endif
