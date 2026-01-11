#include "Cmn/ItemMgr.h"
#include "trampoline.h"
#include <Sports2/Sp2Pln.h>

#include <libkiwi.h>

namespace AP {
namespace Pln {
namespace Item {

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

    int timerNum = Cmn::ItemMgr::GetInstance().GetPlnTimerNum();
    pSequence->setTimeRemain(timerNum * Cmn::ItemMgr::PLN_TIMER_VALUE * 60);
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
    return Cmn::ItemMgr::GetInstance().IsPlnBalloons();
}

/**
 * @brief PlnSetBalloons trampoline
 */
TRAMPOLINE_DEF(0x8042aff0, 0x8042b010){
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
 * @brief Unlocks double blasters, night lights, two-seater plane in Island
 * Flyover
 */
u32 PlnSetMisc(u32 currentField) {

    kiwi::TBitFlag<u32> plnUnlocks = currentField;

    if (Cmn::ItemMgr::GetInstance().IsPlnDoubleBlasters()) {
        plnUnlocks.SetBit(2);
    } else {
        plnUnlocks.ResetBit(2);
    }

    if (Cmn::ItemMgr::GetInstance().IsPlnNightLights()) {
        plnUnlocks.SetBit(4);
    } else {
        plnUnlocks.ResetBit(4);
    }

    if (Cmn::ItemMgr::GetInstance().IsPlnTwoSeater()) {
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
    return Cmn::ItemMgr::GetInstance().IsPlnBrake();
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
    return Cmn::ItemMgr::GetInstance().IsPlnBoost();
}

/**
 * @brief PlnSetBoost trampolines
 */
TRAMPOLINE_DEF(0x80433f70, 0x80433f74){
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

} // namespace Item
} // namespace Pln
} // namespace AP
