#ifndef APCLIENT_SCENE_DEBUGROOTSCENE_SCENE_H
#define APCLIENT_SCENE_DEBUGROOTSCENE_SCENE_H
#include "core/const.h"
#include "scene/DebugRootScene/RootPage.h"

#include <libkiwi.h>

namespace AP {
namespace DebugRoot {

/**
 * @brief Root debug menu scene
 */
class Scene : public kiwi::IScene {
public:
    /**
     * @brief Constructor
     */
    Scene();
    /**
     * @brief Destructor
     */
    virtual ~Scene() {}

    /**
     * @brief Gets the scene's ID
     */
    virtual s32 GetID() const {
        return ESceneID_DebugRootScene;
    }
    /**
     * @brief Gets the scene's target pack
     */
    virtual kiwi::EPackID GetPack() const {
        return kiwi::EPackID_SportsPack;
    }

    /**
     * @brief Performs initial scene setup
     */
    virtual void OnConfigure();
    /**
     * @brief Runs one step of scene logic
     */
    virtual void OnCalculate();
    /**
     * @brief User-level draw
     */
    virtual void OnUserDraw();

private:
    //! Debug menu
    kiwi::DebugMenu mDebugMenu;
    //! Root menu page
    RootPage mRootPage;

    //! Ambient sound effect timer
    u32 mAmbientTimer;
    //! Scene exit timer
    s32 mExitTimer;
};

} // namespace DebugRoot
} // namespace AP

#endif
