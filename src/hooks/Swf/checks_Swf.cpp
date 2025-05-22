#include "core/CheckMgr.h"
#include "hooks/trampoline.h"

#include <Sports2/Sp2Swf.h>

#include <libkiwi.h>

namespace AP {
namespace Swf {
namespace {

/******************************************************************************
 *
 * Swordplay
 *
 ******************************************************************************/

void GetSwordplayFirstWinCheck() {
    bool hasCheck = CheckMgr::GetInstance().GetCheckState(CheckMgr::CheckID(CheckMgr::SWORDPLAY_DUEL_FIRST_WIN));
    if(!hasCheck) {
        CheckMgr::GetInstance().GiveItemFromCheck(CheckMgr::CheckID(CheckMgr::SWORDPLAY_DUEL_FIRST_WIN));
        hasCheck = CheckMgr::GetInstance().GetCheckState(CheckMgr::CheckID(CheckMgr::SWORDPLAY_DUEL_FIRST_WIN));
        kiwi::cout << "Check: " << CheckMgr::GetInstance().GetCheckName(CheckMgr::CheckID(CheckMgr::SWORDPLAY_DUEL_FIRST_WIN)) << " has been set to " << hasCheck << kiwi::endl;
    }
    else
        kiwi::cout << "Already has check..." << kiwi::endl;
}


TRAMPOLINE_DEF(0x802b1e34, 0x802b1e38) {
    TRAMPOLINE_BEGIN

    bl GetSwordplayFirstWinCheck
    cmpwi r0, 0x1
    mfcr r0

    TRAMPOLINE_END
    mtcr r0
    blr
}

} // namespace
} // namespace Swf
} // namespace AP