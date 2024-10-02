#ifndef SPORTS2_SWF_PRC_RULE_OBJECT_H
#define SPORTS2_SWF_PRC_RULE_OBJECT_H
#include <Sports2/Sp2Types.h>

namespace Sp2 {
namespace Swf {

// Forward declarations
class TrainerObject;

class PrcRuleObject /* public Cmn::ObjectBase */ {
public:
    TrainerObject* getTrainerObject() const {
        return mpTrainerObject;
    }

private:
    char _00[0x14];
    TrainerObject* mpTrainerObject; // at 0x14
};

} // namespace Swf
} // namespace Sp2

#endif