#include "Scene/DebugRoot/ThreadDebugPage.h"

#include <libkiwi.h>

#include <revolution/OS.h>

namespace AP {
namespace DebugRoot {
namespace {

/**
 * @brief Displays information about the specified thread
 *
 * @param pOSThread Operating system thread
 * @param ox Text X-position
 * @param oy Text Y-position
 */
void DrawThreadText(const OSThread* pOSThread, f32 ox, f32 oy) {
    ASSERT_PTR(pOSThread);

    static const char* STATE_TBL[] = {
        "EXITED", "READY", "RUNNING", "SLEEPING", "MORIBUND",
    };

    // libkiwi threads link to the OSThread userdata
    void* pUserData = pOSThread->specific[0];
    kiwi::Thread* pKiwiThread = static_cast<kiwi::Thread*>(pUserData);

    const char* pName =
        pKiwiThread != nullptr ? pKiwiThread->GetName().CStr() : "NoName";

    kiwi::Text("[%s] %s flg=%d pri=%d sus=%d", pName,
               STATE_TBL[pOSThread->state], pOSThread->flags,
               pOSThread->priority, pOSThread->suspend)
        .SetTextColor(kiwi::Color::WHITE)
        .SetStrokeType(kiwi::ETextStroke_Outline)
        .SetPosition(ox, oy);
}

} // namespace

/**
 * @brief Updates the page state
 * @return Result of actions
 */
kiwi::EDebugMenuResult ThreadDebugPage::Calculate() {
    for (int i = 0; i < kiwi::EPlayer_Max; i++) {
        const kiwi::WiiCtrl& rCtrl = kiwi::CtrlMgr::GetInstance().GetWiiCtrl(i);
        if (!rCtrl.IsConnected()) {
            continue;
        }

        // Close page with B
        if (rCtrl.IsTrig(kiwi::EButton_B)) {
            return kiwi::EDebugMenuResult_Back;
        }
    }

    return kiwi::EDebugMenuResult_None;
}

/**
 * @brief User-level render pass
 */
void ThreadDebugPage::UserDraw() {
    kiwi::AutoInterruptLock lock;
    OSDisableScheduler();

    static const f32 ox = 0.10f;
    static const f32 oy = 0.10f;
    static const f32 row = 0.05f;

    f32 x = ox;
    f32 y = oy;

    for (OSThread* pIt = OSGetCurrentThread(); pIt != nullptr;
         pIt = pIt->nextActive) {

        DrawThreadText(pIt, x, y);
        y += row;
    }

    OSEnableScheduler();
}

} // namespace DebugRoot
} // namespace AP