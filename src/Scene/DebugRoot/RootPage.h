#ifndef APCLIENT_SCENE_DEBUGROOTSCENE_ROOT_PAGE_H
#define APCLIENT_SCENE_DEBUGROOTSCENE_ROOT_PAGE_H
#include "const.h"
#include "scene/DebugRoot/ConsolePage.h"
#include "scene/DebugRoot/SceneSelectPage.h"
#include "scene/DebugRoot/ThreadDebugPage.h"

#include <libkiwi.h>

namespace AP {
namespace DebugRoot {

/**
 * @brief Root debug menu page
 */
class RootPage : public kiwi::DebugPage {
public:
    /**
     * @brief Constructor
     *
     * @param rMenu Parent menu
     */
    explicit RootPage(kiwi::DebugMenu& rMenu);

    /**
     * @brief Go to main menu option callback
     *
     * @param pInvoker Callback invoker
     * @param pArg Callback user argument
     * @return Result of action
     */
    static kiwi::EDebugMenuResult GotoMenuProc(kiwi::DebugOptionBase* pInvoker,
                                               void* pArg);

    /**
     * @brief Unit test manager option callback
     *
     * @param pInvoker Callback invoker
     * @param pArg Callback user argument
     * @return Result of action
     */
    static kiwi::EDebugMenuResult UnitTestProc(kiwi::DebugOptionBase* pInvoker,
                                               void* pArg);

private:
    //! Go to main menu
    kiwi::DebugProcOption mGotoMenu;

    //! Debug scene select
    kiwi::DebugOpenPageOption mSceneDebug;
    SceneSelectPage mSceneSelectPage;

    //! Thread debug
    kiwi::DebugOpenPageOption mThreadDebug;
    ThreadDebugPage mThreadDebugPage;

    //! AP item debug
    kiwi::DebugOpenPageOption mItemDebug;
    // ItemDebugPage mItemDebugPage;

    //! AP check debug
    kiwi::DebugOpenPageOption mCheckDebug;
    // ItemDebugPage mItemDebugPage;

    //! AP cosmetic debug
    kiwi::DebugOpenPageOption mCosmeticDebug;
    // ItemDebugPage mItemDebugPage;

    //! Toggle debug console
    kiwi::DebugOpenPageOption mDebugConsole;
    ConsolePage mConsolePage;

    //! Unit test manager
    kiwi::DebugProcOption mUnitTest;
};

} // namespace DebugRoot
} // namespace AP

#endif
