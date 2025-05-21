#ifndef APCLIENT_SCENE_DEBUGROOTSCENE_SCENE_H
#define APCLIENT_SCENE_DEBUGROOTSCENE_SCENE_H
#include "core/const.h"
#include "scene/DebugRootScene/MainPage.h"

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
        return EAPScene_DebugRootScene;
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

private:
    //! Debug menu
    kiwi::DebugMenu mDebugMenu;
    //! Main menu page
    MainPage mMainPage;
};

} // namespace DebugRoot
} // namespace AP

#endif
