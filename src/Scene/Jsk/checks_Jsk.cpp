#include "Cmn/CheckMgr.h"
#include "trampoline.h"
#include <Sports2/Sp2Jsk.h>

#include <libkiwi.h>

namespace AP {
namespace Jsk {
namespace Check {

/******************************************************************************
 *
 * Power Cruising
 *
 ******************************************************************************/
namespace Std {

void SetJskPtCheck(int points) {
    if (points >= 15000) {
        Cmn::CheckMgr::GetInstance().SetCheckState(CHECK_POWER_CRUISING_1500_POINTS, true);
    }
}

TRAMPOLINE_DEF(0x805824ec, 0x805824f0) {
    // clang-format off
    TRAMPOLINE_BEGIN

    add r23, r3, r24
    mr r3, r23
    bl SetJskPtCheck

    TRAMPOLINE_END
    blr
}
}
} // namespace Check
} // namespace Jsk
} // namespace AP