#ifndef SPORTS2_SWF_SCENE_H
#define SPORTS2_SWF_SCENE_H
#include <Sports2/Sp2Types.h>

namespace Sp2 {
namespace Swf {

// Forward declarations
class SoundObject;

class Scene /* : public RPSysMplsGameScene */ {
public:
    static Scene* getInstance() {
        return sInstance;
    }

    SoundObject* getGuardSound() const {
        return mpGuardSound;
    }

private:
    char _00[0x18C];
    SoundObject* mpGuardSound; // at 0x18C

    static Scene* sInstance;
};

} // namespace Swf
} // namespace Sp2

#endif