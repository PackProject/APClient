#ifndef LIBKIWI_PRIM_STACK_H
#define LIBKIWI_PRIM_STACK_H
#include <libkiwi/debug/kiwiAssert.h>
#include <libkiwi/k_types.h>
#include <libkiwi/prim/kiwiIterator.h>
#include <libkiwi/prim/kiwiList.h>

namespace kiwi {
//! @addtogroup libkiwi_prim
//! @{

/**
 * @brief Templated stack (LI-FO structure)
 */
template <typename T> class TStack {
public:
    // Stack iteration will be in the reverse order of the list
    typedef typename TList<T>::RevIterator Iterator;
    typedef typename TList<T>::ConstRevIterator ConstIterator;
    typedef typename TList<T>::Iterator RevIterator;
    typedef typename TList<T>::ConstIterator ConstRevIterator;

public:
    // Autogen const/reverse getters
    K_GEN_ITERATOR_METHODS(TStack);

public:
    /**
     * @brief Gets the number of elements in the stack
     */
    u32 Size() const {
        return mList.Size();
    }
    /**
     * @brief Tests whether the stack is empty
     */
    bool Empty() const {
        return mList.Empty();
    }

    /**
     * @brief Gets an iterator to the top of the stack
     */
    Iterator Begin() {
        return mList.REnd();
    }
    /**
     * @brief Gets an iterator to the bottom of the stack
     */
    Iterator End() {
        return mList.RBegin();
    }

    /**
     * @brief Pushes an element to the stack
     *
     * @param rElement New element
     */
    void Push(const T& rElement) {
        mList.PushBack(rElement);
    }
    /**
     * @brief Pops the element from the top of the stack
     *
     * @returns The element that was just erased
     */
    T Pop() {
        K_ASSERT(!Empty());
        return mList.PopBack();
    }

    /**
     * @brief Accesses the element at the top of the stack
     */
    T& Top() {
        K_ASSERT(!Empty());
        return mList.Back();
    }
    /**
     * @brief Accesses the element at the top of the stack (const-view)
     */
    const T& Top() const {
        K_ASSERT(!Empty());
        return mList.Back();
    }

private:
    //! Internal list
    TList<T> mList;
};

//! @}
} // namespace kiwi

#endif
