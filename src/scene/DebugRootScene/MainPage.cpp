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

    AddOption(mDummyIntOption);
    AddOption(mDummyBoolOption);
    AddOption(mDummyProcOption);
}

/**
 * @brief Returns to the main menu scene
 */
kiwi::EDebugMenuResult MainPage::ReturnToMenuProc(void* pArg) {
    kiwi::SceneCreator::GetInstance().ChangeSceneAfterFade(
        kiwi::SceneCreator::GetMenuScene());

    return kiwi::EDebugMenuResult_Close;
}

} // namespace DebugRoot
} // namespace AP
