#include "scene/DebugRootScene/SeqSelectPage.h"

#include "scene/DebugRootScene/SceneSelectPage.h"

#include <Sports2/Sp2Cmn.h>
#include <Sports2/Sp2Snd.h>

#include <libkiwi.h>

namespace AP {
namespace DebugRoot {
namespace {
// clang-format off

// List of all scenes/sequences/stages
#define USE_GAME_DATA()                                                                \
    X(Swf,                                                                             \
        Y(Swf_Vs,  Z(Main))                                                            \
        Y(Swf_Prc, Z(Main))                                                            \
        Y(Swf_Sgl, Z(Bridge)  Z(Lighthouse)  Z(Beach)   Z(Mountain)  Z(Forest)         \
                   Z(Ruins)   Z(Waterfall)   Z(Cliffs)  Z(Castle)    Z(Volcano)        \
                   Z(BridgeR) Z(LighthouseR) Z(BeachR)  Z(MountainR) Z(ForestR)        \
                   Z(RuinsR)  Z(WaterfallR)  Z(CliffsR) Z(CastleR)   Z(VolcanoR)))     \
    X(Jsk,                                                                             \
        Y(Jsk_Rng, Z(Beach) Z(Lagoon) Z(Lighthouse) Z(Marina) Z(Cavern) Z(Shoals))     \
        Y(Jsk_Vs,  Z(Beach) Z(Lagoon) Z(Lighthouse) Z(Marina) Z(Cavern) Z(Shoals)))    \
    X(Arc,                                                                             \
        Y(Arc, Z(Beginner) Z(Intermediate) Z(Expert)))                                 \
    X(Fld,                                                                             \
        Y(Fld, Z(Main)))                                                               \
    X(Bsk,                                                                             \
        Y(Bsk_3pt, Z(Main))                                                            \
        Y(Bsk_Vs,  Z(Main)))                                                           \
    X(Bwl,                                                                             \
        Y(Bwl_Std, Z(Main))                                                            \
        Y(Bwl_100, Z(Main))                                                            \
        Y(Bwl_Wal, Z(Main)))                                                           \
    X(Can,                                                                             \
        Y(Can,    Z(Beginner) Z(Intermediate) Z(Expert))                               \
        Y(Can_Vs, Z(Main)))                                                            \
    X(Png,                                                                             \
        Y(Png,     Z(Main))                                                            \
        Y(Png_Ret, Z(Main)))                                                           \
    X(Wkb,                                                                             \
        Y(Wkb, Z(Beginner) Z(Intermediate) Z(Expert)))                                 \
    X(Pln,                                                                             \
        Y(Pln,    Z(Daytime) Z(Evening) Z(Night))                                      \
        Y(Pln_Vs, Z(Main)))                                                            \
    X(Glf,                                                                             \
        Y(Glf, Z(ResortA)  Z(ResortB)  Z(ResortC)  Z(ClassicA) Z(ClassicB) Z(ClassicC) \
               Z(Special)  Z(Resort9)  Z(Classic9) Z(Eighteen)))                       \
    X(Dgl,                                                                             \
        Y(Dgl, Z(ResortA)  Z(ResortB)  Z(ResortC)  Z(ClassicA) Z(ClassicB) Z(ClassicC) \
               Z(Special)  Z(Resort9)  Z(Classic9) Z(Eighteen)))                       \
    X(Bic,                                                                             \
        Y(Bic,    Z(S01) Z(S02) Z(S03) Z(S04) Z(S05) Z(S06) Z(ThreeStage) Z(SixStage)) \
        Y(Bic_Vs, Z(S01) Z(S02) Z(S03) Z(S04) Z(S05) Z(S06)))                          \
    X(Omk,                                                                             \
        Y(Omk, Z(Main)))

// Generate gamemode keys
#define X(S, QT) namespace S { const char* GAMEMODE_KEYS[] = { QT }; }
#define Y(Q, T) #Q,
USE_GAME_DATA();
#undef X
#undef Y

// Generate gamemode values
#define X(S, QT) namespace S { const Sp2::Cmn::ESeq GAMEMODE_VALUES[] = { QT }; }
#define Y(Q, T) Sp2::Cmn::ESeq_##Q,
USE_GAME_DATA();
#undef X
#undef Y

// Generate stage keys
#define X(S, QT) QT
#define Y(Q, T) namespace Q { const char* STAGENO_KEYS[] = { T }; }
#define Z(T) #T,
USE_GAME_DATA();
#undef X
#undef Y
#undef Z

// Generate stage values
#define X(S, QT) QT
#define Y(Q, T) namespace Q { enum STAGENO_ENUM { T }; const u32 STAGENO_VALUES[] = { T }; }
#define Z(T) T,
USE_GAME_DATA();
#undef X
#undef Y
#undef Z

// clang-format on
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
      mGameMode(rMenu, "GameMode", Swf::GAMEMODE_KEYS, 0,
                LENGTHOF(Swf::GAMEMODE_KEYS)),
      mStageNo(rMenu, "StageNo", Swf_Vs::STAGENO_KEYS, 0,
               LENGTHOF(Swf_Vs::STAGENO_KEYS)) {

    mStateMachine.RegistState(EState_Select, &SeqSelectPage::State_Select_calc);
    mStateMachine.RegistState(EState_Decide, &SeqSelectPage::State_Decide_calc);

    mOptions.PushBack(&mPlayerNum);
    mOptions.PushBack(&mRemoteNum);
    mOptions.PushBack(&mGameMode);
    mOptions.PushBack(&mStageNo);
}

/**
 * @brief Sets the next scene ID
 *
 * @param scene Scene ID
 */
void SeqSelectPage::SetNextScene(s32 scene) {
    ASSERT(scene >= 0);
    mNextScene = scene;

    CalcOption();
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
 * @brief Scene select ('Select' state)
 * @return Result of actions
 */
kiwi::EDebugMenuResult SeqSelectPage::State_Select_calc() {
    ASSERT(mNextScene >= 0);

    CalcOption();

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
 * @brief Updates the option ranges
 */
void SeqSelectPage::CalcOption() {
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

    // Setup GameMode option by the selected scene
#define X(S, QT)                                                               \
    case kiwi::ESceneID_Sp2##S##Scene: {                                       \
        mGameMode.SetEnumValues(S::GAMEMODE_KEYS);                             \
        mGameMode.SetRange(0, LENGTHOF(S::GAMEMODE_KEYS) - 1);                 \
        mGameMode.SetEnabled(LENGTHOF(S::GAMEMODE_KEYS) > 1);                  \
        break;                                                                 \
    }

    switch (mNextScene) { USE_GAME_DATA(); }
#undef X

    // Setup StageNo option by the selected sequence
#define X(S, QT)                                                               \
    case kiwi::ESceneID_Sp2##S##Scene: {                                       \
        switch (S::GAMEMODE_VALUES[mGameMode.GetValue()]) { QT }               \
        break;                                                                 \
    }

#define Y(Q, T)                                                                \
    case Sp2::Cmn::ESeq_##Q: {                                                 \
        mStageNo.SetEnumValues(Q::STAGENO_KEYS);                               \
        mStageNo.SetRange(0, LENGTHOF(Q::STAGENO_KEYS) - 1);                   \
        mStageNo.SetEnabled(LENGTHOF(Q::STAGENO_KEYS) > 1);                    \
        break;                                                                 \
    }

