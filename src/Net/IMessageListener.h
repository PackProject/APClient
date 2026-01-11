#ifndef APCLIENT_NET_I_MESSAGE_LISTENER_H
#define APCLIENT_NET_I_MESSAGE_LISTENER_H
#include <types.h>

namespace AP {
namespace Net {

// Forward declarations
class IMessage;

/**
 * @brief Network message listener interface
 */
class IMessageListener {
public:
    /**
     * @brief Destructor
     */
    virtual ~IMessageListener() {}

    /**
     * @brief Handles a new network message
     *
     * @param pMessage Network message
     */
    virtual void OnMessage(IMessage* pMessage) = 0;
};

} // namespace Net
} // namespace AP

#endif
