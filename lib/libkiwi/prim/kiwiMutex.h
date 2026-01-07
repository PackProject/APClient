#ifndef LIBKIWI_PRIM_MUTEX_H
#define LIBKIWI_PRIM_MUTEX_H
#include <libkiwi/debug/kiwiAssert.h>
#include <libkiwi/k_types.h>
#include <libkiwi/util/kiwiBitUtil.h>
#include <libkiwi/util/kiwiNonCopyable.h>
#include <libkiwi/util/kiwiRandom.h>

#include <revolution/OS.h>

namespace kiwi {
//! @addtogroup libkiwi_prim
//! @{

/**
 * @name Functions for lockable types
 */
/**@{*/
/**
 * @brief Initializes a mutex/lockable object
 * @details Default specialization does nothing.
 *
 * @tparam T Mutex/lockable type
 * @param rLockable Lockable object
 */
template <typename T> K_INLINE void InitMutex(T& rLockable) {}
/**
 * @brief Locks a mutex/lockable object
 * @details Default specialization expects a "Lock" method.
 *
 * @tparam T Mutex/lockable type
 * @param rLockable Lockable object
 */
template <typename T> K_INLINE void LockMutex(T& rLockable) {
    rLockable.Lock();
}
/**
 * @brief Unlocks a mutex/lockable object
 * @details Default specialization expects a "Lock" method.
 *
 * @tparam T Mutex/lockable type
 * @param rLockable Lockable object
 */
template <typename T> K_INLINE void UnlockMutex(T& rLockable) {
    rLockable.Unlock();
}
/**
 * @brief Unlocks a mutex/lockable object
 * @details Default specialization expects a "TryLock" method, returning its
 * success.
 *
 * @tparam T Mutex/lockable type
 * @param rLockable Lockable object
 */
template <typename T> K_INLINE bool TryLockMutex(T& rLockable) {
    return rLockable.TryLock();
}
/**
 * @brief Tests whether an OS mutex object is locked
 * @details Default specialization expects a "IsLocked" method, returning its
 * result.
 *
 * @param rMutex OS mutex
 */
template <typename T> K_INLINE bool CheckLockMutex(const T& rMutex) {
    return rMutex.IsLocked();
}
/**@}*/

/**
 * @name Function specializations for OS types
 */
/**@{*/
/**
 * @brief Initializes an OS mutex object
 *
 * @param rMutex OS mutex
 */
template <> K_INLINE void InitMutex(OSMutex& rMutex) {
    OSInitMutex(&rMutex);
}
/**
 * @brief Locks an OS mutex object
 *
 * @param rMutex OS mutex
 */
template <> K_INLINE void LockMutex<OSMutex>(OSMutex& rMutex) {
    if (OSGetCurrentThread() != nullptr) {
        OSLockMutex(&rMutex);
    }
}
/**
 * @brief Unlocks an OS mutex object
 *
 * @param rMutex OS mutex
 */
template <> K_INLINE void UnlockMutex<OSMutex>(OSMutex& rMutex) {
    if (OSGetCurrentThread() != nullptr) {
        OSUnlockMutex(&rMutex);
    }
}
/**
 * @brief Unlocks an OS mutex object
 *
 * @param rMutex OS mutex
 */
template <> K_INLINE bool TryLockMutex<OSMutex>(OSMutex& rMutex) {
    return OSTryLockMutex(&rMutex);
}
/**
 * @brief Tests whether an OS mutex object is locked
 *
 * @param rMutex OS mutex
 */
template <> K_INLINE bool CheckLockMutex<OSMutex>(const OSMutex& rMutex) {
    return rMutex.lock != 0;
}
/**@}*/

/**
 * @brief Mutex synchronization primitive
 *
 * @tparam T Lockable object type
 */
template <typename T> class TMutex : private NonCopyable {
public:
    /**
     * @brief Constructor
     */
    TMutex() {
        InitMutex(mMutexImpl);
    }
    /**
     * @brief Destructor
     */
    ~TMutex() {
        K_ASSERT(!CheckLockMutex(mMutexImpl));
    }

    /**
     * @brief Locks the mutex
     */
    void Lock() {
        LockMutex(mMutexImpl);
    }
    /**
     * @brief Unlocks the mutex
     */
    void Unlock() {
        UnlockMutex(mMutexImpl);
    }

    bool TryLock() {
        return TryLockMutex(mMutexImpl);
    }

private:
    //! Mutex implementation
    T mMutexImpl;
};

//! Shorthand for OS mutex
typedef TMutex<OSMutex> Mutex;

/**
 * @brief Scoped auto-lock
 *
 * @tparam T Mutex/lockable type
 */
template <typename T> class TAutoMutexLock : private NonCopyable {
public:
    /**
     * @brief Constructor
     *
     * @param rLockable Lockable object
     */
    TAutoMutexLock(T& rLockable) : mrLockable(rLockable) {
        LockMutex(mrLockable);
    }
    /**
     * @brief Destructor
     */
    ~TAutoMutexLock() {
        UnlockMutex(mrLockable);
    }

private:
    //! Lockable object
    T& mrLockable;
};

//! Shorthand for OS mutex auto-lock
typedef TAutoMutexLock<Mutex> AutoMutexLock;

/**
 * @brief Scoped auto-lock for OS hardware interrupts
 */
class AutoInterruptLock : private NonCopyable {
public:
    /**
     * @brief Constructor
     * @details The default setting disables interrupts.
     *
     * @param enable Initial interrupt status for the lock
     */
    AutoInterruptLock(bool enable = false)
        : mEnabled(enable ? OSEnableInterrupts() : OSDisableInterrupts()) {}

    /**
     * @brief Destructor
     */
    ~AutoInterruptLock() {
        OSRestoreInterrupts(mEnabled);
    }

private:
    //! Hardware interrupt status
    BOOL mEnabled;
};

//! @}
} // namespace kiwi

#endif
