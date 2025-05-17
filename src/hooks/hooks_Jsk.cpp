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

    TRAMPOLINE_BEGIN

    li r4, 0
    stw r4, 0x110(r3)

    TRAMPOLINE_END
    mr r4, r0

    blr

}

/**
 * @brief Unlocks Boosting in Power Cruising
 */
bool JskSetBoost() {
    return ItemMgr::GetInstance().IsJskBoostUnlocked();
}

/**
 * @brief JskSetBoost
 */
TRAMPOLINE_DEF(0x8059717c, 0x80597180) {

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
}

} // namespace Jsk
} // namespace AP