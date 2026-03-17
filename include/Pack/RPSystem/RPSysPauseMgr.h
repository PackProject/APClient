#ifndef RP_SYSTEM_PAUSE_MGR_H
#define RP_SYSTEM_PAUSE_MGR_H
#include <Pack/types_pack.h>

#include <Pack/RPSingleton.h>

class RPSysPauseMgr {
    RP_SINGLETON_DECL(RPSysPauseMgr);

public:
    bool isPause() const {
        return mFlags & 1;
    }

    void LoadResource();

private:
    u32 mFlags; // at 0x0
};

#endif
