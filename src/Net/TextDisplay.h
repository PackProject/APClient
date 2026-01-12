#ifndef APCLIENT_NET_TEXT_DISPLAY_H
#define APCLIENT_NET_TEXT_DISPLAY_H
#include <types.h>

#include "Net/IMessageListener.h"
#include <Pack/RPGraphics.h>

#include <libkiwi.h>

namespace AP {
namespace Net {

/**
 * @brief Message text writer
 */
class TextDisplay : public IMessageListener,
                    public kiwi::ISceneHook,
                    public IRPGrpDrawObject,
                    public kiwi::DynamicSingleton<TextDisplay> {

    friend class kiwi::DynamicSingleton<TextDisplay>;

private:
    /**
     * @brief State machine state
     */
    enum EState {
        EState_Wait, //!< Waiting for message
        EState_Show, //!< Show the current message
        EState_Fade, //!< Fade out the current message

        EState_Max
    };

    //! Time to show the current message before fading away
    static const u32 SHOW_TIMER = 120;
    //! Time to show the message while fading away
    static const u32 FADE_TIMER = 60;

private:
    /**
     * @brief Constructor
     */
    TextDisplay();

    /**
     * @brief Handles a new network message
     *
     * @param pMessage Network message
     */
    virtual void OnMessage(IMessage* pMessage);

    /**
     * @brief Handles scene Configure event
     *
     * @param pScene Current scene
     */
    virtual void Configure(RPSysScene* pScene);

    /**
     * @brief Handles scene Calculate event
     *
     * @param pScene Current scene
     */
    virtual void AfterCalculate(RPSysScene* /* pScene */) {
        mStateMachine.Calculate();
    }

    /**
     * @brief Handles scene UserDraw event
     */
    virtual void UserDraw();

    /**
     * @brief Updates the packet in the Wait state
     */
    K_STATE_DECL(Wait);

    /**
     * @brief Updates the text display in the Show state
     */
    K_STATE_DECL(Show);

    /**
     * @brief Updates the packet in the Fade state
     */
    K_STATE_DECL(Fade);

private:
    //! Logic state machine
    kiwi::StateMachine<TextDisplay> mStateMachine;

    //! Message display timer
    s32 mTimer;

    //! Message text queue
    kiwi::TList<kiwi::WString> mTextQueue;
};

} // namespace Net
} // namespace AP

#endif
