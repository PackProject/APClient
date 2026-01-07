#ifndef LIBKIWI_UTIL_EXTENSION_H
#define LIBKIWI_UTIL_EXTENSION_H
#include <libkiwi/debug/kiwiAssert.h>
#include <libkiwi/k_types.h>
#include <libkiwi/util/kiwiNonConstructable.h>

namespace kiwi {
//! @addtogroup libkiwi_util
//! @{

/**
 * @brief Extend class using only pre-existing instances
 */
template <typename TBase>
class Extension : public TBase, private NonConstructable {};

/**
 * @brief Extend singleton class (pointer) using only pre-existing instances
 */
template <typename TBase, typename TDerived>
class ExtSingletonPtr : public TBase, private NonConstructable {
public:
    /**
     * @brief Accesses singleton instance (by pointer)
     */
    static TDerived& GetInstance() {
        K_ASSERT_PTR(TBase::instance());
        return static_cast<TDerived&>(*TBase::instance());
    }
};

/**
 * @brief Extend singleton class (reference) using only pre-existing instances
 */
template <typename TBase, typename TDerived>
class ExtSingletonRef : public TBase, private NonConstructable {
public:
    /**
     * @brief Accesses singleton instance (by reference)
     */
    static TDerived& GetInstance() {
        return static_cast<TDerived&>(TBase::instance());
    }
};

//! @}
} // namespace kiwi

/**
 * @brief Declares function(s) necessary to override singleton
 * creation/destruction.
 */
#define K_SINGLETON_REPLACE_DECL(TBASE, TDERIVED)                              \
public:                                                                        \
    static TBASE* Ex_CreateInstance();                                         \
    static void Ex_DestroyInstance();                                          \
                                                                               \
private:                                                                       \
    ;

/**
 * @brief Defines function(s) necessary to override singleton creation.
 * @note The new/derived type must inherit from StaticSingleton.
 */
#define K_SINGLETON_REPLACE_IMPL_STATIC(TBASE, TDERIVED)                       \
    TBASE* TDERIVED::Ex_CreateInstance() {                                     \
        return TBASE::spInstance =                                             \
                   &kiwi::StaticSingleton<TDERIVED>::GetInstance();            \
    }                                                                          \
    KM_BRANCH(TBASE::CreateInstance, TDERIVED::Ex_CreateInstance);

/**
 * @brief Defines function(s) necessary to override singleton creation.
 * @note The new/derived type must inherit from DynamicSingleton.
 */
#define K_SINGLETON_REPLACE_IMPL_DYNAMIC(TBASE, TDERIVED)                      \
    TBASE* TDERIVED::Ex_CreateInstance() {                                     \
        return TBASE::spInstance =                                             \
                   kiwi::DynamicSingleton<TDERIVED>::CreateInstance();         \
    }                                                                          \
    KM_BRANCH(TBASE::CreateInstance, TDERIVED::Ex_CreateInstance);             \
                                                                               \
    void TDERIVED::Ex_DestroyInstance() {                                      \
        kiwi::DynamicSingleton<TDERIVED>::DestroyInstance();                   \
        TBASE::spInstance = nullptr;                                           \
    }                                                                          \
    KM_BRANCH(TBASE::DestroyInstance, TDERIVED::Ex_DestroyInstance);

#endif
