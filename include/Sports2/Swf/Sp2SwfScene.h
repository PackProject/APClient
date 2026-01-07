#ifndef SPORTS2_SWF_SCENE_H
#define SPORTS2_SWF_SCENE_H
#include <Sports2/Sp2Types.h>

namespace Sp2 {
namespace Swf {

// Forward declarations
class SoundObject;
class PrcRuleObject;

class Scene /* : public RPSysMplsGameScene */ {
public:
    static Scene* instance() {
        return sInstance;
    }

    PrcRuleObject* getPrcRuleObject() const {
        return mpPrcRuleObject;
    }

    SoundObject* getGuardSoundObject() const {
        return mpGuardSound;
    }

private:
    char _00[0x180];
    PrcRuleObject* mpPrcRuleObject; // at 0x180
    char _184[0x18C - 0x184];
    SoundObject* mpGuardSound; // at 0x18C

    static Scene* sInstance;
};

} // namespace Swf
} // namespace Sp2

#endif