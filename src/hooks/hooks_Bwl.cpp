#include "core/ItemMgr.h"
#include "hooks/trampoline.h"

#include <Sports2/Sp2Bwl.h>

#include <libkiwi.h>

namespace AP {
namespace Bowling {

/******************************************************************************
 *
 * Bowling Standard Game
 *
 ******************************************************************************/

/**
 * @brief Determines if the player can move in bowling
 */
bool BwlCheckMoveState() {
    return ItemMgr::GetInstance().IsBwlMoveUnlocked();
}

/**
 * @brief BwlSetPosition trampoline (move left)
 */
TRAMPOLINE_DEF(0x804ea5ac, 0x804ea5b0) {
    // clang-format off
    TRAMPOLINE_BEGIN

    BwlMoveLogic:
        bl BwlCheckMoveState
        cmpwi r3, 0
        beq BwlCantMove
        stfs f0, 0x4e0 (r31)

    BwlCantMove:

    TRAMPOLINE_END
    blr
}

/**
 * @brief BwlSetPosition trampoline (move right)
 */
TRAMPOLINE_DEF(0x804ea5dc, 0x804ea5e0) {
    // clang-format off
    TRAMPOLINE_BEGIN

    BwlMoveLogic:
        bl BwlCheckMoveState
        cmpwi r3, 0
        beq BwlCantMove
        stfs f0, 0x4e0 (r31)

    BwlCantMove:

    TRAMPOLINE_END
    blr
}

} // namespace Bowling
} // namespace AP