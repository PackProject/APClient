#include <libkiwi.h>

#include <RPGraphics.h>

namespace kiwi {

/******************************************************************************
 *
 * DebugMenu
 *
 ******************************************************************************/

/**
 * @brief Constructor
 *
 * @param pRootPage Menu root page
 */
DebugMenu::DebugMenu(DebugPage* pRootPage) {
    K_ASSERT(pRootPage != nullptr);
    mPageStack.Push(pRootPage);

    RPGrpRenderer::GetCurrent()->AppendDrawObject(this);
}

/**
 * @brief Updates the menu state
 * @return Result of actions
 */
DebugMenu::EResult DebugMenu::Calculate() {
    if (mPageStack.Empty()) {
        return EResult_None;
    }

    return mPageStack.Top().Calculate();
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
 * @param pOption Debug option
 * @return Success
 */
bool DebugPage::AddOption(DebugOptionBase* pOption) {
    K_ASSERT(pOption != nullptr);

    if (mOptions.Size() >= mMaxOptions) {
        K_LOG_EX("Can't add option: %s\n", pOption->GetName().CStr());
        return false;
    }

    mOptions.PushBack(pOption);
    return true;
}

/**
 * @brief Updates the menu state
 * @return Result of actions
 */
DebugMenu::EResult DebugPage::Calculate() {
    for (int i = 0; i < EPlayer_Max; i++) {
        const WiiCtrl& rCtrl =
            CtrlMgr::GetInstance().GetWiiCtrl(static_cast<EPlayer>(i));

        if (!rCtrl.IsConnected()) {
            continue;
        }

        // Highlight option with Up/Down
        if (rCtrl.IsTrig(EButton_Up)) {
            mCursor = mCursor == 0 ? mOptions.Size() - 1 : mCursor - 1;
            return DebugMenu::EResult_Change;
        } else if (rCtrl.IsTrig(EButton_Down)) {
            mCursor = mCursor == mOptions.Size() - 1 ? 0 : mCursor + 1;
            return DebugMenu::EResult_Change;
        }

        K_ASSERT(0 <= mCursor && mCursor < mOptions.Size());

        DebugOptionBase* pOption = mOptions[mCursor];
        K_ASSERT(pOption != nullptr);

        // Change option with Left/Right
        if (rCtrl.IsTrig(EButton_Right)) {
            pOption->Increment();
            return DebugMenu::EResult_Change;
        } else if (rCtrl.IsTrig(EButton_Left)) {
            pOption->Decrement();
            return DebugMenu::EResult_Change;
        }

        // Select option with A
        if (rCtrl.IsTrig(EButton_A)) {
            pOption->Select();
            return DebugMenu::EResult_Change;
        }

        // Close page with B
        if (rCtrl.IsTrig(EButton_B)) {
            return DebugMenu::EResult_Close;
        }
    }

    return DebugMenu::EResult_None;
}

/**
 * @brief User-level render pass
 */
void DebugPage::UserDraw() {
    f32 x = 0.25f;
    f32 y = 0.20f;
    static const f32 row = 0.05f;

    for (u32 i = 0; i < mOptions.Size(); i++) {
        // clang-format off
        Text(mOptions[i]->GetName())
            .SetPosition(x + 0.00, y + 0.00)
            .SetScale(0.8);

        Text(mOptions[i]->GetValueText())
            .SetPosition(x + 0.15, y + 0.00)
            .SetScale(0.8);
        // clang-format on

        // Show cursor at selected option
        if (i == mCursor) {
            // clang-format off
            Text("*")
                .SetPosition(x - 0.015, y)
                .SetScale(0.8);
            // clang-format on
        }

        y += row;
    }
}

} // namespace kiwi
