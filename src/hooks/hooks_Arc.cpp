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

/**
 * @brief Sets the max arrow count in Archery
 */
u32 ArcSetMaxArrowCount() {
    return ItemMgr::GetInstance().GetArcArrowNum();
}

/**
 * @brief ArcSetMaxArrowCount trampoline
 */
TRAMPOLINE_DEF(0x8056aaac, 0x8056aab0) {
    // clang-format off
    TRAMPOLINE_BEGIN

    bl ArcSetMaxArrowCount
    mr r0, r3

    TRAMPOLINE_END
    mr r3, r0
    blr
    // clang-format on
}

} // namespace Arc
} // namespace AP
