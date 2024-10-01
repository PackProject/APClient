#ifndef APCLIENT_HOOKS_TRAMPOLINE_H
#define APCLIENT_HOOKS_TRAMPOLINE_H
#include <types.h>

/**
 * @brief Defines a trampoline function
 *
 * @param enter Entry address
 */
#define TRAMPOLINE_DEF(enter) KM_BRANCH_DEF_ASM(enter, NULL)

/**
 * @brief Defines a trampoline function
 *
 * @param enter Entry address
 * @param exit Exit address
 */
#define TRAMPOLINE_DEF_EXIT(enter, exit) KM_BRANCH_DEF_ASM(enter, exit)

/**
 * @brief Saves registers at the start of a trampoline function
 */
// clang-format off
#define TRAMPOLINE_BEGIN \
    nofralloc         ;  \
    stwu r1, -0x90(r1);  \
    stmw r3,  0x0C(r1);  \
    mflr r12          ;  \
    stw  r12, 0x08(r1);
// clang-format on

/**
 * @brief Restores registers at the end of a trampoline function
 */
// clang-format off
#define TRAMPOLINE_END  \
    lwz  r12, 0x08(r1); \
    mtlr r12          ; \
    lmw  r3,  0x0C(r1); \
    addi r1, r1, 0x90 ; \
    blr               ;
// clang-format on

#endif