#ifndef RP_GRAPHICS_MODEL_MATERIAL_H
#define RP_GRAPHICS_MODEL_MATERIAL_H
#include "RPTypes.h"

#include <nw4r/g3d.h>

class RPGrpModelMaterial {
public:
    void SetTevKColor(GXTevKColorID id, GXColor color) {
        mTevKColors[id] = color;
    }
    void SetTevColor(GXTevRegID id, GXColorS10 color) {
        mTevColors[id - GX_TEVREG0] = color;
    }

    nw4r::g3d::ScnMdl::CopiedMatAccess& GetCopiedMatAccess() {
        return mCopiedMatAccess;
    }

private:
    char _00[0xC];
    GXColor mTevKColors[GX_MAX_KCOLOR];                // at 0xC
    GXColorS10 mTevColors[GX_MAX_TEVREG - GX_TEVREG0]; // at 0x1C
    char _34[0x80 - 0x34];
    nw4r::g3d::ScnMdl::CopiedMatAccess mCopiedMatAccess; // at 0x80
    // . . .
};

#endif
