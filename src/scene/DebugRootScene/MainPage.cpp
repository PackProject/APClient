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
      mDummyProcOption("DummyProc", ReturnToMenuProc) {

    mOptions.PushBack(&mDummyIntOption);
    mOptions.PushBack(&mDummyBoolOption);
    mOptions.PushBack(&mDummyProcOption);
}

/**
 * @brief Returns to the main menu scene
 */
kiwi::DebugMenu::EResult MainPage::ReturnToMenuProc(void* pArg) {
    kiwi::SceneCreator::GetInstance().ChangeSceneAfterFade(
        kiwi::SceneCreator::GetMenuScene());

    return kiwi::DebugMenu::EResult_Close;
}

} // namespace DebugRoot
} // namespace AP
