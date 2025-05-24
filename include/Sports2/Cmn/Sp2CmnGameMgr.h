#ifndef SPORTS2_CMN_GAME_MGR_H
#define SPORTS2_CMN_GAME_MGR_H
#include <Pack/RPSystem.h>
#include <Sports2/Sp2Types.h>

namespace Sp2 {
namespace Cmn {

class GameMgr {
    RP_SINGLETON_DECL(GameMgr);

public:
    void setPlayerNum(int num);
    void setControllerNum(int num);

    void writeDebugPlayerData();

private:
    ;
};

} // namespace Cmn
} // namespace Sp2

#endif
