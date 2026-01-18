#include <libkiwi.h>

#include <revolution/OS.h>

namespace kiwi {

/**
 * @brief Constructor
 *
 * @param rName Thread name
 * @param priority Thread priority
 * @param stackSize Thread stack size
 */
Thread::Thread(const String& rName, s32 priority, u32 stackSize)
    : mName(rName), mpOSThread(nullptr), mpThreadStack(nullptr) {

    K_ASSERT(priority >= OS_PRIORITY_MIN && priority <= OS_PRIORITY_MAX);

    mpOSThread = new (32) OSThread();
    K_ASSERT_PTR(mpOSThread);

    // Need 32-byte align but can't round up past the stack end
    stackSize = RoundDown(stackSize, 32);

    mpThreadStack = new (32) u8[stackSize];
    K_ASSERT_PTR(mpThreadStack);

    BOOL success =
        OSCreateThread(mpOSThread, ThreadFunc, this, mpThreadStack + stackSize,
                       stackSize, priority, 0);

    K_ASSERT(success);

    // Allow access from inner OSThread
    mpOSThread->specific[0] = this;
}

/**
 * @brief Destructor
 */
Thread::~Thread() {
    K_ASSERT_PTR(mpOSThread);
    K_ASSERT_EX(*mpOSThread->stackEnd == OS_THREAD_STACK_MAGIC,
                "Thread stack overflow!!!");

    if (!OSIsThreadTerminated(mpOSThread)) {
        OSDetachThread(mpOSThread);
        OSCancelThread(mpOSThread);
    }

    delete mpOSThread;
    mpOSThread = nullptr;

    delete[] mpThreadStack;
    mpThreadStack = nullptr;
}

/**
 * @brief Resumes the thread
 */
void Thread::Resume() {
    K_ASSERT_PTR(mpOSThread);

    s32 suspend = OSResumeThread(mpOSThread);
    K_ASSERT(suspend == 1);
}

/**
 * @brief OS thread function
 *
 * @param pArg Thread function argument
 */
void* Thread::ThreadFunc(void* pArg) {
    K_ASSERT_PTR(pArg);

    // Thread function argument is this object
    Thread* p = static_cast<Thread*>(pArg);
    p->Run();

    return nullptr;
}

} // namespace kiwi