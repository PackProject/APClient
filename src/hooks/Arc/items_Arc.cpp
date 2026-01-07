#include "core/ItemMgr.h"
#include "hooks/trampoline.h"
#include <Sports2/Sp2Arc.h>

#include <libkiwi.h>

namespace AP {
namespace Arc {

/******************************************************************************
 *
 * Archery
 *
 ******************************************************************************/

/**
 * @brief Sets the aim flag in Archery
 */
bool ArcSetAimFlag(bool hold2) {
    if (!ItemMgr::GetInstance().IsArcAim())
        return false;
    else if (!hold2)
        return false;
    else
        return true;
}

/**
 * @brief ArcSetAimFlag trampoline
 */
TRAMPOLINE_DEF(0x80548828, 0x8054882c) {
    // clang-format off
    TRAMPOLINE_BEGIN

    mr r31, r3
    mr r3, r0
    bl ArcSetAimFlag
    stb r3, 0x85(r31)

    TRAMPOLINE_END
    blr
    // clang-format on
}

/**
 * @brief Sets the secret fruit flag in Archery
 */
bool ArcSetFruitFlag(int stageID) {

    int difficulty = 0;

    switch (stageID) {
    case 11:
    case 24:
    case 12:
    case 3:
        difficulty = 0;
        break;

    case 31:
    case 9:
    case 32:
    case 13:
        difficulty = 1;
        break;

    case 17:
    case 22:
    case 35:
    case 4:
        difficulty = 2;
        break;

    default:
        K_LOG_EX("stageID: %d\n", stageID);
        K_LOG_EX("difficulty: %d\n", difficulty);
        K_ASSERT(false);
    }

    return ItemMgr::GetInstance().IsArcFruitUnlock(difficulty) == 1;
}

/**
 * @brief ArcSetFruitFlag trampoline
 */

TRAMPOLINE_DEF(0x8057cbe0, 0x8057cbe4){
    // clang-format off
    TRAMPOLINE_BEGIN

    lis r12, 0x8057
    ori r12, r12, 0xcb9c

    mr r14, r3
    mr r3, r4
    bl ArcSetFruitFlag
    cmpwi r3, 1
    beq Unlocked
    mr r3, r14
    mtctr r12
    TRAMPOLINE_END
    bnectr

    Unlocked:
        nop

    TRAMPOLINE_END
    blr
    // clang-format on
}

/**
 * @brief Sets the max arrow count in Archery
 */
u32 ArcSetMaxArrowCount() {
    return ItemMgr::GetInstance().GetArcArrowNum();
}

/**
 * @brief ArcSetMaxArrowCount trampoline
 */
TRAMPOLINE_DEF(0x8056aaac, 0x8056aab0) {
    // clang-format off
    TRAMPOLINE_BEGIN

    bl ArcSetMaxArrowCount
    mr r0, r3

    TRAMPOLINE_END
    mr r3, r0
    blr
    // clang-format on
}

} // namespace Arc
} // namespace AP
