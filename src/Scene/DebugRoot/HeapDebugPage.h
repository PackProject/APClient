#ifndef APCLIENT_SCENE_DEBUGROOTSCENE_HEAP_DEBUG_PAGE_H
#define APCLIENT_SCENE_DEBUGROOTSCENE_HEAP_DEBUG_PAGE_H
#include <types.h>

#include <libkiwi.h>

namespace AP {
namespace DebugRoot {

/**
 * @brief Heap debug page
 */
class HeapDebugPage : public kiwi::DebugPage {
public:
    /**
     * @brief Constructor
     *
     * @param rMenu Parent menu
     */
    explicit HeapDebugPage(kiwi::DebugMenu& rMenu) : kiwi::DebugPage(rMenu) {}

private:
    /**
     * @brief Updates the page state
     * @return Result of actions
     */
    virtual kiwi::EDebugMenuResult Calculate();

    /**
     * @brief User-level render pass
     */
    virtual void UserDraw();
};

} // namespace DebugRoot
} // namespace AP

#endif
