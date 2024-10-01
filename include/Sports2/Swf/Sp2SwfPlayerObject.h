#ifndef SPORTS2_SWF_PLAYER_OBJECT_H
#define SPORTS2_SWF_PLAYER_OBJECT_H
#include <Sports2/Sp2Types.h>

namespace Sp2 {
namespace Swf {

class PlayerObject /* public ??? */ {
public:
    int getRemoteNo() const {
        return mRemoteNo;
    }

private:
    char _00[0x10];
    int mRemoteNo; // at 0x10
};

} // namespace Swf
} // namespace Sp2

#endif