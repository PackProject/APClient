#include "Cmn/SceneHook.h"

#include "Cmn/TextDisplay.h"
#include "Net/GameMessageListener.h"

#include <libkiwi.h>

K_DYNAMIC_SINGLETON_IMPL(AP::Cmn::SceneHook);

namespace AP {
namespace Cmn {

/**
 * @brief Constructor
 */
SceneHook::SceneHook() : mpListener(nullptr), mpTextDisplay(nullptr) {
    mpListener = new Net::GameMessageListener();
    ASSERT_PTR(mpListener);

    mpTextDisplay = new TextDisplay();
    ASSERT_PTR(mpTextDisplay);
}

/**
 * @brief Destructor
 */
SceneHook::~SceneHook() {
    delete mpListener;
    mpListener = nullptr;

    delete mpTextDisplay;
    mpTextDisplay = nullptr;
}

/**
 * @brief Handles scene Configure event
 *
 * @param pScene Current scene
 */
void SceneHook::Configure(RPSysScene* pScene) {
    if (pScene->getSceneID() == kiwi::SceneCreator::GetBootScene()) {
        return;
    }

    ASSERT_PTR(mpTextDisplay);
    mpTextDisplay->Configure();
}

/**
 * @brief Handles scene Calculate event
 *
 * @param pScene Current scene
 */
void SceneHook::AfterCalculate(RPSysScene* pScene) {
    if (pScene->getSceneID() == kiwi::SceneCreator::GetBootScene()) {
        return;
    }

    ASSERT_PTR(mpTextDisplay);
    mpTextDisplay->Calculate();
}

} // namespace Cmn
} // namespace AP