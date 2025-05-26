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
namespace Cosmetic {

/**
 * @brief Overrides the BGM ID based on the randomizer settings
 *
 * @param id Original music ID
 */
u32 InterceptBgm(u32 id) {
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
 * @brief InterceptBgm trampoline
 */
TRAMPOLINE_DEF(0x802B722C, 0x802B7230){
    // clang-format off
    TRAMPOLINE_BEGIN

    bl InterceptBgm
    mr r0, r3 // New ID must outlive the stack frame

    TRAMPOLINE_END
    mr r4, r0
    blr
    // clang-format on
}

/**
 * @brief Overrides the island time based on the randomizer settings
 *
 * @param pScene Incoming scene
 */
RPSysScene::ETime InterceptIslandTime(RPSysScene* pScene) {
    ASSERT_PTR(pScene);

    // Randomization disabled
    if (!CosmeticMgr::GetInstance().IsRandomTime()) {
        return pScene->getIslandTime();
    }

    s32 group = RP_GET_INSTANCE(Sp2::Cmn::StaticMem)->getSceneGroup();

    // Ignore Island Flyover
    if (group == Sp2::Cmn::EGroupID_Pln) {
        return pScene->getIslandTime();
    }

    // 'Auto' delegates to the scene
    RPSysScene::ETime time = CosmeticMgr::GetInstance().GetRandomTime(group);
    return time != RPSysScene::ETime_Auto ? time : pScene->getIslandTime();
}
KM_CALL(0x8026a56c, InterceptIslandTime);

} // namespace Cosmetic
} // namespace Cmn
} // namespace AP
