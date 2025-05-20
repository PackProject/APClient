#include "core/ItemMgr.h"
#include "hooks/trampoline.h"

#include <Sports2/Sp2Bsk.h>

#include <libkiwi.h>

namespace AP {
namespace Bsk {

//! Timer frame-rate (frames/timer sec)
static const u32 TIMER_RATE = 60;

/******************************************************************************
 *
 * Basketball (3-Point Contest)
 *
 ******************************************************************************/
namespace Pt3 {

//! Number of basketballs in each rack
static const u32 RACK_BALL_NUM = 5;

/**
 * @brief Sets the initial timer
 *
 * @param pSequence 3-Point Contest sequence
 */
void InitTimer(Sp2::Bsk::Sequence3pt* pSequence) {
    ASSERT(pSequence != nullptr);

    u32 timerNum = ItemMgr::GetInstance().GetBsk3ptTimerNum();
    u32 timerSec = timerNum * ItemMgr::BSK_3PT_TIMER_VALUE;

    pSequence->getMainLyt()->setTimer(timerSec, TIMER_RATE);
}

/**
 * @brief InitTimer trampoline
 */
TRAMPOLINE_DEF(0x80521D38, 0x80521D3C) {
    // clang-format off
    TRAMPOLINE_BEGIN

    mr r3, r31
    bl InitTimer

    TRAMPOLINE_END
    blr
    // clang-format on
}

/**
 * @brief Initializes the ball type
 *
 * @param pBall Basketball object
 * @param id Basketball ID
 */
void InitBallType(Sp2::Bsk::Ball* pBall, s32 id) {
    ASSERT(pBall != nullptr);
    ASSERT(id == -1 || (id >= 0 && id < RACK_BALL_NUM));

    // Last ball in the rack is a bonus ball
    Sp2::Bsk::Ball::EType type = id == RACK_BALL_NUM - 1
                                     ? Sp2::Bsk::Ball::EType_Bonus
                                     : Sp2::Bsk::Ball::EType_Regular;

    // Bonus balls locked behind the item
    if (!ItemMgr::GetInstance().IsBsk3ptBonus()) {
        type = Sp2::Bsk::Ball::EType_Regular;
    }

    pBall->setType(type);
}

/**
 * @brief InitBallType trampoline
 */
TRAMPOLINE_DEF(0x80522CFC, 0x80522D10) {
    // clang-format off
    TRAMPOLINE_BEGIN

    mr r3, r15
    mr r4, r19
    bl InitBallType

    TRAMPOLINE_END
    blr
    // clang-format on
}

} // namespace Pt3

/******************************************************************************
 *
 * Basketball (Pickup Game)
 *
 ******************************************************************************/
namespace Vs {

/**
 * @brief Sets the initial timer
 *
 * @param pSequence Pickup Game sequence
 */
void InitTimer(Sp2::Bsk::SequenceVs* pSequence) {
    ASSERT(pSequence != nullptr);

    u32 timerNum = ItemMgr::GetInstance().GetBskVsTimerNum();
    u32 timerSec = timerNum * ItemMgr::BSK_VS_TIMER_VALUE;

    pSequence->getMainLyt()->setTimer(timerSec, TIMER_RATE);
}

/**
 * @brief InitTimer trampoline
 */
TRAMPOLINE_DEF(0x80507C74, 0x80507C78) {
    // clang-format off
    TRAMPOLINE_BEGIN

    mr r3, r27
    bl InitTimer

    TRAMPOLINE_END
    blr
    // clang-format on
}

bool HasPassUnlocked() {
    return ItemMgr::GetInstance().IsBskVsPass();
}

TRAMPOLINE_DEF(0x8052ce98, 0x8052ce9c) {
    // clang-format off
    TRAMPOLINE_BEGIN

    mr r31, r3
    mr r30, r4
    mr r28, r5
    bl HasPassUnlocked
    cmpwi r3, 0
    beq end

    mr r3, r31
    mr r4, r30
    mr r5, r28
    lis r12, 0x80513b54@ha
    addi r12, r12, 0x80513b54@l
    mtctr r12
    bctrl

    end:
    TRAMPOLINE_END
    blr
    // clang-format on
}

bool Has3ptUnlocked() {
    return ItemMgr::GetInstance().IsBskVs3pt();
}

TRAMPOLINE_DEF(0x8050685C, 0x80506860) {
    // clang-format off
    TRAMPOLINE_BEGIN
    lwz r0, 0x11C(r27)
    cmpwi r0, 3
    bne End // not 3pt

    bl Has3ptUnlocked
    cmpwi r3, 0
    beq NotUnlocked
    li r0, 3 // 3pt allowed
    b End

NotUnlocked:
    li r0, 2 // limit to 2pt

End:
    stw r0, 0x11C(r27) // update for future

    TRAMPOLINE_END
    blr
    // clang-format on
}

} // namespace Vs

} // namespace Bsk
} // namespace AP
