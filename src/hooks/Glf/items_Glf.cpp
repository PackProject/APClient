#include "core/ItemMgr.h"
#include "hooks/trampoline.h"

#include <Sports2/Sp2Cmn.h>
#include <Sports2/Sp2Glf.h>

#include <libkiwi.h>

namespace AP {
namespace Glf {

/******************************************************************************
 *
 * Golf
 *
 ******************************************************************************/
int GlfClubUp(int currentClubIdx) {
    for (int i = currentClubIdx - 1; i >= 0; i--) {
        if (ItemMgr::GetInstance().IsGlfClubUnlock(i)) {
            return i;
        }
    }

    return currentClubIdx;
}

/**
 * @brief GlfClubUp trampoline
 */
TRAMPOLINE_DEF(0x8040945c, 0x80409460) {
    // clang-format off
    TRAMPOLINE_BEGIN

    mr r3, r4
    bl GlfClubUp
    mr r0, r3

    TRAMPOLINE_END
    blr
    // clang-format on
}

int GlfClubDown(int currentClubIdx) {
    for (int i = currentClubIdx + 1; i <= 7; i++) {
        if (ItemMgr::GetInstance().IsGlfClubUnlock(i)) {
            return i;
        }
    }

    return currentClubIdx;
}

/**
 * @brief GlfClubDown trampoline
 */
TRAMPOLINE_DEF(0x804093a0, 0x804093a4) {
    // clang-format off
    TRAMPOLINE_BEGIN

    mr r3, r4
    bl GlfClubDown
    mr r0, r3

    TRAMPOLINE_END
    blr
    // clang-format on
}

int GetMaxClubID() {
    int maxClubID = 0;

    for (int i = 0; i < ItemMgr::GLF_CLUB_COUNT - 1; i++) {
        if (ItemMgr::GetInstance().IsGlfClubUnlock(i)) {
            maxClubID = i;
        }
    }

    return maxClubID;
}

int GetMinClubID() {
    int minClubID = 7;

    for (int i = 0; i <= ItemMgr::GLF_CLUB_COUNT - 1; i++) {
        if (ItemMgr::GetInstance().IsGlfClubUnlock(i)) {
            minClubID = i;
        }
    }

    return minClubID;
}

int GetNextClubUp(int currentClubIdx) {
    int nextClubIdx = currentClubIdx;

    for (int i = currentClubIdx - 1; i >= 0; i--) {
        if (ItemMgr::GetInstance().IsGlfClubUnlock(i)) {
            nextClubIdx = i;
            break;
        }
    }

    // if no club up, go down
    if (nextClubIdx == currentClubIdx) {
        for (int i = currentClubIdx; i < 7; i++) {
            if (ItemMgr::GetInstance().IsGlfClubUnlock(i)) {
                nextClubIdx = i;
                break;
            }
        }
    }

    return nextClubIdx;
}

int GetNextClubDown(int currentClubIdx) {
    int nextClubIdx = currentClubIdx;

    for (int i = currentClubIdx + 1; i <= 7; i++) {
        if (ItemMgr::GetInstance().IsGlfClubUnlock(i)) {
            nextClubIdx = i;
            break;
        }
    }

    // if no club down, go up
    if (nextClubIdx == currentClubIdx) {
        for (int i = currentClubIdx; i >= 0; i--) {
            if (ItemMgr::GetInstance().IsGlfClubUnlock(i)) {
                nextClubIdx = i;
                break;
            }
        }
    }

    return nextClubIdx;
}

/**
 * @brief Putter Set trampoline
 */
TRAMPOLINE_DEF(0x80409148, 0x8040914c){
    // clang-format off
    TRAMPOLINE_BEGIN

    bl GetMinClubID
    mr r0, r3

    TRAMPOLINE_END
    blr
    // clang-format on
}

/**
 * @brief 3 Iron Set trampoline
 */
TRAMPOLINE_DEF(0x8040917c, 0x80409180){
    // clang-format off
    TRAMPOLINE_BEGIN

    li r3, 2
    bl GetNextClubUp
    mr r0, r3

    TRAMPOLINE_END
    blr
    // clang-format on
}

/**
 * @brief Driver Set trampoline
 */
TRAMPOLINE_DEF(0x804091b0, 0x804091b4){
    // clang-format off
    TRAMPOLINE_BEGIN

    bl GetMaxClubID
    mr r0, r3

    TRAMPOLINE_END
    blr
    // clang-format on
}

/**
 * @brief R26 Club Set trampoline
 *
 */
TRAMPOLINE_DEF(0x80409264, 0x80409268){
    // clang-format off
    TRAMPOLINE_BEGIN

    mr r3, r26
    bl GetNextClubUp
    stw r3, 0x2C(r29)

    TRAMPOLINE_END
    blr
    // clang-format on
}

/**
 * @brief R26 Club Set trampoline
 *
 */
TRAMPOLINE_DEF(0x8040924c, 0x80409250) {
    // clang-format off
    TRAMPOLINE_BEGIN

    mr r3, r26
    bl GetNextClubDown
    stw r3, 0x2C(r29)

    TRAMPOLINE_END
    blr
    // clang-format on
}

void GlfSetBlindFlag(bool hold2) {
    if (hold2 || !ItemMgr::GetInstance().IsGlfHUD()) {
        RP_GET_INSTANCE(Sp2::Cmn::StaticMem)->setVariable(3, 1, false);
    }

    else {
        RP_GET_INSTANCE(Sp2::Cmn::StaticMem)->setVariable(3, 0, false);
    }
}

/**
 * @brief GlfSetBlindFlag trampoline
 */
TRAMPOLINE_DEF(0x80406a1c, 0x80406a30){
    // clang-format off
    TRAMPOLINE_BEGIN

    bl GlfSetBlindFlag

    TRAMPOLINE_END
    blr
    // clang-format on
}

u32 GlfDisableZoom(u32 input) {
    if (!ItemMgr::GetInstance().IsGlfViewLow())
        return 0;
    else
        return input;
}

/**
 * @brief GlfDisableZoom trampoline
 */
TRAMPOLINE_DEF(0x803facdc, 0x803face0){
    // clang-format off
    TRAMPOLINE_BEGIN

    lwz r0, 0x1c(r31)
    mr r3, r0
    bl GlfDisableZoom
    mr r0, r3

    TRAMPOLINE_END
    blr
    // clang-format on
}

u32 GlfDisableTopo(u32 input) {
    if (!ItemMgr::GetInstance().IsGlfViewSlope())
        return 0;
    else
        return input;
}

/**
 * @brief GlfDisableTopo trampoline
 */
TRAMPOLINE_DEF(0x803fac64, 0x803fac68) {
    // clang-format off
    TRAMPOLINE_BEGIN

    lwz r0, 0x1c(r31)
    mr r3, r0
    bl GlfDisableTopo
    mr r0, r3

    TRAMPOLINE_END
    blr
    // clang-format on
}

bool GlfDisableTurn() {
    return ItemMgr::GetInstance().IsGlfTurn();
}

/**
 * @brief GlfDisableTurn trampoline
 */
TRAMPOLINE_DEF(0x803fac54, 0x803fac58) {
    // clang-format off
    TRAMPOLINE_BEGIN

    mr r31, r6
    mr r30, r5
    mr r29, r4
    mr r28, r3
    bl GlfDisableTurn
    cmpwi r3, 0
    beq end

    mr r6, r31
    mr r5, r30
    mr r4, r29
    mr r3, r28
    lis r12, 0x803fcf28@ha
    addi r12, r12, 0x803fcf28@l
    mtctr r12
    bctrl

    end:
    TRAMPOLINE_END
    blr
    // clang-format on
}

} // namespace Glf
} // namespace AP
