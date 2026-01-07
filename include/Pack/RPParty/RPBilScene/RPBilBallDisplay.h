#ifndef RP_PARTY_BIL_BALL_DISPLAY_H
#define RP_PARTY_BIL_BALL_DISPLAY_H
#include <Pack/RPParty/RPPartyUtlModel.h>
#include <Pack/RPTypes.h>
#include <Pack/RPUtility/RPUtlBaseFsm.h>

class RPBilBallDisplay : public RPPartyUtlModel {
public:
    enum EState { EState_Hide, EState_AnimIn, EState_Wait, EState_AnimOut };

    RPBilBallDisplay(u32 index);
    virtual ~RPBilBallDisplay();

    virtual void Configure(); // at 0x78
    virtual void Reset();     // at 0x7C
    virtual void Calculate(); // at 0x80
    virtual void Exit();      // at 0x84

    bool IsState(EState state) const {
        return mStateMachine->IsState(state);
    }

    void ChangeState(EState state) {
        mStateMachine->ChangeState(state);
    }

    void StartAnimOut();
    void CalcDisplay(u32 player, f32 offsetY, u32 pocketNum, u32 displayNo);

private:
    u32 mIndex; // at 0x60
    char _64[0x84 - 0x64];
    RPUtlBaseFsm<RPBilBallDisplay>* mStateMachine; // at 0x84
};

#endif
