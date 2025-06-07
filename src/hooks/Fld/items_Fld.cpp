#include "core/ItemMgr.h"
#include "hooks/trampoline.h"

#include <Sports2/Sp2Cmn.h>
#include <Sports2/Sp2Fld.h>

#include <libkiwi.h>

namespace AP {
namespace Fld {

/******************************************************************************
 *
 * Frisbee Dog
 *
 ******************************************************************************/

u32 FldA2Disable(u32 inputs) {
    if (!ItemMgr::GetInstance().IsFldSecretPop()) return 0;
    else return inputs;
}

/**
 * @brief FldA2Disable trampoline
 */
TRAMPOLINE_DEF(0x805ee79c, 0x805ee7a0) {
    // clang-format off
    TRAMPOLINE_BEGIN

    lwz r0, 0x18(r3)
    mr r3, r0
    bl FldA2Disable
    mr r0, r3

    TRAMPOLINE_END
    blr
    // clang-format on
}

/**
 * @brief Sets number of frisbee throws
 */
int FldSetThrows() {
    return ItemMgr::GetInstance().GetFldThrowNum();
}

/**
 * @brief Ermmmmmmmm
 */
int FldSetThrowsBackwards() {
    return 10 - ItemMgr::GetInstance().GetFldThrowNum();
}

/**
 * @brief FldSetThrows trampoline
 */
TRAMPOLINE_DEF(0x805deda0, 0x805deda4) {
    // clang-format off
    TRAMPOLINE_BEGIN

    bl FldSetThrows
    mr r0, r3

    TRAMPOLINE_END
    mr r5, r0
    blr
    // clang-format on
}

/**
 * @brief FldSetThrowsBackwards trampoline
 */
TRAMPOLINE_DEF(0x805dc458, 0x805dc460) {
    // clang-format off
    TRAMPOLINE_BEGIN

    mr r16, r4
    bl FldSetThrowsBackwards
    lwz r15, 0x0(r16)
    add r3, r15, r3
    mr r0, r3

    TRAMPOLINE_END
    mr r30, r0
    lwz r0, 0x78(r3)
    mr r3, r30
    blr
    // clang-format on
}

} // namespace Fld
} // namespace AP