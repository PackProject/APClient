#ifndef APCLIENT_HOOKS_TRAMPOLINE_H
#define APCLIENT_HOOKS_TRAMPOLINE_H
#include <types.h>

/**
 * @brief Defines a trampoline function
 *
 * @param enter Entry address
 */
#define TRAMPOLINE_DEF(enter, exit) KM_BRANCH_DEF_ASM(enter, exit)

/******************************************************************************
 *
 * Save/restore all registers (r3-r31)
 *
 ******************************************************************************/

/**
 * @brief Saves *ALL* registers at the start of a trampoline function
 */
// clang-format off
#define TRAMPOLINE_BEGIN \
    nofralloc          ; \
    stwu r1, -0x100(r1); \
    stmw r3,  0x0C(r1) ; \
    mflr r12           ; \
    stw  r12, 0x08(r1) ; \
    mfcr r12           ; \
    stw  r12, 0x88(r1) ;
// clang-format on

/**
 * @brief Restores registers at the end of a trampoline function
 */
// clang-format off
#define TRAMPOLINE_END  \
    lwz  r12, 0x88(r1); \
    mtcr r12          ; \
    lwz  r12, 0x08(r1); \
    mtlr r12          ; \
    lmw  r3, 0x0C(r1) ; \
    addi r1, r1, 0x100;
// clang-format on

/******************************************************************************
 *
 * Save/restore only saved registers (r14-r31)
 *
 ******************************************************************************/

/**
 * @brief Saves only saved registers at the start of a trampoline function
 */
// clang-format off
#define TRAMPOLINE_BEGIN_SAVED \
    nofralloc          ;       \
    stwu r1, -0x100(r1);       \
    stmw r14, 0x0C(r1) ;       \
    mflr r12           ;       \
    stw  r12, 0x08(r1) ;       \
    mfcr r12           ;       \
    stw  r12, 0x88(r1) ;
// clang-format on

/**
 * @brief Restores only saved registers at the end of a trampoline function
 */
// clang-format off
#define TRAMPOLINE_END_SAVED  \
    lwz  r12, 0x88(r1);       \
    mtcr r12          ;       \
    lwz  r12, 0x08(r1);       \
    mtlr r12          ;       \
    lmw  r14, 0x0C(r1);       \
    addi r1, r1, 0x100;
// clang-format on

#endif