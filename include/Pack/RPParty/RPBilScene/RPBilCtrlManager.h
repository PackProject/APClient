#ifndef RP_PARTY_BIL_CTRL_MANAGER_H
#define RP_PARTY_BIL_CTRL_MANAGER_H
#include <Pack/types_pack.h>

#include <Pack/RPSingleton.h>

struct RPBilCtrl {
    void TurnX(f32 amount);
    void TurnY(f32 amount);

    bool CanCtrl() const {
        return BOOL_0x1FC == false;
    }

    char _00[0x1FC];
    bool BOOL_0x1FC;
};

class RPBilCtrlManager {
    RP_SINGLETON_DECL(RPBilCtrlManager);

public:
    RPBilCtrl* GetCtrl() const {
        return PTR_0x4;
    }

private:
    RPBilCtrl* PTR_0x4;
};

#endif
