#ifndef SPORTS2_BSK_BALL_H
#define SPORTS2_BSK_BALL_H
#include <Sports2/Sp2Types.h>

namespace Sp2 {
namespace Bsk {

class Ball /* public Cmn::Model */ {
public:
    enum EType { EType_Regular, EType_Bonus };

public:
    void setType(EType type);
};

} // namespace Bsk
} // namespace Sp2

#endif
