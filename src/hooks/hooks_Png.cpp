#include "core/ItemMgr.h"
#include "hooks/trampoline.h"

#include <Sports2/Sp2Png.h>

#include <libkiwi.h>

namespace AP {
namespace Png {

/******************************************************************************
 *
 * Table Tennis
 *
 ******************************************************************************/

/**
 * @brief Unlocks Boosting in Table Tennis
 */
bool PngCanSmashHit() {
    return ItemMgr::GetInstance().IsPngSmash();
}

/**
 * @brief PngCanSmashHit trampoline
 */
TRAMPOLINE_DEF(0x80467470, 0x80467474) {
    // clang-format off
    TRAMPOLINE_BEGIN

    bl PngCanSmashHit
    cmpwi r3, 0
    beq end
    stw r0,0x0(r9)

    end:
    TRAMPOLINE_END
    blr
    // clang-format on
}

/**
 * @brief Unlocks Cans in Table Tennis Return Challenge
 */
bool PngHasCansUnlocked() {
    return ItemMgr::GetInstance().IsPngCans();
}

/**
 * @brief PngCanSpinHit trampoline
 */
TRAMPOLINE_DEF(0x80482800, 0x80482804) {
    // clang-format off
    TRAMPOLINE_BEGIN

    mr r31, r3
    bl PngHasCansUnlocked
    cmpwi r3, 0
    beq end

    mr r3, r31
    lis r12, 0x8048762c@ha
    addi r12, r12, 0x8048762c@l
    mtctr r12
    bctrl

    end:
    TRAMPOLINE_END
    blr
    // clang-format on
}

} // namespace Png
} // namespace AP
