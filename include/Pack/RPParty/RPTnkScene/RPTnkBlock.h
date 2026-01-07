#ifndef RP_PARTY_TNK_BLOCK_H
#define RP_PARTY_TNK_BLOCK_H
#include <Pack/RPGraphics.h>
#include <Pack/RPParty/RPTnkScene/RPTnkGameObjBase.h>
#include <Pack/RPTypes.h>

#include <egg/math.h>

/**
 * @brief Tanks block object
 */
class RPTnkBlock : public RPTnkGameObjBase {
public:
    RPTnkBlock();
    virtual ~RPTnkBlock(); // at 0x8

    virtual void Configure();    // at 0xC
    virtual void LoadResource(); // at 0x10
    virtual void Calculate();    // at 0x18

    virtual void CalcModel(); // at 0x24

    virtual void SetParam();              // at 0x64
    virtual void SetUserParam(u32 value); // at 0x68

    virtual void CalcMove();   // at 0x6C
    virtual void FirstCalc();  // at 0x70
    virtual void SecondCalc(); // at 0x74

    virtual bool CollideBounding(const RPTnkGameObjBase* pOther,
                                 u32 flags) const; // at 0x94

    virtual u32 GetType() const;   // at 0x9C
    virtual u32 GetHeight() const; // at 0xA0

    void StartBreakEffect();

    static f32 GetSizeWidth() {
        return sWidth;
    }
    static f32 GetSizeHeight() {
        return sHeight;
    }

private:
    typedef void (RPTnkBlock::*StateFunc)();

    enum EState {
        EState_Main,

        EState_Max
    };

    enum EModel {
        EModel_Block1,
        EModel_Block7,
        EModel_Block8,

        EModel_Max
    };

private:
    void InitBounding();
    void CalcShadow();

private:
    u32 mType;  // at 0xB0
    u32 mState; // at 0xB4
    char _B8[0x138 - 0xB8];
    u32 mUpTileHeight;    // at 0x138
    u32 mRightTileHeight; // at 0x13C
    u32 mDownTileHeight;  // at 0x140
    u32 mLeftTileHeight;  // at 0x144
    bool mIsBreak;        // at 0x148
    u32 mHeight;          // at 0x14C
    char _150[0x158 - 0x150];
    RPGrpModel* mpBlockModels[EModel_Max]; // at 0x158
    RPGrpModel* mpBlockShadowModel;        // at 0x164
    EGG::Vector3f mShadowScale;            // at 0x168
    StateFunc mStateFunctions[EState_Max]; // at 0x174

private:
    static f32 sWidth;
    static f32 sHeight;
};

DECOMP_SIZE_ASSERT(RPTnkBlock, 0x180);

#endif
