#include <libkiwi/prim/kiwiBitCast.h>

#include <libkiwi.h>

namespace kiwi {
namespace detail {

/**
 * @brief Constructor
 */
ThreadImpl::ThreadImpl() : mpOSThread(nullptr), mpThreadStack(nullptr) {
    // Thread & stack aligned to 32
    mpOSThread = new (32) OSThread();
    K_ASSERT_PTR(mpOSThread);
    mpThreadStack = new (32) u8[scStackSize];
    K_ASSERT_PTR(mpThreadStack);

    BOOL success =
        OSCreateThread(mpOSThread, nullptr, nullptr,
                       mpThreadStack + scStackSize, scStackSize, scPriority, 0);
    K_ASSERT(success);
}

/**
 * @brief Destructor
 */
ThreadImpl::~ThreadImpl() {
    K_ASSERT_PTR(mpOSThread);
    K_ASSERT_EX(*mpOSThread->stackEnd == OS_THREAD_STACK_MAGIC,
                "Thread stack overflow!!!");

    OSDetachThread(mpOSThread);

    delete mpOSThread;
    delete mpThreadStack;
}

/**
 * @brief Begins execution on this thread
 */
void ThreadImpl::Start() {
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
void ThreadImpl::Join() {
    K_ASSERT_PTR(mpOSThread);

    BOOL success = OSJoinThread(mpOSThread, nullptr);
    K_ASSERT(success);
}

/**
 * @brief Sets a function for this thread to run
 *
 * @param addr Function address (new SRR0 value)
 */
void ThreadImpl::SetFunction(const void* addr) {
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
void ThreadImpl::SetGPR(u32 idx, u32 value) {
    K_ASSERT_PTR(mpOSThread);
    K_ASSERT(idx >= 0 && idx < K_LENGTHOF(mpOSThread->context.gprs));
    mpOSThread->context.gprs[idx] = value;
}

} // namespace detail
} // namespace kiwi
