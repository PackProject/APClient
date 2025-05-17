#include "core/ItemMgr.h"
#include "hooks/trampoline.h"

#include <Sports2/Sp2Arc.h>

#include <libkiwi.h>

namespace AP {
namespace Arc {

/******************************************************************************
 *
 * Archery
 *
 ******************************************************************************/

/**
 * @brief Sets the aim flag in Archery
 */
bool ArcSetAimFlag(bool hold2) {
    if (!ItemMgr::GetInstance().IsArcAim()) return false;
    else if (!hold2) return false;
    else return true;
}

/**
 * @brief ArcSetMaxArrowCount trampoline
 */
TRAMPOLINE_DEF(0x80548828, 0x8054882c) {
    // clang-format off
    TRAMPOLINE_BEGIN

    mr r31, r3
    mr r3, r0
    bl ArcSetAimFlag
    stb r3, 0x85(r31)

    TRAMPOLINE_END
    blr
    // clang-format on
}

} // namespace Arc
} // namespace AP
