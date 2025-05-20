#ifndef LIBKIWI_PRIM_STACK_H
#define LIBKIWI_PRIM_STACK_H
#include <libkiwi/debug/kiwiAssert.h>
#include <libkiwi/k_types.h>
#include <libkiwi/prim/kiwiLinkList.h>

namespace kiwi {
//! @addtogroup libkiwi_prim
//! @{

/**
 * @brief Templated stack
 */
template <typename T> class TStack : private TList<T> {
private:
    // TODO!!!!! BAD
    typedef TList<T> BaseType;
    typedef T* ElemType;
    typedef T& RefType;

public:
    /**
     * @brief Gets the number of elements in the stack
     */
    u32 Size() const {
        return TList<T>::Size();
    }
    /**
     * @brief Tests whether the stack is empty
     */
    bool Empty() const {
        return Size() == 0;
    }

    /**
     * @brief Pushes an element to the stack
     *
     * @param pElem New element
     */
    void Push(ElemType pElem) {
        K_ASSERT(pElem != nullptr);
        TList<T>::PushBack(pElem);
    }
    /**
     * @brief Pops an element from the stack
     * @details No element is returned to prevent undefined behavior.
     *
     * @param pElem New element
     */
    void Pop() {
        K_ASSERT(!Empty());
        TList<T>::PopBack();
    }

    /**
     * @brief Accesses the element at the top of the stack
     */
    RefType Top() {
        K_ASSERT(!Empty());
        return TList<T>::Back();
    }
    /**
     * @brief Accesses the element at the top of the stack (const-view)
     */
    const RefType Top() const {
        K_ASSERT(!Empty());
        return TList<T>::Back();
    }
};

//! @}
} // namespace kiwi

#endif
