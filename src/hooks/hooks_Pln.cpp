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
    pSequence->setTimeRemain(60 *
                             250); //(timerNum * ItemMgr::PLN_TIMER_VALUE * 60);
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

} // namespace Pln
} // namespace AP
