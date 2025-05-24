#ifndef SPORTS2_CMN_STATIC_MEM_H
#define SPORTS2_CMN_STATIC_MEM_H
#include <Pack/RPSystem.h>
#include <Sports2/Sp2Types.h>

namespace Sp2 {
namespace Cmn {

class StaticMem {
    RP_SINGLETON_DECL(StaticMem);

public:
    u32 getVariable(u32 index, bool local = false);
    void setVariable(u32 index, u32 value, bool local = false);

    u32 getSceneSeq() const {
        return mSequenceNo;
    }
    void setSceneSeq(u32 seq);

    u32 getSceneGroup() const {
        return mGroupNo;
    }
    void setSceneGroup(u32 group);

    RPSysScene::ETime getIslandTime() const {
        return mIslandTime;
    }
    void setIslandTime(RPSysScene::ETime type) {
        mIslandTime = type;
    }

private:
    char _04[0x14 - 0x4];
    u32 mGroupNo;    // at 0x14
    u32 mSequenceNo; // at 0x18
    char _1C[0x380 - 0x1C];
    RPSysScene::ETime mIslandTime; // at 0x380
};

} // namespace Cmn
} // namespace Sp2

#endif
