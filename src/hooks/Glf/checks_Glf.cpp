#include "core/CheckMgr.h"
#include "hooks/trampoline.h"

#include <Sports2/Sp2Glf.h>

#include <libkiwi.h>

namespace AP {
namespace Glf {
namespace {

/******************************************************************************
 *
 * Golf
 *
 ******************************************************************************/

void SetGolfHoleComplete(int holeIdx) {
    bool hasCheck = CheckMgr::GetInstance().GetCheckState(CheckMgr::CheckID(CheckMgr::GOLF_COMPLTE_HOLE_1 + holeIdx));
    if(hasCheck) return;

    CheckMgr::GetInstance().GiveItemFromCheck(CheckMgr::CheckID(CheckMgr::GOLF_COMPLTE_HOLE_1 + holeIdx));
}

TRAMPOLINE_DEF(0x803f76b0, 0x803f76b4) {
    TRAMPOLINE_BEGIN

    stb r0, 0x19(r3)
    lis r3, 0x80CE
    ori r3, r3, 0x6B97
    lbz r3, 0x0(r3)
    bl SetGolfHoleComplete

    TRAMPOLINE_END
    blr
}

TRAMPOLINE_DEF(0x804069f8, 0x804069fc) {
    TRAMPOLINE_BEGIN

    stw r0, 0x8(r29)
    lis r3, 0x80CE
    ori r3, r3, 0x6B97
    lbz r3, 0x0(r3)
    subi r3, r3, 1
    bl SetGolfHoleComplete
    
    TRAMPOLINE_END
    blr
}

} // namespace
} // namespace Glf
} // namespace AP