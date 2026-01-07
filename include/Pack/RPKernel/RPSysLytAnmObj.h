#ifndef RP_KERNEL_LYT_ANM_OBJ_H
#define RP_KERNEL_LYT_ANM_OBJ_H
#include "RPSysFrameCtrl.h"
#include "RPTypes.h"

class RPSysLytAnmObj {
public:
    RPSysFrameCtrl* getFrameCtrl() {
        return &mFrameCtrl;
    }

    void play() {
        mFrameCtrl.play();
    }

private:
    u32 _00;
    RPSysFrameCtrl mFrameCtrl; // at 0x4
    u16 _18;
    u32 _1C;
};

#endif
