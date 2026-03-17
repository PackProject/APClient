#ifndef RP_PARTY_TNK_GAME_OBJ_BASE_H
#define RP_PARTY_TNK_GAME_OBJ_BASE_H
#include <Pack/types_pack.h>

#include <Pack/RPAudio.h>
#include <Pack/RPUtility.h>

#include <egg/math.h>

/**
 * @brief Basic tanks game actor
 */
class RPTnkGameObjBase : public RPUtlGameObjBase {
public:
    /**
     * @brief Block collision flags
     */
    enum EBlockColFlag {
        //! Ignore blocks with no height
        COLLIDE_NO_FLAT = (1 << 0),

        //! Ignore block faces obscured by neighboring blocks
        COLLIDE_NO_OBSCURE = (1 << 1),
    };

public:
    RPTnkGameObjBase();
    virtual ~RPTnkGameObjBase(); // at 0x8

    virtual void Configure();    // at 0xC
    virtual void LoadResource(); // at 0x10
    virtual void Reset();        // at 0x14
    virtual void Calculate();    // at 0x18

    virtual void InitParam(); // at 0x58

    virtual void ResetDelta(); // at 0x5C
    virtual void ApplyDelta(); // at 0x60

    virtual void SetParam();              // at 0x64
    virtual void SetUserParam(u32 value); // at 0x68

    virtual void CalcMove();   // at 0x6C
    virtual void FirstCalc();  // at 0x70
    virtual void SecondCalc(); // at 0x74
    virtual void ThirdCalc();  // at 0x78

    virtual void Init(const EGG::Vector3f& rPosition, u32 param); // at 0x7C
    virtual void Destroy();                                       // at 0x80

    virtual bool CheckSphere(const RPTnkGameObjBase* pOther,
                             f32* pHitDist) const; // at 0x84
    virtual bool CheckSphereMine(const RPTnkGameObjBase* pOther,
                                 f32* pHitDist) const; // at 0x88

    virtual void CalcBounding(); // at 0x8C
    virtual void VF_90();        // at 0x90
    virtual bool CollideBounding(const RPTnkGameObjBase* pOther,
                                 u32 flags) const; // at 0x94

    virtual u32 GetID() const;     // at 0x98
    virtual u32 GetType() const;   // at 0x9C
    virtual u32 GetHeight() const; // at 0xA0

    virtual void SetMinePos(const EGG::Vector3f& rPosition); // at 0xA4
    virtual bool
    IsExplodeBlock(const RPTnkGameObjBase* pOther) const;            // at 0xA8
    virtual bool IsObjTrigger(const RPTnkGameObjBase* pOther) const; // at 0xAC
    virtual void StopEffect();                                       // at 0xB0
    virtual void StartExplodeEffect();                               // at 0xB4
    virtual bool IsExplode() const;                                  // at 0xB8

    virtual void SetOwner(RPTnkGameObjBase* pOwner); // at 0xBC
    virtual RPTnkGameObjBase* GetOwner() const;      // at 0xC0

    const EGG::Vector3f& GetVelocity() const {
        return mVelocity;
    }

    bool IsAlive() const {
        return mLifeTime >= 0;
    }
    bool IsDead() const {
        return mLifeTime < 0;
    }

    s32 GetLifeTime() const {
        return mLifeTime;
    }
    void SetLifeTime(s32 lifeTime) {
        mLifeTime = lifeTime;
    }

private:
    EGG::Vector3f mVelocity;     // at 0x48
    EGG::Vector3f g_reject_vel;  // at 0x54
    EGG::Vector3f g_reject_vel2; // at 0x60
    EGG::Vector3f g_reject_vel3; // at 0x6C
    EGG::Vector3f _78;           // at 0x78

    EGG::Vector3f mHitOffset;   // at 0x84
    f32 mHitRadius;             // at 0x90
    EGG::Vector3f mHitOffsetSP; // at 0x94

    s32 mLifeTime; // at 0xA0
    char _A4[0xAC - 0xA4];

    RPSndObject* mpSndObject; // at 0xAC
};

DECOMP_SIZE_ASSERT(RPTnkGameObjBase, 0xB0);

#endif
