#ifndef RP_PARTY_BIL_BALL_MANAGER_H
#define RP_PARTY_BIL_BALL_MANAGER_H
#include <Pack/RPParty/RPPartyUtlModel.h>
#include <Pack/RPTypes.h>

// Forward declarations
class RPBilBall;
class RPBilBallGuide;
class RPBilBallPlaceFoul;
class RPBilBallDisplay;
class RPSysKokeshiIcon;
template <int N> class TRPSndObject;

class RPBilBallManager : public RPPartyUtlModel {
    RP_SINGLETON_DECL(RPBilBallManager);

public:
    virtual void Configure(); // at 0x78
    virtual void Reset();     // at 0x7C
    virtual void Calculate(); // at 0x80
    virtual void Exit();      // at 0x84

    virtual void UserDraw(); // at 0x88

private:
    enum EFoulType {
        EFoulType_None = -1,
        EFoulType_OffTable,
        EFoulType_CuePocket,
        EFoulType_MissTarget,
        EFoulType_WrongBall,
    };

    static const int PLAYER_MAX = 2;
    static const int BALL_MAX = 10;
    static const int GUIDE_BALL_MAX = 10;

private:
    void CalcBallCollision();
    void CalcTableCollision();

private:
    u32 mLayoutNo;                                // at 0x60
    s32 mBallNum;                                 // at 0x64
    s32 mTurnNo;                                  // at 0x68
    u32 mFirstHitBall;                            // at 0x6C
    EFoulType mFoulType;                          // at 0x70
    bool mStartedFoulSE;                          // at 0x74
    s32 mTurnEndTimer;                            // at 0x78
    RPBilBall* mpBalls[BALL_MAX];                 // at 0x7C
    RPBilBallGuide* mpGuideBalls[GUIDE_BALL_MAX]; // at 0xA4
    RPBilBallPlaceFoul* mpPlaceFoulBall;          // at 0xCC
    RPBilBallDisplay* mpDisplayBalls[BALL_MAX];   // at 0xD0
    RPSysKokeshiIcon* mpKokeshiIcons[PLAYER_MAX]; // at 0xF8
    TRPSndObject<4>* mpSndObject;                 // at 0x100
};

#endif
