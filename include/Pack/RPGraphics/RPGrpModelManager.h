#ifndef RP_GRAPHICS_MODEL_MANAGER_H
#define RP_GRAPHICS_MODEL_MANAGER_H
#include <RPTypes.h>

// Forward declarations
class RPGrpLightManager;
class RPGrpFogManager;

class RPGrpModelManager {
public:
    void CreateModelScene(u32 index, u8 drawPathFlag, u32 viewNum,
                          RPGrpLightManager* pLightMgr,
                          RPGrpFogManager* pFogMgr);

    static RPGrpModelManager* GetCurrent() {
        return spCurrent;
    }

private:
    static RPGrpModelManager* spCurrent;
};

#endif
