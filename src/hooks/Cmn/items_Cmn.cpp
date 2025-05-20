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
                    RP_GET_INSTANCE(Sp2::Cmn::StaticMem)->getSequence() ==
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
                    RP_GET_INSTANCE(Sp2::Cmn::StaticMem)->getSequence() ==
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
 * Randomization
 *
 ******************************************************************************/

/**
 * @brief Gets the random music ID that should be played instead of the
 * provided ID
 *
 * @param id Original music ID
 */
u32 RandomizeBgm(u32 id) {
    // Randomization disabled
    if (!CosmeticMgr::GetInstance().IsRandomBgm()) {
        return id;
    }

    // Not music
    if (!CosmeticMgr::IsBgm(id)) {
        return id;
    }

    return CosmeticMgr::GetInstance().GetRandomBgm(id);
}

/**
 * @brief RandomizeBgm trampoline
 */
TRAMPOLINE_DEF(0x802B722C, 0x802B7230){
    // clang-format off
    TRAMPOLINE_BEGIN

    bl RandomizeBgm
    mr r0, r3 // New ID must outlive the stack frame

    TRAMPOLINE_END
    mr r4, r0
    blr
    // clang-format on
}

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



} // namespace Cmn
} // namespace AP