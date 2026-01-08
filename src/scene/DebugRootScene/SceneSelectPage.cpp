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
    : kiwi::DebugPage(rMenu, SCENE_NUM), mSeqSelectPage(rMenu) {

    for (int i = 0; i < SCENE_NUM; i++) {
        const char* pSceneName =
            kiwi::SceneCreator::GetInstance().GetSceneName(i);

        ASSERT_PTR(pSceneName);

        kiwi::DebugProcOption* pOption =
            new kiwi::DebugProcOption(rMenu, pSceneName, SelectProc, this);

        ASSERT_PTR(pOption);

        // Store scene ID to recall later
        pOption->SetUserData(reinterpret_cast<kiwi::DebugUserData>(i));

        mpSceneOptions[i] = pOption;
        mOptions.PushBack(pOption);
    }

    // Disable scenes that would cause problems
    static const u32 badScenes[] = {
        kiwi::ESceneID_Sp2StrapScene,
        kiwi::ESceneID_Sp2SaveDataLoadScene,
    };

    for (int i = 0; i < LENGTHOF(badScenes); i++) {
        mpSceneOptions[badScenes[i]]->SetEnabled(false);
    }
}

/**
 * @brief Destructor
 */
SceneSelectPage::~SceneSelectPage() {
    for (int i = 0; i < SCENE_NUM; i++) {
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

    // Scene ID is stored as user data
    ASSERT_PTR(pInvoker);
    u32 scene = reinterpret_cast<u32>(pInvoker->GetUserData());

    p->mSeqSelectPage.SetNextScene(scene);
    p->GetMenu().OpenPage(p->mSeqSelectPage);

    return kiwi::EDebugMenuResult_Select;
}

} // namespace DebugRoot
} // namespace AP
