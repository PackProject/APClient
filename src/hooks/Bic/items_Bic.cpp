#include "core/ItemMgr.h"
#include "hooks/trampoline.h"
#include <Sports2/Sp2Bic.h>

#include <libkiwi.h>

namespace AP {
namespace Bic {

/******************************************************************************
 *
 * Cycling
 *
 ******************************************************************************/

/**
 * @brief Maximum energy per heart amount
 * @details hearts = ceil((E - 0.1f) * 3 / 0.7f)
 */
static const f32 scHeartMaxEnergy[ItemMgr::BIC_HEART_COUNT + 1] = {
    0.100000f, // Zero hearts
    0.333333f, // One heart
    0.566666f, // Two hearts
    1.0f       // Three hearts
};

/**
 * @brief Sets the initial number of hearts
 *
 * @param pCyclist Cyclist object
 */
void BicInitHeartNum(Sp2::Bic::Cyclist* pCyclist) {
    ASSERT(pCyclist != nullptr);

    pCyclist->setHeartNum(ItemMgr::GetInstance().GetBicHeartNum());
}

/**
 * @brief BicInitHeartNum trampoline
 */
TRAMPOLINE_DEF(0x803afd74, 0x803afd78){
    // clang-format off
    TRAMPOLINE_BEGIN

    bl BicInitHeartNum

    TRAMPOLINE_END
    blr
    // clang-format on
}

/**
 * @brief Updates the cyclist's energy level
 *
 * @param pCyclist Cyclist object
 * @param energy Current energy level
 */
f32 BicCalcEnergy(Sp2::Bic::Cyclist* pCyclist, f32 energy) {
    ASSERT(pCyclist != nullptr);
    energy = kiwi::Clamp(energy, 0.0f, 1.0f);

    // Energy is capped by heart AP items
    f32 energyLimit = scHeartMaxEnergy[ItemMgr::GetInstance().GetBicHeartNum()];
    energy = kiwi::Min(energy, energyLimit);

    pCyclist->setEnergy(energy);
    return energy;
}

/**
 * @brief BicCalcEnergy trampoline
 */
TRAMPOLINE_DEF(0x803af720, 0x803af724) {
    // clang-format off
    TRAMPOLINE_BEGIN

    mr r3, r30
    bl BicCalcEnergy

    TRAMPOLINE_END
    blr
    // clang-format on
}

/**
 * @brief Adjusts the drinking state for the energy AP items
 */
void BicCalcDrinking(Sp2::Bic::Cyclist* pCyclist) {
    ASSERT(pCyclist != nullptr);
    ASSERT(pCyclist->getState() == Sp2::Bic::Cyclist::EState_Drinking);

    // Drinking restores 80% energy
    f32 drinkLimit = scHeartMaxEnergy[ItemMgr::GetInstance().GetBicHeartNum()];
    drinkLimit *= 0.80f;

    if (pCyclist->getEnergy() >= drinkLimit) {
        pCyclist->setState(Sp2::Bic::Cyclist::EState_Idle);
    }
}

/**
 * @brief BicCalcDrinking trampoline
 */
TRAMPOLINE_DEF(0x803afb90, 0x803afcb8) {
    // clang-format off
    TRAMPOLINE_BEGIN

    mr r3, r30
    bl BicCalcDrinking

    TRAMPOLINE_END
    blr
    // clang-format on
}

} // namespace Bic
} // namespace AP
