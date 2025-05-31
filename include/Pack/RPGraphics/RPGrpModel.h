#ifndef RP_GRAPHICS_MODEL_H
#define RP_GRAPHICS_MODEL_H
#include "RPTypes.h"

#include <egg/gfx/eggModelEx.h>

class RPGrpModelMaterial;

class RPGrpModel {
public:
    EGG::ModelEx* GetModelEx() const {
        return mModelEx;
    }

    RPGrpModelMaterial* GetMaterial(u32 id) const {
        return mppMaterials[id];
    }

private:
#if defined(PACK_RESORT)
    char _00[0x38];
    RPGrpModelMaterial** mppMaterials; // at 0x38
    char _3C[0x44 - 0x3C];
    EGG::ModelEx* mModelEx; // at 0x44
#else
    char _00[0x40];
    EGG::ModelEx* mModelEx; // at 0x40
#endif
};

#endif
