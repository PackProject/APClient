#ifndef SPORTS2_PLN_ISLAND_SEQ_H
#define SPORTS2_PLN_ISLAND_SEQ_H
#include <Sports2/Sp2Types.h>

namespace Sp2 {
namespace Pln {

class IslandSeq /* public Cmn::IslandSeqBase */ {
public:
    u32 setTimeRemain(u32 remain) {
        mTimeRemain = remain;
    }

private:
    char _00[0xCC];
    u32 mTimeRemain; // at 0xCC
};

} // namespace Pln
} // namespace Sp2

#endif