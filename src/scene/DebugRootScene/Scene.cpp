#include "scene/DebugRootScene/Scene.h"

#include <libkiwi.h>

namespace AP {
namespace DebugRoot {

K_SCENE_DECL(Scene);

/**
 * @brief Constructor
 */
Scene::Scene() : mDebugMenu(mMainPage) {}

/**
 * @brief Performs initial scene setup
 */
void Scene::OnConfigure() {
    RPGrpRenderer::GetCurrent()->AppendDrawObject(&mDebugMenu);
}

/**
 * @brief Calculate state user callback
 */
void Scene::OnCalculate() {
    mDebugMenu.Calculate();
}

/**
 * @brief User-level draw
 */
void Scene::OnUserDraw() {
    kiwi::Text(kiwi::GetBuildPack())
        .SetPosition(0.75, 0.85)
        .SetScale(0.7)
        .SetTextColor(kiwi::Color::YELLOW)
        .SetStrokeType(kiwi::ETextStroke_Outline);

    kiwi::Text(kiwi::GetBuildTarget())
        .SetPosition(0.75, 0.88)
        .SetScale(0.7)
        .SetTextColor(kiwi::Color::YELLOW)
        .SetStrokeType(kiwi::ETextStroke_Outline);

    kiwi::Text(kiwi::GetBuildDate())
        .SetPosition(0.75, 0.91)
        .SetScale(0.7)
        .SetTextColor(kiwi::Color::YELLOW)
        .SetStrokeType(kiwi::ETextStroke_Outline);
}

} // namespace DebugRoot
} // namespace AP
