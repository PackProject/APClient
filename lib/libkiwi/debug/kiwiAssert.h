#ifndef LIBKIWI_DEBUG_ASSERT_H
#define LIBKIWI_DEBUG_ASSERT_H
#include <libkiwi/k_types.h>
#include <libkiwi/util/kiwiPtrUtil.h>

#include <cmath>

//! @addtogroup libkiwi_debug
//! @{

/**
 * @name External usage
 * @brief Removes K_ prefix for user code
 */
/**@{*/
//! Log a message to the console
#define LOG(msg) K_LOG(msg)
//! Log a message (format string) to the console
#define LOG_EX(msg, ...) K_LOG_EX(msg, __VA_ARGS__)

//! Log an error if the condition is TRUE
#define WARN(exp) K_WARN(exp)
//! Log a custom message if the condition is TRUE
#define WARN_EX(exp, ...) K_WARN_EX(exp, __VA_ARGS__)

//! Halt the program if the condition is FALSE
#define ASSERT(exp) K_ASSERT(exp)
//! Halt the program and display a message if the condition is FALSE
#define ASSERT_EX(exp, ...) K_ASSERT_EX(exp, __VA_ARGS__)

//! Assert that the pointer falls into a valid memory region
#define ASSERT_PTR(exp) K_ASSERT_PTR(exp)
//! Assert that the pointer falls into a valid memory region
#define ASSERT_PTR_EX(exp, ...) K_ASSERT_PTR_EX(exp, __VA_ARGS__)

//! Assert that the floating-point value is a finite, non-NaN value
#define ASSERT_FP(exp) K_ASSERT_FP(exp)

//! Assert that a code path is unreachable
#define UNREACHABLE() K_UNREACHABLE()
//! Denote a function as not implemented
#define NOT_IMPLEMENTED() K_NOT_IMPLEMENTED()

//! Compile-time assertion
#define STATIC_ASSERT(exp) K_STATIC_ASSERT(exp)
//! Compile-time assertion with a custom message
#define STATIC_ASSERT_EX(exp, msg) K_STATIC_ASSERT_EX(exp, msg)

//! For compatability with modern libraries
#define static_assert(exp, msg) K_STATIC_ASSERT_EX(exp, msg)
/**@}*/

/**
 * @name Internal usage
 */
/**@{*/
#if !defined(NDEBUG)
//! Log a message to the console
#define K_LOG(msg) kiwi_log(msg)
//! Log a message (format string) to the console
#define K_LOG_EX(msg, ...) kiwi_log(msg, __VA_ARGS__)

//! Log an error if the condition is TRUE
#define K_WARN(exp) ((exp) ? kiwi_log(#exp) : (void)0)
//! Log a custom message if the condition is TRUE
#define K_WARN_EX(exp, ...) ((exp) ? kiwi_log(__VA_ARGS__) : (void)0)

//! Halt the program if the condition is FALSE
#define K_ASSERT(exp)                                                          \
    (!(exp) ? kiwi_fail_assert(__FILE__, __LINE__, #exp) : (void)0)
//! Halt the program and display a message if the condition is FALSE
#define K_ASSERT_EX(exp, ...)                                                  \
    (!(exp) ? kiwi_fail_assert(__FILE__, __LINE__, __VA_ARGS__) : (void)0)

//! Assert that the pointer falls into a valid memory region
#define K_ASSERT_PTR(exp)                                                      \
    K_ASSERT_EX(kiwi::PtrUtil::IsPointer(exp),                                 \
                #exp " is not a valid pointer (=0x%08X)", exp)
//! Assert that the pointer falls into a valid memory region
#define K_ASSERT_PTR_EX(exp, ...)                                              \
    K_ASSERT_EX(kiwi::PtrUtil::IsPointer(exp), __VA_ARGS__)

//! Assert that the floating-point value is a finite, non-NaN value
#define K_ASSERT_FP(exp)                                                       \
    K_ASSERT_EX(isfinite(exp) && !isnan(exp), #exp " is infinite or nan")

//! Assert that a code path is unreachable
#define K_UNREACHABLE() K_ASSERT_EX(false, "Unreachable code")

//! Denote a function as not implemented
#define K_NOT_IMPLEMENTED() K_ASSERT_EX(false, "Not yet implemented")
#else
#define K_LOG(msg) (void)0
#define K_LOG_EX(msg, ...) (void)0

#define K_WARN(exp) (void)0
#define K_WARN_EX(exp, ...) (void)0

#define K_ASSERT(exp) (void)0
#define K_ASSERT_EX(exp, ...) (void)0

#define K_ASSERT_PTR(exp) (void)0
#define K_ASSERT_FP(exp) (void)0

#define K_UNREACHABLE() (void)0

#define K_NOT_IMPLEMENTED() (void)0
#endif

//! Compile-time assertion
#define K_STATIC_ASSERT(exp) extern u8 __K_PREDICATE[(exp) ? 1 : -1]
#define K_STATIC_ASSERT_EX(exp, msg) K_STATIC_ASSERT(exp)
/**@}*/

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Logs a message to the console
 *
 * @param pMsg Message
 * @param ... Format string arguments
 */
void kiwi_log(const char* pMsg, ...);

/**
 * @brief Halts the program and displays an error message to the screen/console
 *
 * @param pFile Source file name where assertion failed
 * @param line Source file line where assertion failed
 * @param pMsg Assertion message
 * @param ... Format string arguments
 */
void kiwi_fail_assert(const char* pFile, int line, const char* pMsg, ...);

#ifdef __cplusplus
}
#endif

//! @}

#endif
