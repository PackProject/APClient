// Implementation header
#ifndef LIBKIWI_CORE_STD_THREAD_IMPL_HPP
#define LIBKIWI_CORE_STD_THREAD_IMPL_HPP

// Declaration header
#ifndef LIBKIWI_CORE_STD_THREAD_H
#include <libkiwi/core/kiwiStdThread.h>
#endif

#include <libkiwi/prim/kiwiBitCast.h>

namespace kiwi {
//! @addtogroup libkiwi_core
//! @{

/**
 * @name Non-member function
 */
/**@{*/
/**
 * @brief Constructor
 *
 * @param pFunc Static, no-parameter function
 */
template <typename TRet> StdThread::StdThread(TRet (*pFunc)()) {
    K_ASSERT_PTR(pFunc);

    SetFunction(pFunc);
    Start();
}

/**
 * @brief Constructor
 *
 * @param pFunc Static, single-parameter function
 * @param pArg Function argument
 */
template <typename TRet>
StdThread::StdThread(TRet (*pFunc)(StdThread::Param), StdThread::Param pArg) {
    K_ASSERT_PTR(pFunc);

    SetFunction(pFunc);
    SetGPR(3, BitCast<u32>(pArg));
    Start();
}
/**@}*/

/**
 * @name Member function (non-const)
 */
/**@{*/
/**
 * @brief Constructor
 *
 * @param pFunc No-parameter member function
 * @param rObj Class instance
 */
template <typename TRet, typename TClass>
StdThread::StdThread(TRet (TClass::*pFunc)(), TClass& rObj) {
    K_ASSERT(pFunc);

    SetMemberFunction(pFunc, rObj);
    Start();
}

/**
 * @brief Constructor
 *
 * @param pFunc Single-parameter member function
 * @param rObj Class instance
 * @param pArg Function argument
 */
template <typename TRet, typename TClass>
StdThread::StdThread(TRet (TClass::*pFunc)(StdThread::Param), TClass& rObj,
                     StdThread::Param pArg) {
    K_ASSERT(pFunc);

    SetMemberFunction(pFunc, rObj);
    SetGPR(4, BitCast<u32>(pArg));
    Start();
}
/**@}*/

/**
 * @name Member function (const)
 */
/**@{*/
/**
 * @brief Constructor
 *
 * @param pFunc No-parameter, const member function
 * @param rObj Class instance
 */
template <typename TRet, typename TClass>
StdThread::StdThread(TRet (TClass::*pFunc)() const, const TClass& rObj) {
    K_ASSERT(pFunc);

    SetMemberFunction(pFunc, rObj);
    Start();
}

/**
 * @brief Constructor
 *
 * @param pFunc Single-parameter, const member function
 * @param rObj Class instance
 * @param pArg Function argument
 */
template <typename TRet, typename TClass>
StdThread::StdThread(TRet (TClass::*pFunc)(StdThread::Param) const,
                     const TClass& rObj, StdThread::Param pArg) {
    K_ASSERT(pFunc);

    SetMemberFunction(pFunc, rObj);
    SetGPR(4, BitCast<u32>(pArg));
    Start();
}

namespace detail {
//! @addtogroup libkiwi_core
//! @{

/**
 * @brief Pointer-to-member-function (PTMF)
 */
struct MemberFunction {
    s32 toff; //!< 'This' pointer offset for target object type
    s32 voff; //!< Vtable offset into class
    union {
        s32 foff;    //!< Function offset into vtable
        void* pAddr; //!< Raw function address (if voff is -1)
    };
};

/**
 * @brief Sets a member function to run on this thread
 *
 * @param pFunc Function
 * @param rObj Class instance
 */
template <typename TFunc, typename TClass>
K_DONT_INLINE void StdThreadImpl::SetMemberFunction(TFunc pFunc,
                                                    const TClass& rObj) {

    K_STATIC_ASSERT_EX(sizeof(TFunc) == sizeof(MemberFunction),
                       "Not a member function");

    register const MemberFunction* pPtmf;
    register u32 self;

    // clang-format off
    asm volatile {
        mr pPtmf, r4 // pFunc -> pPtmf
        mr self, r5 //  rObj  -> self
    }
    K_ASSERT_PTR(pPtmf);
    K_ASSERT(self != 0);
    // clang-format on

    K_ASSERT_PTR(mpOSThread);
    K_ASSERT(mpOSThread->state == OS_THREAD_STATE_READY);

    // Adjust this pointer
    self += pPtmf->toff;
    SetGPR(3, self);

    // Non-virtual function?
    if (pPtmf->voff == -1) {
        SetFunction(pPtmf->pAddr);
        return;
    }

    // Find virtual function table
    const void** pVtbl = BitCast<const void**>(self + pPtmf->voff);

    // Find virtual function address
    K_ASSERT(pPtmf->foff >= 0);
    SetFunction(pVtbl[pPtmf->foff / sizeof(void*)]);
}

//! @}
} // namespace detail

//! @}
} // namespace kiwi

#endif
