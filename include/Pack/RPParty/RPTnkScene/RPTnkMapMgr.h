#ifndef RP_PARTY_TNK_MAP_MGR_H
#define RP_PARTY_TNK_MAP_MGR_H
#include <Pack/RPTypes.h>

// Forward declarations
class RPTnkMapResMgr;

class RPTnkMapMgr {
    RP_SINGLETON_DECL(RPTnkMapMgr);

private:
    RPTnkMapResMgr* mpResMgr; // at 0x4
};

#endif
