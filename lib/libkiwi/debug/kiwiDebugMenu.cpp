#include <libkiwi.h>

namespace kiwi {

/******************************************************************************
 *
 * DebugMenu
 *
 ******************************************************************************/

/**
 * @brief Opens a new menu page
 *
 * @param rPage Menu page
 */
void DebugMenu::OpenPage(DebugPage& rPage) {
    rPage.SetParent(*this);
    mPageStack.Push(&rPage);
}

/**
 * @brief Updates the menu state
 * @return Result of actions
 */
EDebugMenuResult DebugMenu::Calculate() {
    if (mPageStack.Empty()) {
        return EDebugMenuResult_None;
    }

    EDebugMenuResult result = mPageStack.Top().Calculate();

    if (result == EDebugMenuResult_Close) {
        // Can't close the root page
        if (mPageStack.Size() > 1) {
            mPageStack.Pop();
        } else {
            result = EDebugMenuResult_Invalid;
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

    mPageStack.Top().UserDraw();
}

/******************************************************************************
 *
 * DebugPage
 *
 ******************************************************************************/

/**
 * @brief Appends a new option to the page
 *
 * @param rOption Debug option
 * @return Success
 */
bool DebugPage::AddOption(DebugOptionBase& rOption) {
    if (mOptions.Size() >= mMaxOptions) {
        K_LOG_EX("Can't add option: %s\n", rOption.GetName().CStr());
        return false;
    }

    rOption.SetParent(*this);
    mOptions.PushBack(&rOption);

    return true;
}

/**
 * @brief Updates the menu state
 * @return Result of actions
 */
EDebugMenuResult DebugPage::Calculate() {
    for (int i = 0; i < EPlayer_Max; i++) {
        const WiiCtrl& rCtrl =
            CtrlMgr::GetInstance().GetWiiCtrl(static_cast<EPlayer>(i));

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
        K_ASSERT(pOption != nullptr);

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
            return EDebugMenuResult_Close;
        }
    }

    return EDebugMenuResult_None;
}

/**
 * @brief User-level render pass
 */
void DebugPage::UserDraw() {
    f32 x = 0.15f;
    f32 y = 0.20f;

    static const f32 cursor = 0.015f;
    static const f32 option = 0.25f;
    static const f32 row = 0.05f;

    for (u32 i = 0; i < mOptions.Size(); i++) {
        Text(mOptions[i]->GetName())
            .SetStrokeType(ETextStroke_Outline)
            .SetPosition(x, y);

        Text(mOptions[i]->GetValueText())
            .SetStrokeType(ETextStroke_Outline)
            .SetPosition(x + option, y);

        // Show cursor at selected option
        if (i == mCursor) {
            Text("*")
                .SetStrokeType(ETextStroke_Outline)
                .SetPosition(x - cursor, y);
        }

        y += row;
    }
}

} // namespace kiwi
