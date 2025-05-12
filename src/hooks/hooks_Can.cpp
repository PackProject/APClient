

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
 * addresses for difficulty level timer setting: 0x804af180, 0x804af1e4
 * addresses for function call: 804af1fc, 0x804af200
 * 
 */
int CanSetTimer(int difficulty) {
    int difficultyTimer;
    switch(difficulty) {
        case 1: 
            difficultyTimer = 60;
        case 2:
            difficultyTimer = 80;
        case 3:
            difficultyTimer = 100;
        default:
            difficultyTimer = 60;
    }

    float timer = (float)difficultyTimer /
        (ItemMgr::CAN_TIMER_COUNT - ItemMgr::GetInstance().GetCanTimerNum());
    return timer;
}

/**
 * @brief CanSetTimer trampoline
 */
TRAMPOLINE_DEF(0x804af188, 0x804af1e0) {

    TRAMPOLINE_BEGIN

    mr r3, r0
    bl CanSetTimer
    mr r0, r3

    TRAMPOLINE_END
    mr r3, r0

    blr

}

} // namespace Can
} // namespace AP