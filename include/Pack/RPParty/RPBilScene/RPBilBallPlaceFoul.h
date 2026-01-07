#ifndef RP_PARTY_BIL_BALL_PLACE_FOUL_H
#define RP_PARTY_BIL_BALL_PLACE_FOUL_H
#include <Pack/RPParty/RPPartyUtlModel.h>
#include <Pack/RPTypes.h>
#include <Pack/RPUtility/RPUtlBaseFsm.h>

class RPBilBallPlaceFoul : public RPPartyUtlModel {
public:
    virtual void Configure(); // at 0x78
    virtual void Reset();     // at 0x7C
    virtual void Calculate(); // at 0x80
    virtual void Exit();      // at 0x84
    virtual void UserDraw();  // at 0x88

private:
    u32 mId; // at 0x60
};

#endif
