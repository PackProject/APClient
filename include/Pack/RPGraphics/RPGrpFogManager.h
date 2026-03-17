#ifndef RP_GRAPHICS_FOG_MANAGER_H
#define RP_GRAPHICS_FOG_MANAGER_H
#include <Pack/types_pack.h>

#include <egg/gfxe.h>

/**
 * @brief RP engine fog manager
 * @wfuname
 */
class RPGrpFogManager : public EGG::FogManager {
public:
    RPGrpFogManager() {}
    // @address 801b2424
    virtual ~RPGrpFogManager() {}
};

#endif
