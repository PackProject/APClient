#ifndef SPORTS2_SWF_USER_CTRL_H
#define SPORTS2_SWF_USER_CTRL_H
#include <Sports2/Sp2Types.h>

namespace Sp2 {
namespace Swf {

// Forward declarations
class PlayerObject;

class UserCtrl {
public:
    PlayerObject* getPlayerObject() const {
        return mpPlayerObject;
    }

    bool isBlocking() const {
        return mIsBlocking;
    }
    void setBlocking(bool flag) {
        mIsBlocking = flag;
    }

private:
    char _00[0x8];
    PlayerObject* mpPlayerObject; // at 0x8
    bool mIsBlocking;             // at 0xC
};

} // namespace Swf
} // namespace Sp2

#endif