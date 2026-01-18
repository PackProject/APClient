#ifndef LIBKIWI_CORE_THREAD_H
#define LIBKIWI_CORE_THREAD_H
#include <libkiwi/debug/kiwiAssert.h>
#include <libkiwi/k_types.h>

#include <revolution/OS.h>

namespace kiwi {
//! @addtogroup libkiwi_core
//! @{

/**
 * @brief OS thread wrapper
 */
class Thread {
public:
    //! Default thread stack size
    static const u32 DEFAULT_STACK_SIZE = OS_MEM_KB_TO_B(16);
    //! Default thread priority
    static const s32 DEFAULT_PRIORITY = OS_PRIORITY_MAX - 1;

public:
    /**
     * @brief Constructor
     *
     * @param rName Thread name
     * @param priority Thread priority
     * @param stackSize Thread stack size
     */
    Thread(const String& rName, s32 priority = DEFAULT_PRIORITY,
           u32 stackSize = DEFAULT_STACK_SIZE);

    /**
     * @brief Destructor
     */
    virtual ~Thread();

    /**
     * @brief Thread function
     */
    virtual void Run() = 0;

    /**
     * @brief Resumes the thread
     */
    void Resume();

    /**
     * @brief Accesses the thread's name
     */
    const String& GetName() const {
        return mName;
    }
    /**
     * @brief Sets the thread's name
     *
     * @param rName Thread name
     */
    void SetName(const String& rName) {
        mName = rName;
    }

private:
    /**
     * @brief OS thread function
     *
     * @param pArg Thread function argument
     */
    static void* ThreadFunc(void* pArg);

private:
    //! Thread name
    String mName;

    //! Operating system thread
    OSThread* mpOSThread;
    //! Thread stack
    u8* mpThreadStack;
};

//! @}
} // namespace kiwi

#endif
