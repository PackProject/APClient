#include <Pack/RPKernel.h>
#include <Pack/RPSystem.h>
#include <Sports2/Sp2Cmn.h>
#include <hooks/hooks_Swf.h>
#include <libkiwi.h>
#include <types.h>

namespace AP {
namespace Cmn {

/**
 * @brief Attempts to pause the game
 */
void TryPause() {
    bool isSwfPrc = RP_GET_INSTANCE(RPSysSceneMgr)->getCurrentSceneID() ==
                        kiwi::ESceneID_Sp2SwfScene &&
                    RP_GET_INSTANCE(Sp2::Cmn::StaticMem)->getSequence() ==
                        Sp2::Cmn::ESeq_Swf_Prc;

    // Pausing is disabled in Speed Slice while objects are falling
    if (isSwfPrc && Swf::PrcIsObjFalling()) {
        return;
    }

    RP_GET_INSTANCE(RPSysSysWinMgr)->updatePauseClosed();
}
KM_CALL(0x8023536C, TryPause);

/**
 * @brief Attempts to open the homebutton menu
 */
bool TryHomeButton() {
    bool isSwfPrc = RP_GET_INSTANCE(RPSysSceneMgr)->getCurrentSceneID() ==
                        kiwi::ESceneID_Sp2SwfScene &&
                    RP_GET_INSTANCE(Sp2::Cmn::StaticMem)->getSequence() ==
                        Sp2::Cmn::ESeq_Swf_Prc;

    // Home menu is disabled in Speed Slice while objects are falling
    if (isSwfPrc && Swf::PrcIsObjFalling()) {
        return false;
    }

    return true;
}
KM_CALL(0x802431B0, TryHomeButton);

} // namespace Cmn
} // namespace AP