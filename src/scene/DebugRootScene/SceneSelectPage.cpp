#include "scene/DebugRootScene/SceneSelectPage.h"

#include <libkiwi.h>

namespace AP {
namespace DebugRoot {

/**
 * @brief Constructor
 *
 * @param rMenu Parent menu
 */
SceneSelectPage::SceneSelectPage(kiwi::DebugMenu& rMenu)
    : kiwi::DebugPage(rMenu, scOptionNum), mSeqSelectPage(rMenu) {

    for (int i = 0; i < scOptionNum; i++) {
        const char* pSceneName =
            kiwi::SceneCreator::GetInstance().GetSceneName(FIRST_SCENE_ID + i);

        ASSERT_PTR(pSceneName);

        kiwi::DebugProcOption* pOption =
            new kiwi::DebugProcOption(rMenu, pSceneName, SelectProc, this);

        ASSERT_PTR(pOption);

        mOptions.PushBack(pOption);
        mpSceneOptions[i] = pOption;
    }
}

/**
 * @brief Destructor
 */
SceneSelectPage::~SceneSelectPage() {
    for (int i = 0; i < scOptionNum; i++) {
        delete mpSceneOptions[i];
        mpSceneOptions[i] = nullptr;
    }
}

/**
 * @brief Option select callback
 *
 * @param pInvoker Callback invoker
 * @param pArg Callback user argument
 * @return Result of action
 */
kiwi::EDebugMenuResult
SceneSelectPage::SelectProc(kiwi::DebugOptionBase* pInvoker, void* pArg) {
    ASSERT_PTR(pArg);
    SceneSelectPage* p = static_cast<SceneSelectPage*>(pArg);

    // Pass on the selected scene ID
    s32 scene = p->mCursor + SceneSelectPage::FIRST_SCENE_ID;
    p->mSeqSelectPage.SetNextScene(scene);

    // Open sequence select
    p->GetMenu().OpenPage(p->mSeqSelectPage);

    return kiwi::EDebugMenuResult_Select;
}

} // namespace DebugRoot
} // namespace AP
