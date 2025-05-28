#include "core/ItemMgr.h"
#include "hooks/trampoline.h"

#include <Sports2/Sp2Pln.h>

#include <libkiwi.h>

namespace AP {
namespace Pln {

/******************************************************************************
 *
 * Island Flyover
 *
 ******************************************************************************/

/**
 * @brief Sets the timer in Island Flyover
 *
 * @param pSequence Game sequence
 *
 */
void PlnSetTimer(Sp2::Pln::IslandSeq* pSequence) {
    ASSERT(pSequence != nullptr);

    int timerNum = ItemMgr::GetInstance().GetPlnTimerNum();
    pSequence->setTimeRemain(timerNum * ItemMgr::PLN_TIMER_VALUE * 60);
}

/**
 * @brief PlnSetTimer trampoline
 */
TRAMPOLINE_DEF(0x80428898, 0x8042889C) {
    // clang-format off
    TRAMPOLINE_BEGIN

    mr r3, r31
    bl PlnSetTimer

    TRAMPOLINE_END
    blr
    // clang-format on
}

/**
 * @brief Unlocks balloons in Island Flyover
 */
bool PlnSetBalloons() {
    return ItemMgr::GetInstance().IsPlnBalloonsUnlock();
}

/**
 * @brief PlnSetBalloons trampoline
 */
TRAMPOLINE_DEF(0x8042aff0, 0x8042b010) {
    // clang-format off
    TRAMPOLINE_BEGIN

    bl PlnSetBalloons
    cmpwi r3, 0
    beq Locked
    b End
   
Locked:
    lis r14, 0x8042
    ori r14, r14, 0xb340
    mtctr r14
    TRAMPOLINE_END
    bctrl

End:
    TRAMPOLINE_END
    blr
    // clang-format on
}

/**
 * @brief Unlocks double blasters, night lights, two-seater plane in Island Flyover
 */
u32 PlnSetMisc(u32 currentField) {

    kiwi::TBitFlag<u32> plnUnlocks = currentField;

    if (ItemMgr::GetInstance().IsPlnDoubleBlastersUnlock()) {
        plnUnlocks.SetBit(2);
    } else {
        plnUnlocks.ResetBit(2);
    }

    if (ItemMgr::GetInstance().IsPlnNightLightsUnlock()) {
        plnUnlocks.SetBit(4);
    } else {
        plnUnlocks.ResetBit(4);
    }
    
    if (ItemMgr::GetInstance().IsPlnTwoSeaterUnlock()) {
        plnUnlocks.SetBit(5);
    } else {
        plnUnlocks.ResetBit(5);
    }
    
    return plnUnlocks;
}

/**
 * @brief PlnSetMisc trampoline
 */
TRAMPOLINE_DEF(0x804455e0, 0x804455e4) {
    // clang-format off
    TRAMPOLINE_BEGIN

    mr r14, r6
    mr r3, r0
    bl PlnSetMisc
    sth r3, 0x3358(r14)
    mr r0, r3

    TRAMPOLINE_END
    lis r4, 0x807d
    blr
    // clang-format on
}

/**
 * @brief Unlocks braking in Island Flyover
 */
bool PlnSetBrake() {
    return ItemMgr::GetInstance().IsPlnBrakeUnlock();
}

/**
 * @brief PlnSetBrake trampoline
*/
TRAMPOLINE_DEF(0x80433858, 0x8043385c) {
    // clang-format off
    TRAMPOLINE_BEGIN

    mr r14, r0
    bl PlnSetBrake
    cmpwi r3, 1
    beq Unlocked
    b Locked

Unlocked:
    TRAMPOLINE_END
    mr r0, r14
    stb r6, 0x120(r3)
    b Exit
Locked:
    TRAMPOLINE_END
    mr r0, r14
Exit:
    blr
    // clang-format on
}

/**
 * @brief Unlocks boosting in Island Flyover
 */
bool PlnSetBoost() {
    return ItemMgr::GetInstance().IsPlnBoostUnlock();
}

/**
 * @brief PlnSetBoost trampolines
*/
TRAMPOLINE_DEF(0x80433f70, 0x80433f74) {
    // clang-format off
    TRAMPOLINE_BEGIN

    mr r14, r0
    bl PlnSetBoost
    cmpwi r3, 1
    beq Unlocked
    b Locked

Unlocked:
    mr r0, r14
    TRAMPOLINE_END
    stb r0, 0x120(r29)
    b Exit
Locked:
    mr r0, r14
    TRAMPOLINE_END
Exit:
    blr
    // clang-format on
}

TRAMPOLINE_DEF(0x80433f28, 0x80433f2c) {
    // clang-format off
    TRAMPOLINE_BEGIN

    mr r14, r0
    bl PlnSetBoost
    cmpwi r3, 1
    beq Unlocked
    b Locked

Unlocked:
    mr r0, r14
    TRAMPOLINE_END
    stb r0, 0x120(r29)
    b Exit
Locked:
    mr r0, r14
    TRAMPOLINE_END
Exit:
    blr
    // clang-format on
}

} // namespace Pln
} // namespace AP
