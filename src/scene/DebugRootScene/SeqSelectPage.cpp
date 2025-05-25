#include "scene/DebugRootScene/SeqSelectPage.h"

#include "scene/DebugRootScene/SceneSelectPage.h"

#include <Sports2/Sp2Cmn.h>
#include <Sports2/Sp2Snd.h>

#include <libkiwi.h>

namespace AP {
namespace DebugRoot {
namespace {

// Sequence list
#define ALL_SEQ()                                                              \
    X(Swf, Y(Swf_Vs) Y(Swf_Prc) Y(Swf_Sgl))                                    \
    X(Jsk, Y(Jsk_Rng) Y(Jsk_Vs))                                               \
    X(Arc, Y(Arc))                                                             \
    X(Fld, Y(Fld))                                                             \
    X(Bsk, Y(Bsk_3pt) Y(Bsk_Vs))                                               \
    X(Bwl, Y(Bwl_Std) Y(Bwl_100) Y(Bwl_Wal))                                   \
    X(Can, Y(Can) Y(Can_Vs))                                                   \
    X(Png, Y(Png) Y(Png_Ret))                                                  \
    X(Wkb, Y(Wkb))                                                             \
    X(Pln, Y(Pln) Y(Pln_Vs))                                                   \
    X(Glf, Y(Glf))                                                             \
    X(Dgl, Y(Dgl))                                                             \
    X(Bic, Y(Bic) Y(Bic_Vs))                                                   \
    X(Omk, Y(Omk))

// Generate arrays of keys
#define X(S, Q) const char* GameMode_Keys_##S[] = {Q};
#define Y(Z) #Z,
ALL_SEQ();

#undef X
#undef Y

// Generate arrays of values
#define X(S, Q) u32 GameMode_Values_##S[] = {Q};
#define Y(Z) Sp2::Cmn::ESeq_##Z,
ALL_SEQ();

#undef X
#undef Y

} // namespace

/**
 * @brief Constructor
 *
 * @param rMenu Parent menu
 */
SeqSelectPage::SeqSelectPage(kiwi::DebugMenu& rMenu)
    : kiwi::DebugPage(rMenu),
      mStateMachine(this, EState_Max, EState_Select),
      mNextScene(-1),
      mExitTimer(0),
      mPlayerNum(rMenu, "PlayerNum", 1, kiwi::EPlayer_Max),
      mRemoteNum(rMenu, "RemoteNum", 1, kiwi::EPlayer_Max),
      mGameMode(rMenu, "GameMode", GameMode_Keys_Swf, 0,
                LENGTHOF(GameMode_Keys_Swf)),
      mStageNo(rMenu, "StageNo", 0, 0) {

    mStateMachine.RegistState(EState_Select, &State_Select_calc);
    mStateMachine.RegistState(EState_Decide, &State_Decide_calc);

    mOptions.PushBack(&mPlayerNum);
    mOptions.PushBack(&mRemoteNum);
    mOptions.PushBack(&mGameMode);
    mOptions.PushBack(&mStageNo);
}

/**
 * @brief User-level render pass
 */
void SeqSelectPage::UserDraw() {
    DebugPage::UserDraw();

    K_ASSERT(mNextScene >= 0);

    const char* pSceneName =
        kiwi::SceneCreator::GetInstance().GetSceneName(mNextScene);

    K_ASSERT_PTR(pSceneName);

    kiwi::Text(pSceneName)
        .SetTextColor(kiwi::Color::CYAN)
        .SetStrokeColor(kiwi::Color::BLUE)
        .SetStrokeType(kiwi::ETextStroke_Outline)
        .SetPosition(0.15, 0.1)
        .SetScale(1.2);
}

/**
 * @brief Sets the next scene ID
 *
 * @param scene Scene ID
 */
void SeqSelectPage::SetNextScene(s32 scene) {
    ASSERT(scene >= 0);
    mNextScene = scene;

    mGameMode.SetEnabled(true);
    mStageNo.SetEnabled(true);

    switch (mNextScene) {
    case kiwi::ESceneID_Sp2TitleScene:
    case kiwi::ESceneID_Sp2MiiSelectScene: {
        mGameMode.SetEnabled(false);
        mStageNo.SetEnabled(false);
        break;
    }
    }

#define X(S, Q) Y(S)
#define Y(S)                                                                   \
    case kiwi::ESceneID_Sp2##S##Scene: {                                       \
        mGameMode.SetEnumValues(GameMode_Keys_##S);                            \
        mGameMode.SetRange(0, LENGTHOF(GameMode_Keys_##S) - 1);                \
        break;                                                                 \
    }

    switch (mNextScene) { ALL_SEQ(); }
#undef X
#undef Y
}

/**
 * @brief Scene select ('Select' state)
 * @return Result of actions
 */
kiwi::EDebugMenuResult SeqSelectPage::State_Select_calc() {
    for (int i = 0; i < kiwi::EPlayer_Max; i++) {
        const kiwi::WiiCtrl& rCtrl = kiwi::CtrlMgr::GetInstance().GetWiiCtrl(i);

        if (!rCtrl.IsConnected()) {
            continue;
        }

        // Press A at any point to commit settings
        if (rCtrl.IsTrig(kiwi::EButton_A)) {
            mStateMachine.ChangeState(EState_Decide);
            break;
        }
    }

    return DebugPage::Calculate();
}

/**
 * @brief Apply chosen settings ('Decide' state)
 * @return Result of actions
 */
kiwi::EDebugMenuResult SeqSelectPage::State_Decide_calc() {
    K_ASSERT(mNextScene >= 0);

    if (mStateMachine.IsFirstStep()) {
        Sp2::Snd::startSe(SE_CMN_DECIDE_01);
    }

    // Let sound effects finish before exiting
    if (++mExitTimer >= 30) {
        SetupGame();
    }

    return kiwi::EDebugMenuResult_None;
}

/**
 * @brief Sets up the global state and changes to the next scene
 */
void SeqSelectPage::SetupGame() {
    u32 group = kiwi::SceneCreator::GetInstance().GetSceneGroup(mNextScene);
    u32 seq = 0;

#define X(S, Q) Y(S)
#define Y(S)                                                                   \
    case kiwi::ESceneID_Sp2##S##Scene: {                                       \
        seq = GameMode_Values_##S[mGameMode.GetValue()];                       \
        break;                                                                 \
    }
    switch (mNextScene) { ALL_SEQ(); }
#undef X
#undef Y

    RP_GET_INSTANCE(Sp2::Cmn::GameMgr)->writeDebugPlayerData();
    RP_GET_INSTANCE(Sp2::Cmn::GameMgr)->setPlayerNum(mPlayerNum.GetValue());
    RP_GET_INSTANCE(Sp2::Cmn::GameMgr)->setControllerNum(mRemoteNum.GetValue());

    RP_GET_INSTANCE(Sp2::Cmn::StaticMem)->setSceneGroup(group);
    RP_GET_INSTANCE(Sp2::Cmn::StaticMem)->setSceneSeq(seq);

    kiwi::SceneCreator::GetInstance().ChangeSceneAfterFade(mNextScene);
}

} // namespace DebugRoot
} // namespace AP
