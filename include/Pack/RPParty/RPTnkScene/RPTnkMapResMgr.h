#ifndef RP_PARTY_TNK_MAP_RES_MGR_H
#define RP_PARTY_TNK_MAP_RES_MGR_H
#include <Pack/RPTypes.h>

struct RPTnkMapData {
    u32 width;     // at 0x0
    u32 height;    // at 0x4
    u32 balloonP1; // at 0x8
    u32 balloonP2; // at 0xC
    u32 tiles[1];  // at 0x10...
};

class RPTnkMapResMgr {
    RP_SINGLETON_DECL(RPTnkMapResMgr);

public:
    static const int MAX_MAP = 30;

    enum EGameMode {
        EGameMode_1P,
        EGameMode_VS,

        EGameMode_Max,
    };

private:
    enum EBalloonPos {};
};

#endif
