#include "core/ItemMgr.h"
#include "hooks/trampoline.h"

#include <Sports2/Sp2Bsk.h>

#include <libkiwi.h>

namespace AP {
namespace Basketball {

/******************************************************************************
 *
 * Basketball 3 Point Contest
 *
 ******************************************************************************/

/**
 * @brief Sets the max timer in Basketball 3 Point Contest
 */
int BskSetMaxTimer() {
    return ItemMgr::BSK_TIMER_VALUE * ItemMgr::GetInstance().GetBskTimerNum();
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

 TRAMPOLINE_DEF(0x80535c28, 0x80535c2c) {
    // clang-format off
    TRAMPOLINE_BEGIN

    li r4, 1000

    TRAMPOLINE_END
    blr

}


} // namespace Basketball
} // namespace AP