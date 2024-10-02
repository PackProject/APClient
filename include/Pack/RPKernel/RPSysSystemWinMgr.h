#ifndef RP_KERNEL_SYSTEM_WINDOW_MGR_H
#define RP_KERNEL_SYSTEM_WINDOW_MGR_H
#include <Pack/RPTypes.h>

// Thanks Nintendo!
#if defined(PACK_RESORT)
#define RPSysSysWinMgr RPSysSystemWinMgr
#endif

class RPSysSystemWinMgr {
    RP_SINGLETON_DECL(RPSysSystemWinMgr);

public:
    enum E_WINDOW_TYPE {
        WINDOW_TYPE_MSG,
        WINDOW_TYPE_ERR,
    };

    enum E_RESULT { RESULT_NONE, RESULT_WAIT, RESULT_YES, RESULT_NO };

public:
    void createSystemWindow();

    void setSystemWindow(E_WINDOW_TYPE type, u32 group, RPSysMessage* msg,
                         int argc, ...);

    E_RESULT getResult() {
        return (E_RESULT)mResult;
    }

#if defined(PACK_RESORT)
    void updatePauseClosed();
#endif

private:
    char UNK_0x4[0x90 - 0x4];
    s32 mResult;
    char UNK_0x94[0xE0 - 0x94];
};

#endif
