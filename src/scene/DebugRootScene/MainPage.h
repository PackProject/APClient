#ifndef APCLIENT_SCENE_DEBUGROOTSCENE_MAIN_PAGE_H
#define APCLIENT_SCENE_DEBUGROOTSCENE_MAIN_PAGE_H
#include "core/const.h"
#include "scene/DebugRootScene/SubPage.h"

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
    static kiwi::EDebugMenuResult GotoMenuProc(void* pArg);

private:
    //! Example integer option
    kiwi::DebugIntOption mDummyIntOption;
    //! Example boolean option
    kiwi::DebugBoolOption mDummyBoolOption;

    //! Example sub-page, and the option to open it
    SubPage mSubPage;
    kiwi::DebugOpenPageOption mDummyOpenPageOption;

    //! Example procedure option (goto menu scene)
    kiwi::DebugProcOption mGotoMenuOption;
};

} // namespace DebugRoot
} // namespace AP

#endif
