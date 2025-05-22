#include "core/CheckMgr.h"
#include "hooks/trampoline.h"

#include <Sports2/Sp2Bwl.h>

#include <libkiwi.h>

namespace AP {
namespace Bwl {
namespace {
namespace Std {

/******************************************************************************
 *
 * Bowling Standard Game
 *
 ******************************************************************************/

void SetBowlingStrikeCheck() {
    bool hasCheck = CheckMgr::GetInstance().GetCheckState(CheckMgr::CheckID(CheckMgr::BOWLING_STANDARD_FIRST_STRIKE));
    if(hasCheck) return;

    CheckMgr::GetInstance().GiveItemFromCheck(CheckMgr::CheckID(CheckMgr::BOWLING_STANDARD_FIRST_STRIKE));
}

TRAMPOLINE_DEF(0x804ece1c, 0x804ece20) {
    TRAMPOLINE_BEGIN

    li r0, 0x451
    bl SetBowlingStrikeCheck

    TRAMPOLINE_END
    mr r3, r0
    blr
}



} // namespace Std
} // namespace
} // namespace Bwl
} // namespace AP