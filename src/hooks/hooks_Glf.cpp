#include "core/ItemMgr.h"
#include "hooks/trampoline.h"

#include <Sports2/Sp2Cmn.h>
#include <Sports2/Sp2Glf.h>

#include <libkiwi.h>

namespace AP {
namespace Glf {

/******************************************************************************
 *
 * Golf
 *
 ******************************************************************************/
void GlfSetBlindFlag(bool hold2) {
    if (hold2 || !ItemMgr::GetInstance().IsGlfHUD()) {
        RP_GET_INSTANCE(Sp2::Cmn::StaticMem)->setStaticVar(3, 1, false);
    }

    else {
        RP_GET_INSTANCE(Sp2::Cmn::StaticMem)->setStaticVar(3, 0, false);
    }
}

u32 GlfDisableZoom(u32 input) {
    if (!ItemMgr::GetInstance().IsGlfViewLow()) return 0;
    else return input;
}

u32 GlfDisableTopo(u32 input) {
    if (!ItemMgr::GetInstance().IsGlfViewSlope()) return 0;
    else return input;
}

/**
 * @brief GlfSetBlindFlag trampoline
 */
TRAMPOLINE_DEF(0x80406a1c, 0x80406a30) {
    // clang-format off
    TRAMPOLINE_BEGIN

    bl GlfSetBlindFlag

    TRAMPOLINE_END
    blr
    // clang-format on
}

/**
 * @brief GlfDisableZoom trampoline
 */
TRAMPOLINE_DEF(0x803facdc, 0x803face0) {
    // clang-format off
    TRAMPOLINE_BEGIN

    lwz r0, 0x1c(r31)
    mr r3, r0
    bl GlfDisableZoom
    mr r0, r3

    TRAMPOLINE_END
    blr
    // clang-format on
}

/**
 * @brief GlfDisableTopo trampoline
 */
TRAMPOLINE_DEF(0x803fac64, 0x803fac68) {
    // clang-format off
    TRAMPOLINE_BEGIN

    lwz r0, 0x1c(r31)
    mr r3, r0
    bl GlfDisableTopo
    mr r0, r3

    TRAMPOLINE_END
    blr
    // clang-format on
}

} // namespace Glf
} // namespace AP