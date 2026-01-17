#ifndef LIBKIWI_DEBUG_DEBUG_CONSOLE_H
#define LIBKIWI_DEBUG_DEBUG_CONSOLE_H
#include <libkiwi/debug/kiwiNw4rConsole.h>
#include <libkiwi/k_types.h>
#include <libkiwi/util/kiwiDynamicSingleton.h>

#include <revolution/GX.h>

namespace kiwi {
//! @addtogroup libkiwi_debug
//! @{

/**
 * @brief Debugging console output
 */
class DebugConsole : public Nw4rConsole,
                     public DynamicSingleton<DebugConsole> {};

//! @}
} // namespace kiwi

#endif
