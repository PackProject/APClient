#ifndef RP_GRAPHICS_MODEL_H
#define RP_GRAPHICS_MODEL_H
#include <Pack/RPTypes.h>
#include <egg/gfx/eggModelEx.h>
#include <nw4r/g3d.h>

class RPGrpModelMaterial;
class RPGrpModelAnm;

class RPGrpModel {
protected:
    enum FlagBit {
        FLAG_VISIBLE = (1 << 0),
    };

protected:
#if defined(PACK_RESORT)
    char _00[0x38];
    RPGrpModelMaterial** mppMaterials; // at 0x38
    char _3C[0x44 - 0x3C];
    EGG::ModelEx* mModelEx; // at 0x44
#else
    u8 mViewNo;    // at 0x0
    u8 mDrawScene; // at 0x1
    u8 mDrawGroup; // at 0x2
    char _03;
    u16 mFlags; // at 0x4
    char _06[0x2C - 0x6];
    RPGrpModelAnm* mModelAnm;          // at 0x2C
    RPGrpModelMaterial** mppMaterials; // at 0x30
    char _34[0x40 - 0x34];
    EGG::ModelEx* mModelEx; // at 0x40
#endif

public:
    static RPGrpModel* Construct(u16 rd, const char* pName, u32 drawView,
                                 u32 flags, u32 bufferOption);
    static RPGrpModel* Construct(u16 rd, u32 drawView, u32 flags,
                                 u32 bufferOption);

    void UpdateFrame();

    EGG::ModelEx* GetModelEx() const {
        return mModelEx;
    }

    nw4r::g3d::ScnMdlSimple* GetScnMdlSimple() const {
        return mModelEx->getScnMdlSimple();
    }

#if !defined(PACK_RESORT)
    RPGrpModelAnm* GetModelAnm() const {
        return mModelAnm;
    }
#endif

    RPGrpModelMaterial* GetMaterial(u32 id) const {
        return mppMaterials[id];
    }

#if !defined(PACK_RESORT)
    void SetDrawScene(u8 scene) {
        mDrawScene = scene;
    }
    void SetDrawGroup(u8 group) {
        mDrawGroup = group;
    }

    void SetVisible(bool enable) {
        SetShapeVisible(enable);
        SetJointVisible(enable);
    }
#endif

public:
    virtual UNKTYPE VF_0x8(UNKTYPE) = 0; // at 0x8
    virtual UNKTYPE VF_0xC(UNKTYPE) = 0; // at 0xC

    virtual UNKTYPE VF_0x10(UNKTYPE) = 0; // at 0x10
    virtual UNKTYPE VF_0x14(UNKTYPE) = 0; // at 0x14
    virtual UNKTYPE VF_0x18(UNKTYPE) = 0; // at 0x18
    virtual UNKTYPE VF_0x1C(UNKTYPE) = 0; // at 0x1C

    virtual UNKTYPE VF_0x20(UNKTYPE) = 0;          // at 0x20
    virtual UNKTYPE VF_0x24(UNKTYPE) = 0;          // at 0x24
    virtual UNKTYPE VF_0x28(UNKTYPE) = 0;          // at 0x28
    virtual void SetJointVisible(bool enable) = 0; // at 0x2C

    virtual UNKTYPE VF_0x30(UNKTYPE) = 0;          // at 0x30
    virtual void SetShapeVisible(bool enable) = 0; // at 0x34
};

#endif
