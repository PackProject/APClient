#ifndef RP_PARTY_BIL_POCKET_CAM_MANAGER_H
#define RP_PARTY_BIL_POCKET_CAM_MANAGER_H
#include <Pack/RPParty/RPPartyUtlModel.h>
#include <Pack/RPTypes.h>

class RPBilPocketCamManager {
    RP_SINGLETON_DECL(RPBilPocketCamManager);

public:
    void HurryUp();
    void StartCamera(s32 pocketIndex);
};

#endif
