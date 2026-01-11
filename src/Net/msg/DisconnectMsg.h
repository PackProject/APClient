#ifndef APCLIENT_NET_MSG_DISCONNECT_MSG_H
#define APCLIENT_NET_MSG_DISCONNECT_MSG_H
#include <types.h>

#include "Net/IMessage.h"

namespace AP {
namespace Net {

/**
 * @brief PC client disconnection message
 */
class DisconnectMsg : public IMessage {
public:
    /**
     * @brief Constructor
     *
     * @param rStrm Stream to packet content
     */
    DisconnectMsg(kiwi::MemStream& /* rStrm */) {}

    /**
     * @brief Gets the type of this command
     */
    virtual EKind GetKind() const {
        return EKind_Disconnect;
    }
};

} // namespace Net
} // namespace AP

#endif
