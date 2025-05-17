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

} // namespace Png
} // namespace AP
