#include "core/CheckMgr.h"
#include "hooks/trampoline.h"

#include <Sports2/Sp2Cmn.h>

#include <libkiwi.h>

namespace AP {
namespace Cmn {

/******************************************************************************
 *
 * Common
 *
 ******************************************************************************/

void SetStampCheckIfNew(int playerDataPtr,int sportID,int stampIdx) {
    int stampID = (sportID * 5) + stampIdx;
    bool hasCheck = CheckMgr::GetInstance().GetCheckState(CheckMgr::CheckID(stampID));
    if(!hasCheck) {
        CheckMgr::GetInstance().GiveItemFromCheck(CheckMgr::CheckID(stampID));
        hasCheck = CheckMgr::GetInstance().GetCheckState(CheckMgr::CheckID(stampID));
        kiwi::cout << "Stamp Check: " << CheckMgr::GetInstance().GetCheckName(CheckMgr::CheckID(stampID)) << " has been set to " << hasCheck << kiwi::endl;
    }
    else
        kiwi::cout << "Already has check..." << kiwi::endl;
}

TRAMPOLINE_DEF(0x802619e8, 0x802619ec) {
    TRAMPOLINE_BEGIN

    mr r31, r3
    mr r30, r4
    mr r29, r5
    bl SetStampCheckIfNew

    mr r3, r31
    mr r4, r30
    mr r5, r29
    mulli r4, r4, 0x14
    mr r0, r4
    TRAMPOLINE_END
    mr r4, r0
    blr
}

} // namespace Cmn
} // namespace AP