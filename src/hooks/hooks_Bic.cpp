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

// 0 hearts: 0, 0.1
// 1 hearts: 0.1, 0.333
// 2 hearts: 0.333, .56
// 3 hearts: 0.56, 1
/**
 * @brief Return the max stamina in Cycling
 * 
 * @param staminaItems Number of stamina items
 */
float BicGetMaxStamina(int staminaItems) {
    float maxStamina;
    switch(staminaItems) {
        case 0:
            maxStamina = 0.1f;
            break;
        case 1:
            maxStamina = 0.333f;
            break;
        case 2:
            maxStamina = 0.56f;
            break;
        case 3:
            maxStamina = 1.0f;
            break;
        default:
            ASSERT(false);
            break;
    }
    return maxStamina;
}

/**
 * @brief Sets the max hearts in Cycling
 * 
 * @param currentStamina Current stamina (internal)
 * 
 */
float BicSetMaxStamina(float currentStamina) {
    float maxStamina = BicGetMaxStamina(ItemMgr::GetInstance().GetBicHeartNum());

    if(currentStamina > maxStamina) {
        currentStamina = maxStamina;
    }
    return currentStamina;
}

/**
 * @brief BicSetMaxStamina trampoline
 */
TRAMPOLINE_DEF(0x803af720, 0x803af724) {
    // clang-format off
    TRAMPOLINE_BEGIN

    bl BicSetMaxStamina
    stfs f1, 0x14(r30)

    TRAMPOLINE_END
    blr
}

/**
 * @brief Sets the drinking limit in Cycling
 * 
 */
float BicSetDrinkingLimit() {
    float maxStamina = BicGetMaxStamina(ItemMgr::GetInstance().GetBicHeartNum());
    return maxStamina * 0.8f;
}

/**
 * @brief Fixes drinking to end at max stamina
 */
TRAMPOLINE_DEF(0x803afb94, 0x803afb98) {
    // clang-format off
    TRAMPOLINE_BEGIN

    fmr f2, f1
    bl BicSetDrinkingLimit
    fmr f0, f1
    fmr f1, f2

    TRAMPOLINE_END
    blr
}

} // namespace Bic
} // namespace AP