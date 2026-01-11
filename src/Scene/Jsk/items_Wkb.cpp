#include "Cmn/ItemMgr.h"
#include "trampoline.h"
#include <Sports2/Sp2Jsk.h>

#include <libkiwi.h>

namespace AP {
namespace Wkb {
namespace Item {

/******************************************************************************
 *
 * Wakeboarding
 *
 ******************************************************************************/

/**
 * @brief Sets the timer in Wakeboarding
 *
 * @param pSequence Game sequence
 */
void WkbSetTimer(Sp2::Jsk::IslandSeq* pSequence) {
    ASSERT(pSequence != nullptr);

    u32 timerNum = Cmn::ItemMgr::GetInstance().GetWkbTimerNum();
    pSequence->setTimeRemain(timerNum * Cmn::ItemMgr::WKB_TIMER_VALUE);
}

/**
 * @brief WkbSetTimer trampoline
 */
TRAMPOLINE_DEF(0x8058329C, 0x805832A0) {
    // clang-format off
    TRAMPOLINE_BEGIN

    mr r3, r31
    bl WkbSetTimer

    TRAMPOLINE_END
    blr
    // clang-format on
}

// /**
//  * @brief Tests whether the specified stage is unlocked in Swordplay
//  (Showdown)
//  *
//  * @param id Stage ID
//  */
// Sp2::Cmn::EUnlockState SglGetStageState(UNKWORD, UNKWORD, u32 id) {
//     bool unlock = Cmn::ItemMgr::GetInstance().IsSwfSglStageUnlock(id);

//     return unlock ? Sp2::Cmn::EUnlockState_Unlocked
//                   : Sp2::Cmn::EUnlockState_Locked;
// }
// KM_BRANCH(0x802E4848, SglGetStageState);

} // namespace Item
} // namespace Wkb
} // namespace AP
