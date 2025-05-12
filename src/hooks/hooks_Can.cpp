

#include "core/ItemMgr.h"
#include "hooks/trampoline.h"

#include <Sports2/Sp2Can.h>

#include <libkiwi.h>

namespace AP {
namespace Can {

/******************************************************************************
 *
 * Canoeing
 *
 ******************************************************************************/

/**
 * @brief Sets the max timer in Canoeing
 * 
 * @param pSequence Game sequence
 * 
 */
/*int CanSetHearts(int currentHearts) {
    int maxHearts = ItemMgr::GetInstance().GetCanHeartNum();
    if (currentHearts > maxHearts) {
        currentHearts = maxHearts;
    }
    return currentHearts;
}*/

/**
 * @brief CanSetTimer trampoline
 */
TRAMPOLINE_DEF(0x804aafe4, 0x804aafe8) {
    // clang-format off
    TRAMPOLINE_BEGIN

    li r5, 400

    TRAMPOLINE_END
    blr
}

} // namespace Can
} // namespace AP