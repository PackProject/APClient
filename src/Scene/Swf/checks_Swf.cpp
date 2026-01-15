#include "Cmn/CheckMgr.h"
#include "trampoline.h"
#include <Sports2/Sp2Swf.h>

#include <libkiwi.h>

namespace AP {
namespace Swf {
namespace Check {

/******************************************************************************
 *
 * Swordplay
 *
 ******************************************************************************/

void GetSwordplayFirstWinCheck() {
    bool hasCheck = Cmn::CheckMgr::GetInstance().GetCheckState(
        CheckID(CHECK_SWORDPLAY_DUEL_FIRST_WIN));

    if (!hasCheck) {
        Cmn::CheckMgr::GetInstance().SetCheckState(
            CheckID(CHECK_SWORDPLAY_DUEL_FIRST_WIN), true);
    }
}

TRAMPOLINE_DEF(0x802b1e34, 0x802b1e38) {
    // clang-format off
    TRAMPOLINE_BEGIN

    bl GetSwordplayFirstWinCheck
    cmpwi r0, 0x1
    mfcr r0

    TRAMPOLINE_END
    mtcr r0
    blr
    // clang-format on
}

} // namespace Check
} // namespace Swf
} // namespace AP