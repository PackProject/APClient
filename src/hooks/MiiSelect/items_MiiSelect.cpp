#include <types.h>

#include "core/ItemMgr.h"
#include "hooks/trampoline.h"

#include <Sports2/Sp2Cmn.h>
#include <Sports2/Sp2MiiSelect.h>

#include <libkiwi.h>

namespace AP {
namespace MiiSelect {

/**
 * @brief Overrides a stage select button's state based on the AP item unlocks
 *
 * @param pBtnInfo Stage select save data info
 * @param idx Button index
 * @param state Pending button state
 */
void InterceptStageBtnState(Sp2::MiiSelect::StageSelectBtnInfo* pBtnInfo,
                            u32 idx,
                            Sp2::MiiSelect::StageSelectBtnInfo::EState state) {

    ASSERT(pBtnInfo != nullptr);

    // Scene group determines which sport we are dealing with
    switch (RP_GET_INSTANCE(Sp2::Cmn::StaticMem)->getSceneGroup()) {
    case Sp2::Cmn::EGroupID_Jsk: {
        state = ItemMgr::GetInstance().IsJskStageUnlock(idx)
                    ? Sp2::MiiSelect::StageSelectBtnInfo::EState_Open
                    : Sp2::MiiSelect::StageSelectBtnInfo::EState_Locked;
        break;
    }

    case Sp2::Cmn::EGroupID_Arc: {
        state = ItemMgr::GetInstance().IsArcStageUnlock(idx)
                    ? Sp2::MiiSelect::StageSelectBtnInfo::EState_Open
                    : Sp2::MiiSelect::StageSelectBtnInfo::EState_Locked;
        break;
    }

    case Sp2::Cmn::EGroupID_Can: {
        state = ItemMgr::GetInstance().IsCanStageUnlock(idx)
                    ? Sp2::MiiSelect::StageSelectBtnInfo::EState_Open
                    : Sp2::MiiSelect::StageSelectBtnInfo::EState_Locked;
        break;
    }

    case Sp2::Cmn::EGroupID_Wkb: {
        state = ItemMgr::GetInstance().IsWkbStageUnlock(idx)
                    ? Sp2::MiiSelect::StageSelectBtnInfo::EState_Open
                    : Sp2::MiiSelect::StageSelectBtnInfo::EState_Locked;
        break;
    }

    case Sp2::Cmn::EGroupID_Pln: {
        state = ItemMgr::GetInstance().IsPlnStageUnlock(idx)
                    ? Sp2::MiiSelect::StageSelectBtnInfo::EState_Open
                    : Sp2::MiiSelect::StageSelectBtnInfo::EState_Locked;
        break;
    }

    case Sp2::Cmn::EGroupID_Glf: {
        state = ItemMgr::GetInstance().IsGlfStageUnlock(idx)
                    ? Sp2::MiiSelect::StageSelectBtnInfo::EState_Open
                    : Sp2::MiiSelect::StageSelectBtnInfo::EState_Locked;
        break;
    }

    case Sp2::Cmn::EGroupID_Dgl: {
        state = ItemMgr::GetInstance().IsDglStageUnlock(idx)
                    ? Sp2::MiiSelect::StageSelectBtnInfo::EState_Open
                    : Sp2::MiiSelect::StageSelectBtnInfo::EState_Locked;
        break;
    }

    case Sp2::Cmn::EGroupID_Bic: {
        state = ItemMgr::GetInstance().IsBicStageUnlock(idx)
                    ? Sp2::MiiSelect::StageSelectBtnInfo::EState_Open
                    : Sp2::MiiSelect::StageSelectBtnInfo::EState_Locked;
        break;
    }

    default: {
        UNREACHABLE();
        break;
    }
    }

    pBtnInfo->setBtnState(idx, state);
}

/**
 * @brief InterceptStageBtnState trampoline
 */
TRAMPOLINE_DEF(0x8031bda0, 0x8031bdac) {
    // clang-format off
    TRAMPOLINE_BEGIN

    bl InterceptStageBtnState

    TRAMPOLINE_END
    blr
    // clang-format on
}

} // namespace MiiSelect
} // namespace AP
