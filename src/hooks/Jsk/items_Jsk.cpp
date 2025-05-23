#include "core/ItemMgr.h"
#include "hooks/trampoline.h"

#include <Sports2/Jsk/Sp2Jsk.h>

#include <libkiwi.h>

namespace AP {
namespace Jsk {

/******************************************************************************
 *
 * Power Cruising
 *
 ******************************************************************************/

/**
 * @brief Sets the max timer in Power Cruising
 *
 */
int JskSetTimer() {
    return 120;
}

/**
 * @brief JskSetTimer trampoline
 */
TRAMPOLINE_DEF(0x805ae988, 0x805ae98c) {
    // clang-format off
    TRAMPOLINE_BEGIN
    
    li r4, 0
    stw r4, 0x110(r3)

    TRAMPOLINE_END
    mr r4, r0
    blr
    // clang-format on
}

/**
 * @brief Unlocks Boosting in Power Cruising
 */
bool JskSetBoost() {
    return ItemMgr::GetInstance().IsJskBoost();
}

/**
 * @brief JskSetBoost trampoline
 */
TRAMPOLINE_DEF(0x8059717c, 0x80597180) {
    // clang-format off
    TRAMPOLINE_BEGIN

    bl JskSetBoost
    cmpwi r3, 0
    beq JskCantBoost
    
    stfs f1, 0x30(r27)
    b end

    JskCantBoost:
    li r0, 0
    stw r0, 0x30(r27)

    end:
    TRAMPOLINE_END
    blr
    // clang-format on
}

/**
 * @brief Disables 2x rings in Power Cruising
 */
u32 JskUndoBonus(u32 flags) {
    kiwi::TBitFlag<u32> jskInfo = flags;
    jskInfo.ResetBit(3);
    return jskInfo;
}

/**
 * @brief Unlocks 2x rings in Power Cruising
 */
bool JskSetBonus() {
    return ItemMgr::GetInstance().IsJsk2xRing();
}

/**
 * @brief JskSetBonus trampoline
 */
TRAMPOLINE_DEF(0x8059164c, 0x80591650) {
    // clang-format off
    TRAMPOLINE_BEGIN

    //stw r0, 0x119810(r11)
    lhz r7, 0x54(r26)
    bl JskSetBonus
    cmpwi r3, 0
    beq Locked
    //lwz r0, 0x119810(r11)
    mr r0, r7
    b end

    Locked:
    mr r3, r7
    bl JskUndoBonus
    mr r0, r3

    end:
    TRAMPOLINE_END
    mr r4, r0
    //lwz r0, 0x119810(r11)
    blr
    // clang-format on
}

/**
 * @brief Sets ring timer in Power Cruising
 */
f32 JskSetRingTimer() {
    int timerCount = ItemMgr::GetInstance().GetJskRingTimerNum();
    f32 timerNums[] = {(f32)3.0, (f32)7.0, (f32)11.0};
    return timerNums[timerCount];
}

/**
 * @brief JskSetRingTimer trampoline
 */
TRAMPOLINE_DEF(0x805914a8, 0x805914ac) {
    // clang-format off
    TRAMPOLINE_BEGIN

    bl JskSetRingTimer
    stfs f1, 0xdc(r26)

    TRAMPOLINE_END
    blr
    // clang-format on
}

} // namespace Jsk
} // namespace AP
