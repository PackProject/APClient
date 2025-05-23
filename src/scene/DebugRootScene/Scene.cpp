#include "scene/DebugRootScene/Scene.h"

#include <Sports2/Sp2Snd.h>

#include <libkiwi.h>

namespace AP {
namespace DebugRoot {

K_DECL_SCENE(Scene);

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
    kiwi::EDebugMenuResult result = mDebugMenu.Calculate();

    switch (result) {
    case kiwi::EDebugMenuResult_Invalid: {
        Sp2::Snd::startSe(SE_CMN_NG_01);
        break;
    }

    case kiwi::EDebugMenuResult_Cursor: {
        Sp2::Snd::startSe(SE_CMN_CURSOR_01);
        break;
    }

    case kiwi::EDebugMenuResult_Change: {
        Sp2::Snd::startSe(SE_CMN_CURSOR_01);
        break;
    }

    case kiwi::EDebugMenuResult_Select: {
        Sp2::Snd::startSe(SE_CMN_DECIDE_01);
        break;
    }

    case kiwi::EDebugMenuResult_Close: {
        Sp2::Snd::startSe(SE_CMN_CANCEL_01);
        break;
    }

    case kiwi::EDebugMenuResult_None:
    default: {
        break;
    }
    }
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
