#ifndef LIBKIWI_UTIL_DYNAMIC_SINGLETON_H
#define LIBKIWI_UTIL_DYNAMIC_SINGLETON_H
#include <libkiwi/k_types.h>
#include <libkiwi/prim/kiwiMutex.h>
#include <libkiwi/util/kiwiNonCopyable.h>

#include <revolution/OS.h>

#define K_DYNAMIC_SINGLETON_IMPL(T)                                            \
    T* kiwi::DynamicSingleton<T>::sInstance = nullptr;                         \
    kiwi::Mutex kiwi::DynamicSingleton<T>::sMutex;

namespace kiwi {
//! @addtogroup libkiwi_util
//! @{

/**
 * @brief Thread safe, dynamically allocated singleton
 */
template <typename T> class DynamicSingleton : private NonCopyable {
public:
    /**
     * @brief Gets a reference to the singleton object
     */
    static T& GetInstance() {
        AutoMutexLock lock(sMutex);
        K_ASSERT_PTR(sInstance);
        return *sInstance;
    }

    /**
     * @brief Initializes the singleton object
     */
    static T* CreateInstance() {
        AutoMutexLock lock(sMutex);
        K_ASSERT_EX(sInstance == nullptr, "Created singleton twice");

        if (sInstance == nullptr) {
            sInstance = new T();
            K_ASSERT_PTR(sInstance);
        }

        return sInstance;
    }

    /**
     * @brief Destroys the singleton object
     */
    static void DestroyInstance() {
        AutoMutexLock lock(sMutex);
        delete sInstance;
        sInstance = nullptr;
    }

    /**
     * @brief Tests whether the instance has been created
     */
    static bool IsCreateInstance() {
        AutoMutexLock lock(sMutex);
        return sInstance != nullptr;
    }

private:
    static T* sInstance; //! Static instance
    static Mutex sMutex; //! Mutex lock for safe access
};

//! @}
} // namespace kiwi

#endif
