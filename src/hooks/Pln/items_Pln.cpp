#include "core/ItemMgr.h"
#include "hooks/trampoline.h"

#include <Sports2/Sp2Pln.h>

#include <libkiwi.h>

namespace AP {
namespace Pln {

/******************************************************************************
 *
 * Island Flyover
 *
 ******************************************************************************/

/**
 * @brief Sets the timer in Island Flyover
 *
 * @param pSequence Game sequence
 *
 */
void PlnSetTimer(Sp2::Pln::IslandSeq* pSequence) {
    ASSERT(pSequence != nullptr);

    int timerNum = ItemMgr::GetInstance().GetPlnTimerNum();
    pSequence->setTimeRemain(timerNum * ItemMgr::PLN_TIMER_VALUE * 60);
}

/**
 * @brief PlnSetTimer trampoline
 */
TRAMPOLINE_DEF(0x80428898, 0x8042889C) {
    // clang-format off
    TRAMPOLINE_BEGIN

    mr r3, r31
    bl PlnSetTimer

    TRAMPOLINE_END
    blr
    // clang-format on
}

/**
 * @brief Unlocks balloons in Island Flyover
 */
bool PlnSetBalloons() {
    return ItemMgr::GetInstance().IsPlnBalloonsUnlock();
}

/**
 * @brief PlnSetBalloons trampoline
 */
TRAMPOLINE_DEF(0x8042aff0, 0x8042b010) {
    // clang-format off
    TRAMPOLINE_BEGIN

    bl PlnSetBalloons
    cmpwi r3, 0
    beq Locked
    b End
   
Locked:
    lis r14, 0x8042
    ori r14, r14, 0xb340
    mtctr r14
    TRAMPOLINE_END
    bctrl

End:
    TRAMPOLINE_END
    blr
    // clang-format on
}

} // namespace Pln
} // namespace AP
