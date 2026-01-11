#include "Cmn/ItemMgr.h"
#include "trampoline.h"
#include <Sports2/Sp2Bwl.h>

#include <libkiwi.h>

namespace AP {
namespace Bwl {
namespace Item {

/******************************************************************************
 *
 * Bowling Standard Game
 *
 ******************************************************************************/
namespace Std {

/**
 * @brief Determines if the player can move in bowling
 */
bool BwlCheckMoveState() {
    bool unlocked = false;
    u32 sequence = RP_GET_INSTANCE(Sp2::Cmn::StaticMem)->getSceneSeq();

    switch (sequence) {
    case Sp2::Cmn::ESeq_Bwl_Std: {
        unlocked = Cmn::ItemMgr::GetInstance().IsBwlStdMove();
        break;
    }

    case Sp2::Cmn::ESeq_Bwl_100: {
        unlocked = Cmn::ItemMgr::GetInstance().IsBwl100Move();
        break;
    }

    case Sp2::Cmn::ESeq_Bwl_Wal: {
        unlocked = Cmn::ItemMgr::GetInstance().IsBwlWalMove();
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
TRAMPOLINE_DEF(0x804ea5ac, 0x804ea5b0){
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
    // clang-format on
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
    // clang-format on
}

/**
 * @brief Determines if the player can turn in bowling
 */
bool BwlCheckTurnState() {
    bool unlocked = false;
    u32 sequence = RP_GET_INSTANCE(Sp2::Cmn::StaticMem)->getSceneSeq();

    switch (sequence) {
    case Sp2::Cmn::ESeq_Bwl_Std: {
        unlocked = Cmn::ItemMgr::GetInstance().IsBwlStdTurn();
        break;
    }

    case Sp2::Cmn::ESeq_Bwl_100: {
        unlocked = Cmn::ItemMgr::GetInstance().IsBwl100Turn();
        break;
    }

    case Sp2::Cmn::ESeq_Bwl_Wal: {
        unlocked = Cmn::ItemMgr::GetInstance().IsBwlWalTurn();
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
TRAMPOLINE_DEF(0x804ea628, 0x804ea62c){
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
    // clang-format on
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
    // clang-format on
}

} // namespace Std

/******************************************************************************
 *
 * Bowling 100-Pin Game
 *
 ******************************************************************************/
namespace Pin {

/**
 * @brief Determines if the player can press the secret strike button
 */
bool BwlSecretStrike() {
    return Cmn::ItemMgr::GetInstance().IsBwl100SecretBtn();
}

/**
 * @brief BwlSecretStrike trampoline
 */
TRAMPOLINE_DEF(0x804f0058, 0x804f0068) {
    // clang-format off
    TRAMPOLINE_BEGIN

    bl BwlSecretStrike
    cmpwi r3, 0
    beq end

    li r0, 0x1
    stw r0, 0x104(r17)
    li r3, 0x472
    lis r12, 0x802b73bc@ha
    addi r12, r12, 0x802b73bc@l
    mtctr r12
    bctrl

    end:
    TRAMPOLINE_END
    blr
    // clang-format on
}

} // namespace Pin

} // namespace Item
} // namespace Bwl
} // namespace AP
