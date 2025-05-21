#ifndef APCLIENT_SCENE_DEBUGROOTSCENE_MAIN_PAGE_H
#define APCLIENT_SCENE_DEBUGROOTSCENE_MAIN_PAGE_H
#include "core/const.h"

#include <libkiwi.h>

namespace AP {
namespace DebugRoot {

/**
 * @brief Main debug menu page
 */
class MainPage : public kiwi::DebugPage {
public:
    /**
     * @brief Constructor
     */
    MainPage();

    /**
     * @brief Destructor
     */
    virtual ~MainPage() {}

    /**
     * @brief Returns to the main menu scene
     */
    static kiwi::EDebugMenuResult ReturnToMenuProc(void* pArg);

private:
    kiwi::DebugIntOption mDummyIntOption;
    kiwi::DebugBoolOption mDummyBoolOption;
    kiwi::DebugProcOption mDummyProcOption;
};

} // namespace DebugRoot
} // namespace AP

#endif
