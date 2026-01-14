#ifndef APCLIENT_CMN_TEXT_DISPLAY_H
#define APCLIENT_CMN_TEXT_DISPLAY_H
#include <types.h>

#include <Pack/RPGraphics.h>

#include <libkiwi.h>

namespace AP {
namespace Cmn {

/**
 * @brief Message text writer
 */
class TextDisplay : public IRPGrpDrawObject {
public:
    /**
     * @brief Constructor
     */
    TextDisplay();

    /**
     * @brief Handles scene Configure event
     */
    void Configure();

    /**
     * @brief Handles scene Calculate event
     */
    void Calculate() {
        mStateMachine.Calculate();
    }

    /**
     * @brief Handles scene UserDraw event
     */
    void UserDraw();

    /**
     * @brief Adds a text message to the queue
     *
     * @param rText Text message
     */
    void EnqueueText(const kiwi::WString& rText) {
        mTextQueue.PushBack(rText);
    }

private:
    /**
     * @brief State machine state
     */
    enum EState {
        EState_Offline, //!< Waiting for client connection
        EState_Wait,    //!< Waiting for message
        EState_Show,    //!< Show the current message
        EState_Fade,    //!< Fade out the current message

        EState_Max
    };

    //! Time before wrapping the hue of the offline message
    static const u32 OFFLINE_TIMER = 60 * 30;
    //! Time to show the current message before fading away
    static const u32 SHOW_TIMER = 60 * 2;
    //! Time to show the message while fading away
    static const u32 FADE_TIMER = 60 * 1;

private:
    /**
     * @brief Updates the text display in the Offline state
     */
    K_STATE_DECL(Offline);

    /**
     * @brief Updates the text display in the Wait state
     */
    K_STATE_DECL(Wait);

    /**
     * @brief Updates the text display in the Show state
     */
    K_STATE_DECL(Show);

    /**
     * @brief Updates the text display in the Fade state
     */
    K_STATE_DECL(Fade);

    /**
     * @brief Displays the offline state message
     */
    void DrawOfflineMsg() const;

    /**
     * @brief Displays the current text message queue
     */
    void DrawQueue() const;

private:
    //! Logic state machine
    kiwi::StateMachine<TextDisplay> mStateMachine;
    //! Message display timer
    s32 mTimer;

    //! Message text queue
    kiwi::TList<kiwi::WString> mTextQueue;
};

} // namespace Cmn
} // namespace AP

#endif
