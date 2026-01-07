#ifndef RP_PARTY_DUC_CURSOR_H
#define RP_PARTY_DUC_CURSOR_H
#include <nw4r/math.h>

#include <RPTypes.h>

// Forward declarations
class RPSysEffect;
template <int N> class TRPSndObject;

class RPDucCursor /* : some common base */ {
public:
    enum EEffectState {
        EEffectState_Hide,
        EEffectState_HideTail,
        EEffectState_Show,
    };

public:
    RPDucCursor();
    virtual ~RPDucCursor(); // at 0x8

    virtual void Configure();    // at 0xC
    virtual void LoadResource(); // at 0x10
    virtual void Reset();        // at 0x14
    virtual void Calculate();    // at 0x18

    virtual void VF_1C();                            // at 0x1C
    virtual void VF_20();                            // at 0x20
    virtual void CreateMainEffect();                 // at 0x24
    virtual void CreateTailEffect();                 // at 0x28
    virtual void SetEffectState(EEffectState state); // at 0x2C
    virtual void CalcEffectPos();                    // at 0x30
    virtual void VF_34();                            // at 0x34

private:
    nw4r::math::VEC3 mPosition; // at 0x4
    char _10[0x84 - 0x10];
    s32 mChannel;                 // at 0x84
    s32 mState;                   // at 0x88
    RPSysEffect* mpMainEff;       // at 0x8C
    RPSysEffect* mpMainEffMulti;  // at 0x90
    RPSysEffect* mpTailEff;       // at 0x94
    RPSysEffect* mpTailEffMulti;  // at 0x98
    TRPSndObject<4>* mpSndObject; // at 0x9C
};

#endif
