#ifndef RP_PARTY_BIL_POCKET_CAM_MANAGER_H
#define RP_PARTY_BIL_POCKET_CAM_MANAGER_H
#include <Pack/types_pack.h>

#include <Pack/RPParty/RPPartyUtlModel.h>
#include <Pack/RPSingleton.h>

class RPBilPocketCamManager {
    RP_SINGLETON_DECL(RPBilPocketCamManager);

public:
    void HurryUp();
    void StartCamera(s32 pocketIndex);
};

#endif
