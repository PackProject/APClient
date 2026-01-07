#ifndef RP_KERNEL_FRAME_CTRL_H
#define RP_KERNEL_FRAME_CTRL_H
#include "RPTypes.h"

class RPSysFrameCtrl {
public:
    enum EPlayMode {
        PLAYMODE_ONETIME,
        PLAYMODE_INOUT,
        PLAYMODE_LOOP,
    };

    enum EPlayFlag {
        FLAG_PLAY_FINISHED = 1 << 0,
    };

    enum ETypeFlag {
        FLAG_TYPE_F32 = 1 << 0,
    };

    //! TODO
    void play() {
        mFrameNoF32 = mFrameNo;
        mPlayFlags = 0;
        mTypeFlags = FLAG_TYPE_F32;
    }

private:
    u8 mPlayMode;   // at 0x0
    u8 mPlayFlags;  // at 0x1
    u16 mTypeFlags; // at 0x2
    s16 mFrameNo;   // at 0x4
    s16 mFrameNum;  // at 0x6
    char _8[0xC - 0x8];
    f32 mRate;       // at 0xC
    f32 mFrameNoF32; // at 0x10
};

#endif
