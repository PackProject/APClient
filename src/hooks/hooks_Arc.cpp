#include "core/ItemMgr.h"
#include "hooks/trampoline.h"

#include <Sports2/Sp2Arc.h>

#include <libkiwi.h>

namespace AP {
namespace Arc {

/******************************************************************************
 *
 * Archery
 *
 ******************************************************************************/

/**
 * @brief Sets the max arrows in Archery
 */
float ArcSetMaxArrowCount() {}

/**
 * @brief ArcSetMaxArrowCount trampoline
 */
TRAMPOLINE_DEF(0x80549cf0, 0x80549cf4) {
    // clang-format off
    TRAMPOLINE_BEGIN

    li r0, 2

    TRAMPOLINE_END
    blr
    // clang-format on
}

} // namespace Arc
} // namespace AP
