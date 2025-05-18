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

} // namespace Fld
} // namespace AP