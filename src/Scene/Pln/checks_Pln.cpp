#include "Cmn/CheckMgr.h"
#include "trampoline.h"
#include <Sports2/Sp2Pln.h>

#include <libkiwi.h>

namespace AP {
namespace Pln {
namespace Check {

/******************************************************************************
 *
 * Island Flyover
 *
 ******************************************************************************/

void SetIPointGrabbed(int totalIPoints) {
    kiwi::cout << "I Points Grabbed: " << totalIPoints << kiwi::endl;

    u32 iGroup = Cmn::CheckMgr::GetIPointGroupCheckNum(totalIPoints);
    if (iGroup == 0)
        return;

    bool hasCheck = Cmn::CheckMgr::GetInstance().GetCheckState(
        CheckID(CHECK_ISLAND_FLYOVER_IPOINT_GROUP_1 + iGroup - 1));
    if (hasCheck)
        return;

    Cmn::CheckMgr::GetInstance().GiveCheckItem(
        CheckID(CHECK_ISLAND_FLYOVER_IPOINT_GROUP_1 + iGroup - 1));
}

TRAMPOLINE_DEF(0x802619c8, 0x802619cc) {
    // clang-format off
    TRAMPOLINE_BEGIN

    stb r4, 0xc2b(r3)
    mr r3, r4
    bl SetIPointGrabbed

    TRAMPOLINE_END
    blr
    // clang-format on
}

} // namespace Check
} // namespace Pln
} // namespace AP