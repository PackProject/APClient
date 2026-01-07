#include <libkiwi.h>

namespace kiwi {

/**
 * @brief Gets the current scene as the EGG type
 */
EGG::Scene* SceneUtil::GetCurrentScene() {
    EGG::Scene* pScene = RP_GET_INSTANCE(RPSysSceneMgr)->getCurrentScene();
    K_ASSERT_PTR(pScene);

    return pScene;
}

/**
 * @brief Tests whether a given scene has a user-defined scene ID
 * @details Call without arguments to check the current scene
 *
 * @param pScene Current scene
 */
bool SceneUtil::IsSceneUser(const EGG::Scene* pScene) {
    K_ASSERT_PTR(pScene);

    return pScene->getSceneID() >= ESceneID_Max;
}

/**
 * @brief Tests whether the current scene permits NAND access
 *
 * @return Whether NAND access is permitted
 */
bool SceneUtil::IsNANDAccessEnable() {
    return GetCurrentSceneRP()->isNandAccessEnable();
}

} // namespace kiwi