#include "Cmn/TextDisplay.h"

#include "Net/NetworkMgr.h"
#include <Pack/RPGraphics.h>

#include <libkiwi.h>

#include <climits>

namespace AP {
namespace Cmn {

/**
 * @brief Constructor
 */
TextDisplay::TextDisplay()
    : mStateMachine(this, EState_Max, EState_Offline), mTimer(0) {

    mStateMachine.RegistState(EState_Offline, &TextDisplay::State_Offline_calc);
    mStateMachine.RegistState(EState_Wait, &TextDisplay::State_Wait_calc);
    mStateMachine.RegistState(EState_Show, &TextDisplay::State_Show_calc);
    mStateMachine.RegistState(EState_Fade, &TextDisplay::State_Fade_calc);
}

/**
 * @brief Handles scene Configure event
 */
void TextDisplay::Configure() {
    RPGrpRenderer* pRenderer = RPGrpRenderer::GetCurrent();

    if (pRenderer != nullptr) {
        pRenderer->AppendDrawObject(this);
    }
}

/**
 * @brief Handles scene UserDraw event
 */
void TextDisplay::UserDraw() {
    if (mStateMachine.IsState(EState_Offline)) {
        DrawOfflineMsg();
    } else {
        DrawQueue();
    }
}

/**
 * @brief Updates the text display in the Offline state
 */
void TextDisplay::State_Offline_calc() {
    if (mStateMachine.IsFirstStep()) {
        mTimer = 0;
        return;
    }

    // Client is connected once the peer address is set
    if (Net::NetworkMgr::GetInstance().GetPeerAddr().IsValid()) {
        mTextQueue.PushBack(L"Connected!");
        mStateMachine.ChangeState(EState_Wait);
    }

    mTimer = ++mTimer % OFFLINE_TIMER;
}

/**
 * @brief Updates the text display in the Wait state
 */
void TextDisplay::State_Wait_calc() {
    if (!Net::NetworkMgr::GetInstance().GetPeerAddr().IsValid()) {
        mStateMachine.ChangeState(EState_Offline);
    }

    // Wait for any messages to appear
    if (!mTextQueue.Empty()) {
        mStateMachine.ChangeState(EState_Show);
    }
}

/**
 * @brief Updates the text display in the Show state
 */
void TextDisplay::State_Show_calc() {
    if (mStateMachine.IsFirstStep()) {
        mTimer = SHOW_TIMER;
        return;
    }

    if (--mTimer < 0) {
        mStateMachine.ChangeState(EState_Fade);
    }
}

/**
 * @brief Updates the text display in the Fade state
 */
void TextDisplay::State_Fade_calc() {
    if (mStateMachine.IsFirstStep()) {
        mTimer = FADE_TIMER;
        return;
    }

    if (--mTimer < 0) {
        // Discard the current message
        mTextQueue.PopFront();
        mStateMachine.ChangeState(EState_Wait);
    }
}

/**
 * @brief Displays the offline state message
 */
void TextDisplay::DrawOfflineMsg() const {
    kiwi::SockAddr4 addr = Net::NetworkMgr::GetInstance().GetServerAddr();
    ASSERT(addr.IsValid());

    f32 hue = static_cast<f32>(mTimer) / OFFLINE_TIMER;
    kiwi::Color stroke = kiwi::Color::FromHsv(hue, 0.4f, 1.0f);

    kiwi::Text("Waiting for client... (%s)", kiwi::ToString(addr).CStr())
        .SetPosition(0.10, 0.90)
        .SetTextColor(stroke)
        .SetStrokeType(kiwi::ETextStroke_Outline);
}

/**
 * @brief Displays the current text message queue
 */
void TextDisplay::DrawQueue() const {
    if (mTextQueue.Empty()) {
        return;
    }

    u8 alpha = 0xFF;

    if (mStateMachine.IsState(EState_Fade)) {
        f32 amount = static_cast<f32>(mTimer) / FADE_TIMER;
        alpha *= amount;
    }

    kiwi::Text(mTextQueue.Front())
        .SetPosition(0.10, 0.90)
        .SetTextColor(kiwi::Color::WHITE)
        .SetStrokeType(kiwi::ETextStroke_Outline)
        .SetAlpha(alpha);
}

} // namespace Cmn
} // namespace AP