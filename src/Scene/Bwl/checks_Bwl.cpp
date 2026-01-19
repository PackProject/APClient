#include "Cmn/CheckMgr.h"
#include "trampoline.h"
#include <Sports2/Sp2Bwl.h>

#include <libkiwi.h>

namespace AP {
namespace Bwl {
namespace Check {

/******************************************************************************
 *
 * Bowling Standard Game
 *
 ******************************************************************************/
namespace Std {

void SetBowlingStrikeCheck() {
    Cmn::CheckMgr::GetInstance().SetCheckState(CHECK_BOWLING_STANDARD_FIRST_STRIKE, true);
}

TRAMPOLINE_DEF(0x804ece1c, 0x804ece20) {
    // clang-format off
    TRAMPOLINE_BEGIN

    bl SetBowlingStrikeCheck

    TRAMPOLINE_END
    li r3, 0x451
    blr
    // clang-format on
}

} // namespace Std

} // namespace Check
} // namespace Bwl
} // namespace AP