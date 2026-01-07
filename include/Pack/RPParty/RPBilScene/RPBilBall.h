#ifndef RP_PARTY_BIL_BALL_H
#define RP_PARTY_BIL_BALL_H
#include <Pack/RPParty/RPPartyUtlModel.h>
#include <Pack/RPParty/RPPartyUtlModelRigid.h>
#include <Pack/RPTypes.h>
#include <Pack/RPUtility/RPUtlBaseFsm.h>

// Forward declarations
class RPSysEffect;

class RPBilBall : public RPPartyUtlModel {
public:
    enum EState { EState_None, EState_Wait, EState_Pocket, EState_OffTable };

    RPBilBall(u32 no);
    virtual ~RPBilBall();

    virtual const EGG::Vector3f& getPosition() const;   // at 0x34
    virtual void setPosition(const EGG::Vector3f& pos); // at 0x38

    virtual const EGG::Vector3f& getVelocity() const;   // at 0x3C
    virtual void setVelocity(const EGG::Vector3f& vel); // at 0x40

    virtual const EGG::Vector3f& getMtxZBase() const; // at 0x4C
    virtual void setMtxZBase(const EGG::Vector3f& z); // at 0x50

    virtual const EGG::Vector3f& getMtxYBase() const; // at 0x54
    virtual void setMtxYBase(const EGG::Vector3f& y); // at 0x58

    virtual const EGG::Vector3f& getMtxXBase() const; // at 0x5C
    virtual void setMtxXBase(const EGG::Vector3f& x); // at 0x60

    virtual f32 getScale() const;     // at 0x64
    virtual void setScale(f32 scale); // at 0x68

    virtual void Configure(); // at 0x78
    virtual void Reset();     // at 0x7C
    virtual void Calculate(); // at 0x80
    virtual void Exit();      // at 0x84
    virtual void UserDraw();  // at 0x88

    void PreCalculate();
    void PostCalculate();

    void ResetRack();

    bool IsStopped() const {
        return mpRigidBody->isStopped();
    }

    bool IsChangingState() const {
        return mStateMachine->IsChangingState();
    }

    bool IsState(EState state) const {
        return mStateMachine->IsState(state);
    }
    bool IsStateNow(EState state) const {
        return mStateMachine->IsStateNow(state);
    }

    void ChangeState(EState state) {
        mStateMachine->ChangeState(state);
    }

    u32 GetIndex() const {
        return mIndex;
    }

    s32 GetTurnNoPocket() const {
        return mTurnNoPocket;
    }
    s32 GetTurnNoOffTable() const {
        return mTurnNoOffTable;
    }

    bool IsEnabled() const {
        return mIsEnabled;
    }

    void SetFloorBounceNum(s32 num) {
        mFloorBounceNum = num;
    }

    RPPartyUtlModelRigid* GetRigidBody() const {
        return mpRigidBody;
    }

    s32 GetClosePocketIndex() const;

    bool CheckRayIntersect(const EGG::Ray3f& rRay, f32 radius,
                           EGG::Vector3f& rHitPos, f32& rHitDist);

private:
    u32 mIndex;                             // at 0x60
    RPUtlBaseFsm<RPBilBall>* mStateMachine; // at 0x64
    s32 mTurnNoPocket;                      // at 0x68
    s32 mTurnNoOffTable;                    // at 0x6C
    bool mIsEnabled;                        // at 0x70
    bool _71;                               // at 0x70
    s32 mFloorBounceNum;                    // at 0x74
    UNKTYPE* mpSndObject;                   // at 0x78
    RPPartyUtlModelRigid* mpRigidBody;      // at 0x7C
    RPSysEffect* mpTailEffect;              // at 0x80
};

#endif
