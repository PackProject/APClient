#include <types.h>

#include "core/CosmeticMgr.h"
#include "core/ItemMgr.h"
#include "hooks/Swf/items_Swf.h"
#include "hooks/trampoline.h"

#include <Pack/RPKernel.h>
#include <Pack/RPSystem.h>
#include <Sports2/Sp2Cmn.h>

#include <libkiwi.h>

namespace AP {
namespace Cmn {
namespace Item {

/******************************************************************************
 *
 * Pausing
 *
 ******************************************************************************/

/**
 * @brief Attempts to pause the game
 */
void TryPause() {
    bool isSwfPrc = RP_GET_INSTANCE(RPSysSceneMgr)->getCurrentSceneID() ==
                        kiwi::ESceneID_Sp2SwfScene &&
                    RP_GET_INSTANCE(Sp2::Cmn::StaticMem)->getSceneSeq() ==
                        Sp2::Cmn::ESeq_Swf_Prc;

    // Pausing is disabled in Speed Slice while objects are falling
    if (isSwfPrc && !ItemMgr::GetInstance().IsSwfPrcPause() &&
        Swf::PrcIsObjFalling()) {
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
                    RP_GET_INSTANCE(Sp2::Cmn::StaticMem)->getSceneSeq() ==
                        Sp2::Cmn::ESeq_Swf_Prc;

    // Home menu is disabled in Speed Slice while objects are falling
    if (isSwfPrc && !ItemMgr::GetInstance().IsSwfPrcPause() &&
        Swf::PrcIsObjFalling()) {
        return;
    }

    return true;
}
KM_CALL(0x802431B0, TryHomeButton);

/******************************************************************************
 *
 * Menu
 *
 ******************************************************************************/

/**
 * @brief Tests whether the specified sequence ("category") is unlocked
 *
 * @param seq Sequence id
 */
Sp2::Cmn::EUnlockState GetSeqUnlockState(UNKWORD, Sp2::Cmn::ESaveSeq seq) {
    bool unlock = ItemMgr::GetInstance().IsCategoryUnlock(seq);

    return unlock ? Sp2::Cmn::EUnlockState_Unlocked
                  : Sp2::Cmn::EUnlockState_Locked;
}
KM_BRANCH(0x80261F84, GetSeqUnlockState);

} // namespace Item
} // namespace Cmn
} // namespace AP
