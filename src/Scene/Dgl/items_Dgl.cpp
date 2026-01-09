#include "Cmn/ItemMgr.h"
#include "trampoline.h"
#include <Sports2/Sp2Cmn.h>
#include <Sports2/Sp2Dgl.h>

#include <libkiwi.h>

namespace AP {
namespace Dgl {
namespace Item {

/******************************************************************************
 *
 * Frisbee Golf
 *
 ******************************************************************************/
void DglSetBlindFlag(bool hold2) {
    if (hold2 || !Cmn::ItemMgr::GetInstance().IsDglHUD()) {
        RP_GET_INSTANCE(Sp2::Cmn::StaticMem)->setVariable(3, 1, false);
    }

    else {
        RP_GET_INSTANCE(Sp2::Cmn::StaticMem)->setVariable(3, 0, false);
    }
}

/**
 * @brief GlfSetBlindFlag trampoline
 */
TRAMPOLINE_DEF(0x802287d4, 0x802287e8) {
    // clang-format off
    TRAMPOLINE_BEGIN

    bl DglSetBlindFlag

    TRAMPOLINE_END
    blr
    // clang-format on
}

} // namespace Item
} // namespace Dgl
} // namespace AP
