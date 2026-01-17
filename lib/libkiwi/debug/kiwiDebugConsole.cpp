#include <libkiwi.h>

#include <revolution/KPAD.h>
#include <revolution/OS.h>
#include <revolution/VI.h>

namespace kiwi {

K_DYNAMIC_SINGLETON_IMPL(DebugConsole);

/**
 * @brief Enters the console main loop
 */
void DebugConsole::Enter() {
    VIRetraceCallback preRetrace;
    VIRetraceCallback postRetrace;

    {
        AutoInterruptLock lock;

        preRetrace = VISetPreRetraceCallback(nullptr);
        postRetrace = VISetPostRetraceCallback(nullptr);

        VIFlush();
    }

    Nw4rDirectPrint::GetInstance().SetupXfb();

    SetVisible(true);
    MainLoop();

    {
        AutoInterruptLock lock;

        VISetPreRetraceCallback(preRetrace);
        VISetPostRetraceCallback(postRetrace);
    }
}

/**
 * @brief Draws the console using DirectPrint
 */
void DebugConsole::DrawDirect() {
    // ShowLatestLine();
    Nw4rConsole::DrawDirect();
}

/**
 * @brief Console main loop
 */
void DebugConsole::MainLoop() {
    DrawDirect();

    while (true) {
        // Only re-draw when display is changed
        bool draw = false;

        for (int i = 0; i < WPAD_MAX_CONTROLLERS; i++) {
            KPADStatus ks;
            std::memset(&ks, 0, sizeof(KPADStatus));
            KPADRead(i, &ks, 1);

            // Horizontal scroll
            if (ks.hold & KPAD_BTN_DLEFT) {
                ScrollLeft();
            } else if (ks.hold & KPAD_BTN_DRIGHT) {
                ScrollRight();
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
            DrawDirect();
        }

        // Wait 100ms before polling again
        s64 start = OSGetTime();
        while (OSGetTime() - start < OS_MSEC_TO_TICKS(100)) {
            ;
        }
    }
}

} // namespace kiwi