#include <Pack/RPGraphics.h>
#include <Pack/RPKernel.h>

#include <libkiwi.h>

namespace kiwi {

/**
 * @brief Setup scene
 */
void IScene::Configure() {
    // Setup renderer view
    RPGrpScreen* pScreen = new RPGrpScreen();
    K_ASSERT_PTR(pScreen);

    pScreen->SetFarZ(10000.0f);
    pScreen->SetCanvasMode(RPGrpScreen::CANVASMODE_CC);

    // Create 2D view for layout draw
    RPGrpRenderer::GetCurrent()->CreateView2D(1, pScreen);
    RPGrpRenderer::GetCurrent()->CorrectView();

    // User state function
    OnConfigure();
}

/**
 * @brief Load required assets
 */
void IScene::LoadResource() {
    // User state function
    OnLoadResource();
}

/**
 * @brief Reload scene
 */
void IScene::Reset() {
    // User state function
    OnReset();
}

/**
 * @brief Scene logic
 */
void IScene::Calculate() {
    // User state function
    OnCalculate();
}

#if defined(PACK_RESORT)
/**
 * @brief Scene MotionPlus logic
 */
void IScene::CalculateMPlus() {
    // User state function
    OnCalculateMPlus();
}
#endif

/**
 * @brief Exit scene
 */
void IScene::Exit() {
    // User state function
    OnExit();
}

/**
 * @brief User-level draw
 */
void IScene::UserDraw() {
    // User state function
    OnUserDraw();
}

/**
 * @brief Debug-level draw
 */
void IScene::DebugDraw() {
    // User state function
    OnDebugDraw();
}

} // namespace kiwi
