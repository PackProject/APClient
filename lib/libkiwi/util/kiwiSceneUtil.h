#ifndef LIBKIWI_UTIL_SCENE_UTIL_H
#define LIBKIWI_UTIL_SCENE_UTIL_H
#include <Pack/RPSystem.h>
#include <libkiwi/core/kiwiIScene.h>
#include <libkiwi/k_types.h>

#include <egg/core.h>

namespace kiwi {
//! @addtogroup libkiwi_util
//! @{

/**
 * @brief Scene utilities
 */
class SceneUtil {
public:
    /**
     * @brief Gets the current scene as the EGG type
     */
    static EGG::Scene* GetCurrentScene();
    /**
     * @brief Gets the current scene as the RP type
     */
    static RPSysScene* GetCurrentSceneRP() {
        return static_cast<RPSysScene*>(GetCurrentScene());
    }
    /**
     * @brief Gets the current scene as the libkiwi type
     */
    static IScene* GetCurrentSceneKiwi() {
        return static_cast<IScene*>(GetCurrentScene());
    }

    /**
     * @brief Tests whether a given scene has a Pack Project scene ID
     * @details Call without arguments to check the current scene
     *
     * @param pScene Current scene
     */
    static bool IsScenePack(const EGG::Scene* pScene = nullptr) {
        return !IsSceneUser(pScene);
    }
    /**
     * @brief Tests whether a given scene has a user-defined scene ID
     * @details Call without arguments to check the current scene
     *
     * @param pScene Current scene
     */
    static bool IsSceneUser(const EGG::Scene* pScene = nullptr);

    /**
     * @brief Tests whether the current scene permits NAND access
     *
     * @return Whether NAND access is permitted
     */
    static bool IsNANDAccessEnable();
};

//! @}
} // namespace kiwi

#endif
