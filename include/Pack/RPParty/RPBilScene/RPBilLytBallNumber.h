#ifndef RP_PARTY_BIL_LYT_BALL_NUMBER_H
#define RP_PARTY_BIL_LYT_BALL_NUMBER_H
#include <Pack/RPGraphics.h>
#include <Pack/RPTypes.h>
#include <Pack/RPUtility/RPUtlBaseFsm.h>
#include <Pack/RPUtility/RPUtlLytBase.h>

#include <egg/core.h>

#include <nw4r/lyt.h>

// Forward declarations
class RPSysLayout;
class RPSysLytAnmObj;

class RPBilLytBallNumber : public RPUtlLytBase, public IRPGrpDrawObject {
    RP_SINGLETON_DECL(RPBilLytBallNumber);

public:
    enum EState {
        EState_Hide,
        EState_AnimIn,
        EState_Wait,
        EState_AnimOut,

        EState_Max
    };

    virtual void LoadResource(EGG::Archive* pArchive);
    virtual void Reset();
    virtual void Calculate();

    virtual void UserDraw();

    bool IsState(EState state) const {
        return mStateMachine->IsState(state);
    }
    void ChangeState(EState state) {
        mStateMachine->ChangeState(state);
    }

private:
    enum EAnmObj {
        EAnmObj_In,
        EAnmObj_Out,
        EAnmObj_Number1,
        EAnmObj_Number2,
        EAnmObj_Number3,
        EAnmObj_Number4,
        EAnmObj_Number5,
        EAnmObj_Number6,
        EAnmObj_Number7,
        EAnmObj_Number8,
        EAnmObj_Number9,

        EAnmObj_Max
    };

private:
    RP_UTL_FSM_STATE_DECL(HIDE);
    RP_UTL_FSM_STATE_DECL(ANIMIN);
    RP_UTL_FSM_STATE_DECL(WAIT);
    RP_UTL_FSM_STATE_DECL(ANIMOUT);

private:
    RPUtlBaseFsm<RPBilLytBallNumber>* mStateMachine; // at 0x10
    bool mDoAnimIn;                                  // at 0x14
    bool _15;
    bool _16;
    s32 mBallNo;                            // at 0x18
    s32 _1C;                                // at 0x1C
    RPSysLayout* mpLayout;                  // at 0x20
    RPSysLytAnmObj* mpAnmObjs[EAnmObj_Max]; // at 0x24
    nw4r::lyt::Pane* N_number_00;           // at 0x50
};

#if defined(__KOKESHI__)
DECL_WEAK inline RPBilLytBallNumber::RPBilLytBallNumber() {
    mStateMachine = new RPUtlBaseFsm<RPBilLytBallNumber>(this, EState_Max);

    mStateMachine->RegistState(&RPBilLytBallNumber::State_HIDE_enter,
                               &RPBilLytBallNumber::State_HIDE_calc,
                               EState_Hide);

    mStateMachine->RegistState(&RPBilLytBallNumber::State_ANIMIN_enter,
                               &RPBilLytBallNumber::State_ANIMIN_calc,
                               EState_AnimIn);

    mStateMachine->RegistState(&RPBilLytBallNumber::State_WAIT_enter,
                               &RPBilLytBallNumber::State_WAIT_calc,
                               EState_Wait);

    mStateMachine->RegistState(&RPBilLytBallNumber::State_ANIMOUT_enter,
                               &RPBilLytBallNumber::State_ANIMOUT_calc,
                               EState_AnimOut);

    RPGrpRenderer::GetCurrent()->AppendDrawObject(this);
}
#endif

#endif