    switch (mNextScene) { USE_GAME_DATA(); }
#undef X
#undef Y
}

/**
 * @brief Sets up the global state and changes to the next scene
 */
void SeqSelectPage::SetupGame() {
    u32 group = kiwi::SceneCreator::GetInstance().GetSceneGroup(mNextScene);
    u32 seq = 0;
    u32 stage = 0;

    // Get sequence value from the GameMode option
#define X(S, QT) Y(S)
#define Y(S)                                                                   \
    case kiwi::ESceneID_Sp2##S##Scene: {                                       \
        seq = S::GAMEMODE_VALUES[mGameMode.GetValue()];                        \
        break;                                                                 \
    }
    switch (mNextScene) { USE_GAME_DATA(); }
#undef X
#undef Y

    // Get stage value from the StageNo option
#define X(S, QT)                                                               \
    case kiwi::ESceneID_Sp2##S##Scene: {                                       \
        switch (S::GAMEMODE_VALUES[mGameMode.GetValue()]) { QT }               \
        break;                                                                 \
    }

#define Y(Q, T)                                                                \
    case Sp2::Cmn::ESeq_##Q: {                                                 \
        stage = Q::STAGENO_VALUES[mStageNo.GetValue()];                        \
        break;                                                                 \
    }

    switch (mNextScene) { USE_GAME_DATA(); }
#undef X
#undef Y

    RP_GET_INSTANCE(Sp2::Cmn::GameMgr)->writeDebugPlayerData();
    RP_GET_INSTANCE(Sp2::Cmn::GameMgr)->setPlayerNum(mPlayerNum.GetValue());
    RP_GET_INSTANCE(Sp2::Cmn::GameMgr)->setControllerNum(mRemoteNum.GetValue());

    RP_GET_INSTANCE(Sp2::Cmn::StaticMem)->setSceneGroup(group);
    RP_GET_INSTANCE(Sp2::Cmn::StaticMem)->setSceneSeq(seq);
    RP_GET_INSTANCE(Sp2::Cmn::StaticMem)->setStageNo(stage);

    kiwi::SceneCreator::GetInstance().ChangeSceneAfterFade(mNextScene);
}

} // namespace DebugRoot
} // namespace AP
