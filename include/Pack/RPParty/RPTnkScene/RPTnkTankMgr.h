#ifndef RP_PARTY_TNK_TANK_MGR_H
#define RP_PARTY_TNK_TANK_MGR_H
#include <Pack/RPParty/RPTnkScene/RPTnkGameObjMgrBase.h>
#include <Pack/RPParty/RPTnkScene/RPTnkTank.h>
#include <Pack/RPTypes.h>

/**
 * @brief Tanks tank object manager
 */
class RPTnkTankMgr : public RPTnkGameObjMgrBase {
    RP_SINGLETON_DECL(RPTnkTankMgr);

public:
    virtual RPTnkTank* Create(); // at 0x24
    virtual void Finalize();     // at 0x2C

private:
    char _18[0x3C - 0x18];
};

#if defined(__KOKESHI__)
DECL_WEAK inline RPTnkTankMgr::RPTnkTankMgr() {}
#endif

#endif
