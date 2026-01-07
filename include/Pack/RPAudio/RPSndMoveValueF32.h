#ifndef RP_AUDIO_SND_MOVE_VALUE_F32_H
#define RP_AUDIO_SND_MOVE_VALUE_F32_H
#include <Pack/RPTypes.h>

//! @addtogroup rp_audio
//! @{

class RPSndMoveValueF32 {
public:
    RPSndMoveValueF32();

    virtual bool update(); // at 0x8

private:
    char _04[0x1C - 0x4];
};

//! @}

#endif
