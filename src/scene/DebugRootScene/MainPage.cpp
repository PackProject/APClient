#include "scene/DebugRootScene/MainPage.h"

#include <libkiwi.h>

namespace AP {
namespace DebugRoot {

/**
 * @brief Constructor
 */
MainPage::MainPage()
    : mDummyIntOption("DummyInt", 0, 5),
      mDummyBoolOption("DummyBool"),
      mDummyOpenPageOption("DummyOpenPage", mSubPage),
      mGotoMenuOption("Goto Menu", GotoMenuProc) {

    AddOption(mDummyIntOption);
    AddOption(mDummyBoolOption);
    AddOption(mDummyOpenPageOption);
    AddOption(mGotoMenuOption);
}

/**
 * @brief Returns to the main menu scene
 */
kiwi::EDebugMenuResult MainPage::GotoMenuProc(void* pArg) {
    kiwi::SceneCreator::GetInstance().ChangeSceneAfterFade(
        kiwi::SceneCreator::GetMenuScene());

    return kiwi::EDebugMenuResult_Select;
}

} // namespace DebugRoot
} // namespace AP
