#ifndef RP_KERNEL_HOME_MENU_MGR_H
#define RP_KERNEL_HOME_MENU_MGR_H
#include <Pack/types_pack.h>

#include <Pack/RPSingleton.h>

class RPSysHomeMenuMgr {
    RP_SINGLETON_DECL(RPSysHomeMenuMgr);

public:
    void LoadResource();
};

#endif
