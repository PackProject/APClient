#include "core/CheckMgr.h"
#include "hooks/trampoline.h"

#include <Sports2/Sp2Pln.h>

#include <libkiwi.h>

namespace AP {
namespace Pln {
namespace {

/******************************************************************************
 *
 * Island Flyover
 *
 ******************************************************************************/

void SetIPointGrabbed(int totalIPoints) {
    kiwi::cout << "I Points Grabbed: " << totalIPoints << kiwi::endl;
    int iGroup = CheckMgr::GetInstance().GetNumGroupIPointObtained(totalIPoints);
    if(iGroup == 99) return;

    bool hasCheck = CheckMgr::GetInstance().GetCheckState(CheckMgr::CheckID(CheckMgr::ISLAND_FLYOVER_IPOINT_GROUP_1 + iGroup - 1));
    if(hasCheck) return;

    CheckMgr::GetInstance().GiveItemFromCheck(CheckMgr::CheckID(CheckMgr::ISLAND_FLYOVER_IPOINT_GROUP_1 + iGroup - 1));
}


TRAMPOLINE_DEF(0x802619c8, 0x802619cc) {
    TRAMPOLINE_BEGIN

    stb r4, 0xc2b(r3)
    mr r3, r4
    bl SetIPointGrabbed

    TRAMPOLINE_END
    blr
}


}
} // namespace Pln
} // namespace AP