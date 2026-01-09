#include "Net/TextDisplay.h"

#include "Net/IMessage.h"
#include "Net/NetworkMgr.h"
#include "Net/msg/PrintMsg.h"
#include <Pack/RPGraphics.h>

#include <libkiwi.h>

K_DYNAMIC_SINGLETON_IMPL(AP::Net::TextDisplay);

namespace AP {
namespace Net {

/**
 * @brief Constructor
 */
TextDisplay::TextDisplay()
    : mStateMachine(this, EState_Max, EState_Wait), mTimer(0) {

    mStateMachine.RegistState(EState_Wait, &TextDisplay::State_Wait_calc);
    mStateMachine.RegistState(EState_Show, &TextDisplay::State_Show_calc);
    mStateMachine.RegistState(EState_Fade, &TextDisplay::State_Fade_calc);

    NetworkMgr::GetInstance().RegistListener(this);
}

/**
 * @brief Handles a new network message
 *
 * @param pMessage Network message
 */
void TextDisplay::OnMessage(IMessage* pMessage) {
    ASSERT_PTR(pMessage);

    // Only interested in Print messages
    if (pMessage->GetKind() != IMessage::EKind_Print) {
        return;
    }

    PrintMsg* pPrintMsg = static_cast<PrintMsg*>(pMessage);

    K_FOREACH (it, pPrintMsg->GetMessageList()) {
        mTextQueue.PushBack(*it);
    }
}

/**
 * @brief Handles scene Configure event
 *
 * @param pScene Current scene
 */
void TextDisplay::OnConfigure(RPSysScene* /* pScene */) {
    RPGrpRenderer* pRenderer = RPGrpRenderer::GetCurrent();

    K_ASSERT_PTR(pRenderer);
    pRenderer->AppendDrawObject(this);
}

/**
 * @brief Handles scene UserDraw event
 */
void TextDisplay::UserDraw() {
    if (mTextQueue.Empty()) {
        return;
    }

    u8 alpha = 255;

    if (mStateMachine.IsState(EState_Fade)) {
        f32 amount = static_cast<f32>(mTimer) / FADE_TIMER;
        alpha *= amount;
    }

    kiwi::Text(mTextQueue.Front())
        .SetPosition(0.10, 0.90)
        .SetScale(0.7)
        .SetTextColor(kiwi::Color::WHITE)
        .SetStrokeType(kiwi::ETextStroke_Outline)
        .SetAlpha(alpha);
}

/**
 * @brief Updates the packet in the Wait state
 */
void TextDisplay::State_Wait_calc() {
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
 * @brief Updates the packet in the Fade state
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

} // namespace Net
} // namespace AP