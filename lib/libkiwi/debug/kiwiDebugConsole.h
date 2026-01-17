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
class DebugConsole : public Nw4rConsole, public DynamicSingleton<DebugConsole> {
public:
    /**
     * @brief Enters the console main loop
     */
    void Enter();

private:
    /**
     * @brief Draws the console using DirectPrint
     */
    virtual void DrawDirect();

    /**
     * @brief Console main loop
     */
    void MainLoop();
};

//! @}
} // namespace kiwi

#endif
