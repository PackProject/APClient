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

} // namespace Glf
} // namespace AP