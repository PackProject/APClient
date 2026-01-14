#ifndef APCLIENT_NET_GAME_MESSAGE_LISTENER_H
#define APCLIENT_NET_GAME_MESSAGE_LISTENER_H
#include <types.h>

#include "Net/NetworkMgr.h"

#include <libkiwi.h>

namespace AP {
namespace Net {

/**
 * @brief Archipelago message listener
 */
class GameMessageListener : public kiwi::ap::IMessageListener {
public:
    /**
     * @brief Constructor
     */
    GameMessageListener() {
        NetworkMgr::GetInstance().RegistListener(this);
    }

    /**
     * @brief Destructor
     */
    virtual ~GameMessageListener() {
        NetworkMgr::GetInstance().RemoveListener(this);
    }

    /**
     * @brief Callback for receiving a network message
     *
     * @param pMessage Network message
     */
    virtual void OnReceiveMessage(kiwi::ap::IMessage* pMessage);

    /**
     * @brief Callback for responding to a network message
     *
     * @param pMessage Network message
     * @param pConnection Network connection
     */
    virtual void OnRespondMessage(kiwi::ap::IMessage* pMessage,
                                  kiwi::NetConnection* pConnection);
};

} // namespace Net
} // namespace AP

#endif
