#ifndef SPORTS2_CMN_MODEL_H
#define SPORTS2_CMN_MODEL_H
#include <Sports2/Sp2Types.h>

#include <nw4r/math.h>

namespace Sp2 {
namespace Cmn {

class Model {
public:
    virtual nw4r::math::VEC3 getPosition() {
        return nw4r::math::VEC3(0.0f, 0.0f, 0.0f);
    }; // at 0x8

    virtual const char* getName() {
        return "no name";
    } // at 0xC

    virtual ~Model() = 0; // at 0x10

protected:
    u32 mId; // at 0x4
};

} // namespace Cmn
} // namespace Sp2

#endif
