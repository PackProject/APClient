#include "Cmn/CheckMgr.h"
#include "trampoline.h"
#include <Sports2/Sp2Jsk.h>

#include <libkiwi.h>

namespace AP {
namespace Wkb {
namespace Check {

/******************************************************************************
 *
 * Wakeboarding
 *
 ******************************************************************************/
namespace Std {

void SetWakeboardingPointsCheck(int points) {
    if(points >= 1500) {
        Cmn::CheckMgr::GetInstance().SetCheckState(CHECK_WAKEBOARDING_1500_POINTS, true);
    }
}

TRAMPOLINE_DEF(0x805b2d94, 0x805b2d98) {
    // clang-format off
    nofralloc
    cmpw r0, r4    
    TRAMPOLINE_BEGIN_FRAME

    mr r3, r4
    bl SetWakeboardingPointsCheck

    TRAMPOLINE_END
    blr
}

} // namespace Std

} // namespace Check
} // namespace Wkb
} // namespace AP