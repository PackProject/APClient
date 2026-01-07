#ifndef RP_KERNEL_EFFECT_MGR_H
#define RP_KERNEL_EFFECT_MGR_H
#include <Pack/RPTypes.h>

class RPSysEffectMgr {
    RP_SINGLETON_DECL_EX(RPSysEffectMgr);

public:
    enum EDrawScene {
        EDrawScene_Layer0,
        EDrawScene_Layer1,
        EDrawScene_Layer2,
        EDrawScene_Layer3,

        EDrawScene_Cursor = 15,

        EDrawScene_Max = 64,
    };

    enum EEffectOwner {
        EEffectOwner_Scene,
        EEffectOwner_CursorMgr,
        EEffectOwner_Work,

        EEffectOwner_Max
    };

public:
    void LoadResource();
};

#endif
