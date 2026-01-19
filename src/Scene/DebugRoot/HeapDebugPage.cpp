#include "Scene/DebugRoot/HeapDebugPage.h"

#include <libkiwi.h>

#include <revolution/OS.h>

namespace AP {
namespace DebugRoot {
namespace {

/**
 * @brief Displays information about the specified heap
 *
 * @param pOSThread Operating system thread
 * @param ox Text X-position
 * @param oy Text Y-position
 */
void DrawHeapText(const char* pName, EGG::Heap* pHeap, f32 ox, f32 oy) {
    const char* pFormat = pHeap != nullptr ? "%s: %.2f KB free" : "%s: NULL";

    f32 freeSize =
        pHeap != nullptr ? static_cast<f32>(pHeap->getAllocatableSize()) : 0.0f;

    kiwi::Text(pFormat, pName, OS_MEM_B_TO_KB(freeSize))
        .SetTextColor(kiwi::Color::WHITE)
        .SetStrokeType(kiwi::ETextStroke_Outline)
        .SetPosition(ox, oy);
}

} // namespace

/**
 * @brief Updates the page state
 * @return Result of actions
 */
kiwi::EDebugMenuResult HeapDebugPage::Calculate() {
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
void HeapDebugPage::UserDraw() {
    kiwi::AutoInterruptLock lock;
    OSDisableScheduler();

    static const f32 ox = 0.10f;
    static const f32 oy = 0.10f;
    static const f32 row = 0.05f;

    f32 x = ox;
    f32 y = oy;

    DrawHeapText("libkiwi (MEM1)",                                           //
                 kiwi::MemoryMgr::GetInstance().GetHeap(kiwi::EMemory_MEM1), //
                 x, y);
    y += row;

    DrawHeapText("libkiwi (MEM2)",                                           //
                 kiwi::MemoryMgr::GetInstance().GetHeap(kiwi::EMemory_MEM2), //
                 x, y);
    y += row;

    DrawHeapText("RootMem1",                     //
                 RPSysSystem::getRootHeapMem1(), //
                 x, y);
    y += row;

    DrawHeapText("RootMem2",                     //
                 RPSysSystem::getRootHeapMem2(), //
                 x, y);
    y += row;

    DrawHeapText("SysMem1",                    //
                 RPSysSystem::getSystemHeap(), //
                 x, y);
    y += row;

    DrawHeapText("SysMem2",                                       //
                 RP_GET_INSTANCE(RPSysSystem)->getSystemHeapRP(), //
                 x, y);
    y += row;

    DrawHeapText("Res",                                           //
                 RP_GET_INSTANCE(RPSysSystem)->getResourceHeap(), //
                 x, y);
    y += row;

    DrawHeapText("ResCache",                                      //
                 RP_GET_INSTANCE(RPSysSystem)->getResCacheHeap(), //
                 x, y);
    y += row;

    DrawHeapText("RootScene",                                      //
                 RP_GET_INSTANCE(RPSysSystem)->getRootSceneHeap(), //
                 x, y);
    y += row;

    DrawHeapText("RootSceneDepend",                                      //
                 RP_GET_INSTANCE(RPSysSystem)->getRootSceneDependHeap(), //
                 x, y);
    y += row;

    DrawHeapText("Mem1Rest",                                      //
                 RP_GET_INSTANCE(RPSysSystem)->getMem1RestHeap(), //
                 x, y);
    y += row;

    DrawHeapText("Mem2Rest",                                      //
                 RP_GET_INSTANCE(RPSysSystem)->getMem2RestHeap(), //
                 x, y);
    y += row;

    OSEnableScheduler();
}

} // namespace DebugRoot
} // namespace AP