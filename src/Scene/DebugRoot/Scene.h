#ifndef APCLIENT_SCENE_DEBUGROOTSCENE_SCENE_H
#define APCLIENT_SCENE_DEBUGROOTSCENE_SCENE_H
#include "const.h"
#include "scene/DebugRoot/RootPage.h"

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
    /**
     * @brief State machine state
     */
    enum EState {
        EState_Menu, //!< Waiting for menu control
        EState_Exit, //!< Exiting the scene

        EState_Max
    };

    //! Time before fading out when exiting the scene
    static const u32 EXIT_TIMER = 30;

private:
    /**
     * @brief Updates the scene in the Menu state
     */
    K_STATE_DECL(Menu);

    /**
     * @brief Updates the scene in the Exit state
     */
    K_STATE_DECL(Exit);

private:
    //! Logic state machine
    kiwi::StateMachine<Scene> mStateMachine;

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
