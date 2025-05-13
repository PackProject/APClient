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
    bool unlocked = false;
    u32 sequence = RP_GET_INSTANCE(Sp2::Cmn::StaticMem)->getSequence();

    switch (sequence) {
        case Sp2::Cmn::ESeq_Bwl_Std: {
            unlocked = ItemMgr::GetInstance().IsBwlStdMoveUnlocked();
            break;
        }

        case Sp2::Cmn::ESeq_Bwl_100: {
            unlocked = ItemMgr::GetInstance().IsBwl100MoveUnlocked();
            break;
        }

        case Sp2::Cmn::ESeq_Bwl_Wal: {
            unlocked = ItemMgr::GetInstance().IsBwlWalMoveUnlocked();
            break;
        }

        default: {
        ASSERT_EX(false, "Invalid sequence %d", sequence);
        break;
        }
    }

    return unlocked;
}

/**
 * @brief BwlCheckMoveState trampoline (move left)
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
 * @brief BwlCheckMoveState trampoline (move right)
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

/**
 * @brief Determines if the player can turn in bowling
 */
bool BwlCheckTurnState() {
    bool unlocked = false;
    u32 sequence = RP_GET_INSTANCE(Sp2::Cmn::StaticMem)->getSequence();

    switch (sequence) {
        case Sp2::Cmn::ESeq_Bwl_Std: {
            unlocked = ItemMgr::GetInstance().IsBwlStdTurnUnlocked();
            break;
        }

        case Sp2::Cmn::ESeq_Bwl_100: {
            unlocked = ItemMgr::GetInstance().IsBwl100TurnUnlocked();
            break;
        }

        case Sp2::Cmn::ESeq_Bwl_Wal: {
            unlocked = ItemMgr::GetInstance().IsBwlWalTurnUnlocked();
            break;
        }

        default: {
        ASSERT_EX(false, "Invalid sequence %d", sequence);
        break;
        }
    }

    return unlocked;
}

/**
 * @brief BwlCheckTurnState trampoline (turn left)
 */
TRAMPOLINE_DEF(0x804ea628, 0x804ea62c) {
    // clang-format off
    TRAMPOLINE_BEGIN

    BwlTurnLogic:
        bl BwlCheckTurnState
        cmpwi r3, 0
        beq BwlCantTurn
        stfs f0, 0x4dc(r31)

    BwlCantTurn:

    TRAMPOLINE_END
    blr
}

/**
 * @brief BwlCheckTurnState trampoline (turn right)
 */
TRAMPOLINE_DEF(0x804ea658, 0x804ea65C) {
    // clang-format off
    TRAMPOLINE_BEGIN

    BwlTurnLogic:
        bl BwlCheckTurnState
        cmpwi r3, 0
        beq BwlCantTurn
        stfs f0, 0x4dc(r31)

    BwlCantTurn:

    TRAMPOLINE_END
    blr
}

} // namespace Bowling
} // namespace AP