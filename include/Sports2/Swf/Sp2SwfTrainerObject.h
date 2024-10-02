#ifndef SPORTS2_SWF_TRAINER_OBJECT_H
#define SPORTS2_SWF_TRAINER_OBJECT_H
#include <Sports2/Sp2Types.h>

namespace Sp2 {
namespace Swf {

class TrainerObject /* public Cmn::ObjectBase */ {
public:
    enum EState {
        EState_None,
        EState_Wait,
        EState_PrepareThrow,
        EState_Throw,
        EState_ThrowJump,
        EState_WaitFall,
        EState_Judge,
        EState_JudgeResult,
    };

public:
    EState getState() const {
        return mState;
    }

private:
    char _00[0x48];
    EState mState; // at 0x48
};

} // namespace Swf
} // namespace Sp2

#endif