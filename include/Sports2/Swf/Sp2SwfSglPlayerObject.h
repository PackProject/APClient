#ifndef SPORTS2_SWF_SGL_PLAYER_OBJECT_H
#define SPORTS2_SWF_SGL_PLAYER_OBJECT_H
#include <Sports2/Sp2Types.h>
#include <Sports2/Swf/Sp2SwfPlayerObject.h>

namespace Sp2 {
namespace Swf {

class SglPlayerObject : public PlayerObject {
public:
    void setHeartNum(int num) {
        mHeartNum = num;
    }

private:
    char _14[0x104 - 0x14];
    int mHeartNum; // at 0x104
};

} // namespace Swf
} // namespace Sp2

#endif