#include "core/ItemMgr.h"
#include "hooks/trampoline.h"

#include <Sports2/Sp2Bsk.h>

#include <libkiwi.h>

namespace AP {
namespace Bsk {

/******************************************************************************
 *
 * Basketball 3 Point Contest
 *
 ******************************************************************************/

/**
 * @brief Sets the max timer in Basketball 3 Point Contest
 */
int BskSetMaxTimer() { 
    return ItemMgr::BSK_3PT_TIMER_VALUE * ItemMgr::GetInstance().GetBsk3ptTimerNum();
}

/**
 * @brief BskSetMaxTimer trampoline
 */
TRAMPOLINE_DEF(0x80521d34, 0x80521d38) {
    // clang-format off
    TRAMPOLINE_BEGIN

    bl BskSetMaxTimer
    mr r0, r3

    TRAMPOLINE_END
    mr r5, r0
    blr
}

/**
 * @brief BskSetMaxTimerVisual trampoline
 */
// TRAMPOLINE_DEF(0x80521d34, 0x80521d38) {
//     // clang-format off
//     TRAMPOLINE_BEGIN

//     li r5, 7
//     mr r0, r5

//     TRAMPOLINE_END
//     mr r5, r0
//     blr


/******************************************************************************
 *
 * Basketball Pickup Game
 *
 ******************************************************************************/

 int BskVsSetMaxTimer() {
    return ItemMgr::BSK_VS_TIMER_VALUE * ItemMgr::GetInstance().GetBskVsTimerNum();
 }

 TRAMPOLINE_DEF(0x80507c6c, 0x80507c70) {
    // clang-format off
    TRAMPOLINE_BEGIN

    bl BskVsSetMaxTimer
    mr r0, r3

    TRAMPOLINE_END
    mr r4, r0
    blr

}

/**
 * @brief BskVsSetMaxTimerVisual trampoline
 */
bool BskHasPassUnlocked() {
    return ItemMgr::GetInstance().IsBskVsPassUnlocked();
}

TRAMPOLINE_DEF(0x8052ce98, 0x8052ce9c) {
    // clang-format off
    TRAMPOLINE_BEGIN

    mr r31, r3
    mr r30, r4
    mr r28, r5
    bl BskHasPassUnlocked
    cmpwi r3, 0
    beq end

    mr r3, r31
    mr r4, r30
    mr r5, r28
    lis r12, 0x80513b54@ha
    addi r12, r12, 0x80513b54@l
    mtctr r12
    bctrl

    end:
    TRAMPOLINE_END
    blr
}

} // namespace Basketball
} // namespace AP