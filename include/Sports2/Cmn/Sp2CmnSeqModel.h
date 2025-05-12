#ifndef SPORTS2_CMN_SEQ_MODEL_H
#define SPORTS2_CMN_SEQ_MODEL_H
#include <Sports2/Cmn/Sp2CmnModel.h>
#include <Sports2/Sp2Types.h>

namespace Sp2 {
namespace Cmn {

class SeqModel : public Model {
public:
    virtual ~SeqModel() {} // at 0x10

    u32 getState() const {
        return mState;
    }
    void setState(u32 state) {
        mState = state;
    }

private:
    u32 mState; // at 0x8
};

} // namespace Cmn
} // namespace Sp2

#endif
