#ifndef SPORTS2_SWF_SOUND_OBJECT_H
#define SPORTS2_SWF_SOUND_OBJECT_H
#include <Sports2/Sp2Types.h>

namespace Sp2 {
namespace Swf {

class SoundObject /* public Cmn::ObjectBase */ {
public:
    bool isEnabled() const {
        return mIsEnabled;
    }
    void setEnabled(bool flag) {
        mIsEnabled = flag;
    }

private:
    char _00[0x19];
    bool mIsEnabled;
};

} // namespace Swf
} // namespace Sp2

#endif