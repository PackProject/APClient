#ifndef SPORTS2_CMN_STATIC_MEM_H
#define SPORTS2_CMN_STATIC_MEM_H
#include <Pack/RPSystem.h>
#include <Sports2/Sp2Types.h>

#include <egg/core.h>

namespace Sp2 {
namespace Cmn {

enum EPlayStyle { EPlayStyle_Team, EPlayStyle_Solo };
enum EPlayTeam { EPlayTeam_Blue, EPlayTeam_Red };

/**
 * @brief Static memory region
 * @details Used for passing data between scenes
 */
class StaticMem /* : EGG::Singleton */ {
    RP_SINGLETON_DECL(StaticMem);

public:
    u32 getVariable(u32 index, bool local = false);
    void setVariable(u32 index, u32 value, bool local = false);

    s32 getSceneSeq() const {
        return mSequenceNo;
    }
    void setSceneSeq(s32 seq) {
        mSequenceNo = seq;
    }

    u32 getSceneGroup() const {
        return mGroupNo;
    }
    void setSceneGroup(u32 group) {
        mGroupNo = group;
    }

    u32 getStageNo() const {
        return mStageNo;
    }
    void setStageNo(u32 stage) {
        mStageNo = stage;
    }

    RPSysScene::ETime getIslandTime() const {
        return mIslandTime;
    }
    void setIslandTime(RPSysScene::ETime type) {
        mIslandTime = type;
    }

private:
    char _04[0x14 - 0x4];
    s32 mGroupNo;            // at 0x14
    u32 mSequenceNo;         // at 0x18
    u32 mStageNo;            // at 0x1C
    EPlayStyle mPlayStyle;   // at 0x20
    EPlayTeam mPlayTeams[4]; // at 0x24
    char _34[0x380 - 0x34];
    RPSysScene::ETime mIslandTime; // at 0x380
    // . . .
};

} // namespace Cmn
} // namespace Sp2

#endif
