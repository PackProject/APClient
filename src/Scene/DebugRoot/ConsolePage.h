#ifndef APCLIENT_SCENE_DEBUGROOTSCENE_CONSOLE_PAGE_H
#define APCLIENT_SCENE_DEBUGROOTSCENE_CONSOLE_PAGE_H
#include <types.h>

#include <libkiwi.h>

namespace AP {
namespace DebugRoot {

/**
 * @brief Debug console page
 */
class ConsolePage : public kiwi::DebugPage {
public:
    /**
     * @brief Constructor
     *
     * @param rMenu Parent menu
     */
    explicit ConsolePage(kiwi::DebugMenu& rMenu) : kiwi::DebugPage(rMenu) {}

private:
    /**
     * @brief Updates the page state
     * @return Result of actions
     */
    virtual kiwi::EDebugMenuResult Calculate();

    /**
     * @brief User-level render pass
     */
    virtual void UserDraw() {}

    /**
     * @brief Console control main loop
     *
     * @param pConsole Text console
     */
    void ConsoleLoop(kiwi::Nw4rConsole* pConsole);
};

} // namespace DebugRoot
} // namespace AP

#endif
