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

} // namespace Jsk
} // namespace AP