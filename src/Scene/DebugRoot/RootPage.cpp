#include "scene/DebugRoot/RootPage.h"

#include <libkiwi.h>

namespace AP {
namespace DebugRoot {

/**
 * @brief Constructor
 *
 * @param rMenu Parent menu
 */
RootPage::RootPage(kiwi::DebugMenu& rMenu)
    : kiwi::DebugPage(rMenu),
      mGotoMenu(rMenu, "Goto Menu", GotoMenuProc),
      mSceneDebug(rMenu, "Scene Debug", mSceneSelectPage),
      mSceneSelectPage(rMenu),
      mThreadDebug(rMenu, "Thread Debug", mThreadDebugPage),
      mThreadDebugPage(rMenu),
      mItemDebug(rMenu, "Item Debug", *this),
      mCheckDebug(rMenu, "Check Debug", *this),
      mCosmeticDebug(rMenu, "Cosmetic Debug", *this),
      mDebugConsole(rMenu, "Debug Console", DebugConsoleProc),
      mUnitTest(rMenu, "Unit Test", UnitTestProc) {

    mOptions.PushBack(&mGotoMenu);
    mOptions.PushBack(&mSceneDebug);
    mOptions.PushBack(&mThreadDebug);
    mOptions.PushBack(&mItemDebug);
    mOptions.PushBack(&mCheckDebug);
    mOptions.PushBack(&mCosmeticDebug);
    mOptions.PushBack(&mDebugConsole);
    mOptions.PushBack(&mUnitTest);

    // TODO(kiwi) Not yet implemented
    mItemDebug.SetEnabled(false);
    mCheckDebug.SetEnabled(false);
    mCosmeticDebug.SetEnabled(false);
}

/**
 * @brief Go to main menu option callback
 *
 * @param pInvoker Callback invoker
 * @param pArg Callback user argument
 * @return Result of action
 */
kiwi::EDebugMenuResult RootPage::GotoMenuProc(kiwi::DebugOptionBase* pInvoker,
                                              void* pArg) {
    kiwi::SceneCreator::GetInstance().ChangeTitleScene();

    return kiwi::EDebugMenuResult_Select;
}

/**
 * @brief Debug console option callback
 *
 * @param pInvoker Callback invoker
 * @param pArg Callback user argument
 * @return Result of action
 */
kiwi::EDebugMenuResult
RootPage::DebugConsoleProc(kiwi::DebugOptionBase* pInvoker, void* pArg) {
    kiwi::DebugConsole::GetInstance().Enter();

    return kiwi::EDebugMenuResult_Back;
}

/**
 * @brief Unit test manager option callback
 *
 * @param pInvoker Callback invoker
 * @param pArg Callback user argument
 * @return Result of action
 */
kiwi::EDebugMenuResult RootPage::UnitTestProc(kiwi::DebugOptionBase* pInvoker,
                                              void* pArg) {
    kiwi::UnitTestMgr::GetInstance().Run();

    return kiwi::EDebugMenuResult_Select;
}

} // namespace DebugRoot
} // namespace AP
