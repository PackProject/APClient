#ifndef LIBKIWI_AP_I_AP_MESSAGE_LISTENER_H
#define LIBKIWI_AP_I_AP_MESSAGE_LISTENER_H
#include <libkiwi/k_types.h>

namespace kiwi {
//! @addtogroup libkiwi_fun
//! @{

// Forward declarations
class NetConnection;

namespace ap {
//! @addtogroup libkiwi_fun
//! @{

// Forward declarations
class IMessage;

/**
 * @brief Archipelago message listener interface
 */
class IMessageListener {
public:
    /**
     * @brief Destructor
     */
    virtual ~IMessageListener() {}

    /**
     * @brief Callback for receiving a network message
     *
     * @param pMessage Network message
     */
    virtual void OnReceiveMessage(IMessage* pMessage) = 0;

    /**
     * @brief Callback for responding to a network message
     *
     * @param pMessage Network message
     * @param pConnection Network connection
     */
    virtual void OnRespondMessage(IMessage* pMessage,
                                  NetConnection* pConnection) = 0;
};

//! @}
} // namespace ap
//! @}
} // namespace kiwi

#endif
