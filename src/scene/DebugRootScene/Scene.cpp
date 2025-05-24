#include "scene/DebugRootScene/Scene.h"

#include <Sports2/Sp2Snd.h>

#include <libkiwi.h>

namespace AP {
namespace DebugRoot {

K_DECL_SCENE(Scene);

/**
 * @brief Constructor
 */
Scene::Scene()
    : mDebugMenu(mRootPage),
      mRootPage(mDebugMenu),
      mAmbientTimer(0),
      mExitTimer(0) {}

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
    // 1/10 chance to play resort-themed sound effect every second
    if ((++mAmbientTimer % 60) == 0 && kiwi::Random().Chance(0.1f)) {
        switch (kiwi::Random().NextU32() % 3) {
        case 0: {
            Sp2::Snd::startSe(SE_CMN_TITLE_COAST);
            break;
        }

        case 1: {
            Sp2::Snd::startSe(SE_CMN_TITLE_COAST);
            break;
        }

        case 2: {
            Sp2::Snd::startSe(SE_CMN_SEAGULL_CHIRP);
            break;
        }
        }
    }

    // Let sound effects finish before exiting
    if (mExitTimer > 0) {
        if (--mExitTimer <= 0) {
            kiwi::SceneCreator::GetInstance().ChangeMenuScene();
        }

        return;
    }

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

    case kiwi::EDebugMenuResult_Back: {
        Sp2::Snd::startSe(SE_CMN_CANCEL_01);
        break;
    }

    case kiwi::EDebugMenuResult_Exit: {
        Sp2::Snd::startSe(SE_CMN_CANCEL_01);
        mExitTimer = 30;
        break;
    }

    case kiwi::EDebugMenuResult_None: {
        break;
    }

    default: {
        UNREACHABLE();
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
