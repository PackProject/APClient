#ifndef LIBKIWI_CONFIG_H
#define LIBKIWI_CONFIG_H

// Your custom defines
#if defined(LIBKIWI_USER_CONFIG)
#include LIBKIWI_USER_CONFIG
#endif

// Default to big endian byte order
#if !defined(LIBKIWI_ENDIAN_LITTLE) && !defined(LIBKIWI_ENDIAN_BIG)
#define LIBKIWI_ENDIAN_BIG
#endif

// Build target macros
#if defined(REVOLUTION)
#define LIBKIWI_TARGET_RVL
#else
#error Please define a build target!
#endif

// Inline assembly macros
#if defined(LIBKIWI_TARGET_RVL)
// Hide from VSCode
#if !defined(__INTELLISENSE__)
#define K_REGISTER register
#define K_ASM asm
#else
#define K_REGISTER
#define K_ASM(...)
#endif
#endif

// Declare a function as inline
#define K_INLINE inline

// Stop a function from inlining
#if defined(LIBKIWI_TARGET_RVL)
#define K_DONT_INLINE __attribute__((never_inline))
#else
#define K_DONT_INLINE
#endif

// Declare a function/some data with weak linkage
#if defined(LIBKIWI_TARGET_RVL)
#define K_WEAK __attribute__((weak))
#else
#define K_WEAK
#endif

// Expose private members only to Kamek hooks
#if defined(LIBKIWI_INTERNAL)
#define LIBKIWI_KAMEK_PUBLIC public:
#else
#define LIBKIWI_KAMEK_PUBLIC
#endif

// 'typeof'
#define K_TYPEOF(x) __typeof__(x)
// 'decltype'
#define K_DECLTYPE(x) __decltype__(x)

// Primitive array length
#define K_LENGTHOF(x) static_cast<size_t>(sizeof((x)) / sizeof((x)[0]))

// C++ exclusive options
#if defined(__cplusplus)

// Some versions of CW allow C++11
#if defined(__MWERKS__) && __option(cpp1x)
#define LIBKIWI_CPP1X
#elif __cplusplus >= 199711L
#define LIBKIWI_CPP1X
#endif

// nullptr evalutes to NULL when not supported
#if !defined(LIBKIWI_CPP1X)
#define nullptr NULL
#endif

#endif // __cplusplus

#endif
