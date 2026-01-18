#include "Scene/DebugRoot/ConsolePage.h"

#include <libkiwi.h>

#include <revolution/KPAD.h>
#include <revolution/OS.h>
#include <revolution/VI.h>

namespace AP {
namespace DebugRoot {

/**
 * @brief Updates the page state
 * @return Result of actions
 */
kiwi::EDebugMenuResult ConsolePage::Calculate() {
    VIRetraceCallback preRetrace;
    VIRetraceCallback postRetrace;

    // Disable VI retrace handlers
    {
        kiwi::AutoInterruptLock lock;

        preRetrace = VISetPreRetraceCallback(nullptr);
        postRetrace = VISetPostRetraceCallback(nullptr);

        VIFlush();
    }

    kiwi::Nw4rDirectPrint::GetInstance().SetupXfb();

    kiwi::Nw4rConsole* pConsole = &kiwi::DebugConsole::GetInstance();
    pConsole->SetVisible(true);
    ConsoleLoop(pConsole);

    // Restore VI retrace handlers
    {
        kiwi::AutoInterruptLock lock;

        VISetPreRetraceCallback(preRetrace);
        VISetPostRetraceCallback(postRetrace);
    }

    return kiwi::EDebugMenuResult_Back;
}

/**
 * @brief Console control main loop
 *
 * @param pConsole Text console
 */
void ConsolePage::ConsoleLoop(kiwi::Nw4rConsole* pConsole) {
    ASSERT_PTR(pConsole);

    // Initial frame
    pConsole->DrawDirect();

    while (true) {
        // Only re-draw when display is changed
        bool draw = false;

        for (int i = 0; i < WPAD_MAX_CONTROLLERS; i++) {
            KPADStatus ks;
            std::memset(&ks, 0, sizeof(KPADStatus));
            KPADRead(i, &ks, 1);

            // Horizontal scroll
            if (ks.hold & KPAD_BTN_DLEFT) {
                pConsole->ScrollLeft();
            } else if (ks.hold & KPAD_BTN_DRIGHT) {
                pConsole->ScrollRight();
            }

            // Exit console
            if (ks.hold & KPAD_BTN_B) {
                return;
            }

            // Determine whether we need to draw the display again
            draw |= (ks.hold & (KPAD_BTN_DUP | KPAD_BTN_DDOWN | KPAD_BTN_DLEFT |
                                KPAD_BTN_DRIGHT)) != 0;
        }

        if (draw) {
            pConsole->DrawDirect();
        }

        // Wait 100ms before polling again
        s64 start = OSGetTime();
        while (OSGetTime() - start < OS_MSEC_TO_TICKS(100)) {
            ;
        }
    }
}

} // namespace DebugRoot
} // namespace AP