#ifndef APCLIENT_SCENE_DEBUGROOTSCENE_SEQ_SELECT_PAGE_H
#define APCLIENT_SCENE_DEBUGROOTSCENE_SEQ_SELECT_PAGE_H
#include <types.h>

#include <libkiwi.h>

namespace AP {
namespace DebugRoot {

/**
 * @brief Debug menu sequence select
 */
class SeqSelectPage : public kiwi::DebugPage {
public:
    /**
     * @brief Constructor
     *
     * @param rMenu Parent menu
     */
    SeqSelectPage(kiwi::DebugMenu& rMenu);

    /**
     * @brief Sets the next scene ID
     *
     * @param scene Scene ID
     */
    void SetNextScene(s32 scene);

    /**
     * @brief Updates the menu state
     * @return Result of actions
     */
    virtual kiwi::EDebugMenuResult Calculate() {
        return mStateMachine.Calculate();
    }

    /**
     * @brief User-level render pass
     */
    virtual void UserDraw();

private:
    /**
     * @brief State machine state IDs
     */
    enum EState { EState_Select, EState_Decide, EState_Max };

    K_STATE_DECL_EX(kiwi::EDebugMenuResult, Select);
    K_STATE_DECL_EX(kiwi::EDebugMenuResult, Decide);

private:
    /**
     * @brief Updates the option ranges
     */
    void CalcOption();

    /**
     * @brief Sets up the global state and changes to the next scene
     */
    void SetupGame();

private:
    //! Logic state machine
    kiwi::StateMachine<SeqSelectPage, kiwi::EDebugMenuResult> mStateMachine;

    //! Selected scene ID
    s32 mNextScene;
    //! Scene exit timer
    s32 mExitTimer;

    //! Number of players
    kiwi::DebugIntOption mPlayerNum;
    //! Number of Wii Remotes
    kiwi::DebugIntOption mRemoteNum;

    //! Game mode
    kiwi::DebugEnumOption mGameMode;
    //! Game stage
    kiwi::DebugEnumOption mStageNo;
};

} // namespace DebugRoot
} // namespace AP

#endif
