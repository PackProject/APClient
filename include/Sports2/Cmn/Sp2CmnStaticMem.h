#ifndef SPORTS2_CMN_STATIC_MEM_H
#define SPORTS2_CMN_STATIC_MEM_H
#include <Pack/RPSystem.h>
#include <Sports2/Sp2Types.h>

namespace Sp2 {
namespace Cmn {

class StaticMem {
    RP_SINGLETON_DECL(StaticMem);

public:
    int getStaticVar(int var, bool absolute);
    void setStaticVar(int var, int value, bool absolute);

    u32 getSequence() const {
        return mSequence;
    }

    RPSysScene::ETime getIslandTime() const {
        return mIslandTime;
    }
    void setIslandTime(RPSysScene::ETime type) {
        mIslandTime = type;
    }

private:
    char _04[0x14];
    u32 mSequence; // at 0x18
    char _1C[0x380 - 0x1C];
    RPSysScene::ETime mIslandTime; // at 0x380
};

} // namespace Cmn
} // namespace Sp2

#endif
