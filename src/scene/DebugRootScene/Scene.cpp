#include "scene/DebugRootScene/Scene.h"

#include <libkiwi.h>

namespace AP {
namespace DebugRoot {

K_SCENE_DECL(Scene);

/**
 * @brief Constructor
 */
Scene::Scene() : mDebugMenu(&mMainPage) {}

/**
 * @brief Calculate state user callback
 */
void Scene::OnCalculate() {
    mDebugMenu.Calculate();
}

} // namespace DebugRoot
} // namespace AP
