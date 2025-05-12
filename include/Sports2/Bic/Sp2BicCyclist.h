#ifndef SPORTS2_BIC_MODEL_H
#define SPORTS2_BIC_MODEL_H
#include <Sports2/Sp2Cmn.h>
#include <Sports2/Sp2Types.h>

namespace Sp2 {
namespace Bic {

class Cyclist : public Cmn::SeqModel {
public:
    enum EState {
        EState_Idle = 0,
        EState_Boost = 2,
        EState_NoEnergy = 4,
        EState_Drinking = 5,
    };

    f32 getEnergy() const {
        return mEnergy;
    }
    void setEnergy(f32 energy) {
        mEnergy = energy;
    }

    u32 getHeartNum() const {
        return mHeartNum;
    }
    void setHeartNum(u32 num) {
        mHeartNum = num;
    }

private:
    u32 mFlags; // at 0xC
    char _10[0x14 - 0x10];
    f32 mEnergy; // at 0x14
    char _18[0x40 - 0x18];
    u32 mHeartNum; // at 0x40
};

} // namespace Bic
} // namespace Sp2

#endif
