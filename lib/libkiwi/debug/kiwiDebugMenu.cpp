#include <libkiwi.h>

namespace kiwi {

/******************************************************************************
 *
 * DebugMenu
 *
 ******************************************************************************/

/**
 * @brief Updates the menu state
 * @return Result of actions
 */
EDebugMenuResult DebugMenu::Calculate() {
    if (mPageStack.Empty()) {
        return EDebugMenuResult_None;
    }

    EDebugMenuResult result = mPageStack.Top()->Calculate();

    if (result == EDebugMenuResult_Back) {
        if (mPageStack.Size() > 1) {
            mPageStack.Pop();
        } else {
            // Can't close the root page
            result = EDebugMenuResult_Exit;
        }
    }

    return result;
}

/**
 * @brief User-level render pass
 */
void DebugMenu::UserDraw() {
    if (mPageStack.Empty()) {
        return;
    }

    mPageStack.Top()->UserDraw();
}

/******************************************************************************
 *
 * DebugPage
 *
 ******************************************************************************/

/**
 * @brief Updates the menu state
 * @return Result of actions
 */
EDebugMenuResult DebugPage::Calculate() {
    if (mOptions.Empty()) {
        return EDebugMenuResult_None;
    }

    for (int i = 0; i < EPlayer_Max; i++) {
        const WiiCtrl& rCtrl = CtrlMgr::GetInstance().GetWiiCtrl(i);
        if (!rCtrl.IsConnected()) {
            continue;
        }

        // Highlight option with Up/Down
        if (rCtrl.IsTrig(EButton_Up)) {
            mCursor = mCursor == 0 ? mOptions.Size() - 1 : mCursor - 1;
            return EDebugMenuResult_Cursor;

        } else if (rCtrl.IsTrig(EButton_Down)) {
            mCursor = mCursor == mOptions.Size() - 1 ? 0 : mCursor + 1;
            return EDebugMenuResult_Cursor;
        }

        K_ASSERT(0 <= mCursor && mCursor < mOptions.Size());

        DebugOptionBase* pOption = mOptions[mCursor];
        K_ASSERT_PTR(pOption);

        // Change option with Left/Right
        if (rCtrl.IsTrig(EButton_Right)) {
            return pOption->Increment();

        } else if (rCtrl.IsTrig(EButton_Left)) {
            return pOption->Decrement();
        }

        // Select option with A
        if (rCtrl.IsTrig(EButton_A)) {
            return pOption->Select();
        }

        // Close page with B
        if (rCtrl.IsTrig(EButton_B)) {
            return EDebugMenuResult_Back;
        }
    }

    return EDebugMenuResult_None;
}

/**
 * @brief User-level render pass
 */
void DebugPage::UserDraw() {
    static const f32 ox = 0.15f;
    static const f32 oy = 0.20f;

    static const f32 cursor = 0.015f;
    static const f32 option = 0.25f;

    static const f32 row = 0.05f;
    static const f32 column = 0.30f;

    f32 x = ox;
    f32 y = oy;

    for (u32 i = 0; i < mOptions.Size(); i++) {
        // Options marked as disabled are displayed in darker colors
        Color fill = mOptions[i]->IsEnabled() ? Color::WHITE : Color::GREY;

        Text(mOptions[i]->GetName())
            .SetTextColor(fill)
            .SetStrokeType(ETextStroke_Outline)
            .SetPosition(x, y);

        Text(mOptions[i]->GetValueText())
            .SetTextColor(fill)
            .SetStrokeType(ETextStroke_Outline)
            .SetPosition(x + option, y);

        // Show cursor at selected option
        if (i == mCursor) {
            Text("*")
                .SetStrokeType(ETextStroke_Outline)
                .SetPosition(x - cursor, y);
        }

        y += row;

        // Half of them are in the other column
        if (i > 0 && (i % (DEFAULT_MAX_OPTIONS / 2)) == 0) {
            x += column;
            y = oy;
        }
    }
}

} // namespace kiwi
