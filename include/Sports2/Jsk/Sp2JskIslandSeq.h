#ifndef SPORTS2_JSK_ISLAND_SEQ_H
#define SPORTS2_JSK_ISLAND_SEQ_H
#include <Sports2/Sp2Types.h>

namespace Sp2 {
namespace Jsk {

class IslandSeq /* public Cmn::IslandSeqBase */ {
public:
    u32 setTimeRemain(u32 remain) {
        mTimeRemain = remain;
    }

private:
    char _00[0x54];
    u32 mTimeRemain; // at 0x54
};

} // namespace Jsk
} // namespace Sp2

#endif