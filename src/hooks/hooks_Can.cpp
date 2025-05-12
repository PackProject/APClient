

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
 * @param difficulty Difficulty level
 * addresses for difficulty level timer setting: 0x804af188, 0x804af1e4
 * 
 */
int CanSetTimer(int difficulty) {
    // switch(difficulty) {
    //     case 0:
    //         return 10;
    //     case 1: 
    //         return 20;
    //     case 2:
    //         return 30;
    //     case 3:
    //         return 40;
    //     case 4:
    //         return 50;
    // }

    return 50;
}

/**
 * @brief CanSetTimer trampoline
 */
TRAMPOLINE_DEF(0x804af1fc, 0x804af200) {
    // clang-format off
    TRAMPOLINE_BEGIN

    li r3, 50

    TRAMPOLINE_END
    blr
}

} // namespace Can
} // namespace AP