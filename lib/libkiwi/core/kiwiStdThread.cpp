#include <libkiwi.h>

namespace kiwi {
namespace detail {

/**
 * @brief Constructor
 */
StdThreadImpl::StdThreadImpl() : mpOSThread(nullptr), mpThreadStack(nullptr) {
    // Thread & stack aligned to 32
    mpOSThread = new (32) OSThread();
    K_ASSERT_PTR(mpOSThread);
    mpThreadStack = new (32) u8[scStackSize];
    K_ASSERT_PTR(mpThreadStack);

    BOOL success = OSCreateThread(mpOSThread, nullptr, nullptr,
                                  mpThreadStack + scStackSize, scStackSize,
                                  OS_PRIORITY_MAX - 1, 0);

    K_ASSERT(success);
}

/**
 * @brief Destructor
 */
StdThreadImpl::~StdThreadImpl() {
    K_ASSERT_PTR(mpOSThread);
    K_ASSERT_EX(*mpOSThread->stackEnd == OS_THREAD_STACK_MAGIC,
                "Thread stack overflow!!!");

    OSDetachThread(mpOSThread);

    delete mpOSThread;
    delete[] mpThreadStack;
}

/**
 * @brief Begins execution on this thread
 */
void StdThreadImpl::Start() {
    K_ASSERT_PTR(mpOSThread);
    K_ASSERT(mpOSThread->state == OS_THREAD_STATE_READY);
    K_ASSERT_EX(mpOSThread->context.srr0 != 0, "No function to call");

    // Resume thread to call function
    s32 suspend = OSResumeThread(mpOSThread);
    K_ASSERT(suspend == 1);
}

/**
 * @brief Waits for this thread to finish executing
 */
void StdThreadImpl::Join() {
    K_ASSERT_PTR(mpOSThread);

    BOOL success = OSJoinThread(mpOSThread, nullptr);
    K_ASSERT(success);
}

/**
 * @brief Sets a function for this thread to run
 *
 * @param addr Function address (new SRR0 value)
 */
void StdThreadImpl::SetFunction(const void* addr) {
    K_ASSERT_PTR(mpOSThread);
    K_ASSERT(addr != 0);
    mpOSThread->context.srr0 = BitCast<u32>(addr);
}

/**
 * @brief Sets a GPR's value in this thread
 *
 * @param i GPR number
 * @param value New value
 */
void StdThreadImpl::SetGPR(u32 idx, u32 value) {
    K_ASSERT_PTR(mpOSThread);
    K_ASSERT(idx >= 0 && idx < K_LENGTHOF(mpOSThread->context.gprs));
    mpOSThread->context.gprs[idx] = value;
}

/**
 * @brief Sets a member function to run on this thread (internal
 * implementation)
 */
void StdThreadImpl::SetMemberFunctionImpl(
    ... /* TFunc pFunc, const TClass& rObj */) {

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

} // namespace detail
} // namespace kiwi
