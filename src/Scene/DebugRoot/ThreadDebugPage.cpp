#include "Scene/DebugRoot/ThreadDebugPage.h"

#include <libkiwi.h>

#include <revolution/OS.h>

namespace AP {
namespace DebugRoot {

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

    static const char* STATE_TBL[] = {
        "EXITED", "READY", "RUNNING", "SLEEPING", "MORIBUND",
    };

    static const f32 ox = 0.10f;
    static const f32 oy = 0.10f;

    static const f32 option = 0.25f;

    static const f32 row = 0.05f;
    static const f32 column = 0.30f;

    f32 x = ox;
    f32 y = oy;

    for (OSThread* pIt = OSGetCurrentThread(); pIt != nullptr;
         pIt = pIt->nextActive) {

        // libkiwi threads link to the OSThread userdata
        void* pUserData = pIt->specific[0];

        const char* pName =
            pUserData != nullptr
                ? static_cast<kiwi::Thread*>(pUserData)->GetName().CStr()
                : "NoName";

        kiwi::Text("[%s] %s flg=%d pri=%d sus=%d\n", pName,
                   STATE_TBL[pIt->state], pIt->flags, pIt->priority,
                   pIt->suspend)
            .SetTextColor(kiwi::Color::WHITE)
            .SetStrokeType(kiwi::ETextStroke_Outline)
            .SetPosition(x, y);

        y += row;
    }

    OSEnableScheduler();
}

} // namespace DebugRoot
} // namespace AP