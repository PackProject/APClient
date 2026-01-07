#ifndef RP_GRAPHICS_MODEL_MATERIAL_H
#define RP_GRAPHICS_MODEL_MATERIAL_H
#include "RPTypes.h"
#include <nw4r/g3d.h>

class RPGrpModelMaterial {
private:
#if defined(PACK_SPORTS) || defined(PACK_PLAY)
    u32 mSyncFlags; // at 0x0
    char _04[0x20 - 0x4];
    GXColor mTevKColors[GX_MAX_KCOLOR];                // at 0x20
    GXColorS10 mTevColors[GX_MAX_TEVREG - GX_TEVREG0]; // at 0x30
#elif defined(PACK_RESORT)
    u32 mSyncFlags; // at 0x0
    char _04[0xC - 0x4];
    GXColor mTevKColors[GX_MAX_KCOLOR];                // at 0xC
    GXColorS10 mTevColors[GX_MAX_TEVREG - GX_TEVREG0]; // at 0x1C
    char _34[0x80 - 0x34];
    nw4r::g3d::ScnMdl::CopiedMatAccess mCopiedMatAccess; // at 0x80
// . . .
#endif

public:
    enum ESyncFlag {
        ESyncFlag_Tev = 1 << 4,
    };

public:
    RPGrpModelMaterial();
    virtual ~RPGrpModelMaterial();

    void SetSyncFlag(u32 flags) {
        mSyncFlags |= flags;
    }

    void SetTevKColor(GXTevKColorID id, GXColor color) {
        mTevKColors[id] = color;
    }
    void SetTevColor(GXTevRegID id, GXColorS10 color) {
        mTevColors[id - GX_TEVREG0] = color;
    }

#if defined(PACK_RESORT)
    nw4r::g3d::ScnMdl::CopiedMatAccess& GetCopiedMatAccess() {
        return mCopiedMatAccess;
    }
#endif
};

#endif
