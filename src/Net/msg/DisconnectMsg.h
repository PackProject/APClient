#ifndef APCLIENT_NET_MSG_DISCONNECT_MSG_H
#define APCLIENT_NET_MSG_DISCONNECT_MSG_H
#include <types.h>

#include "Net/Define.h"

#include <libkiwi.h>

namespace AP {
namespace Net {

/**
 * @brief PC client disconnection message
 */
class DisconnectMsg : public kiwi::ap::IMessage {
public:
    /**
     * @brief Constructor
     *
     * @param rStrm Stream to packet content
     */
    DisconnectMsg(kiwi::MemStream& /* rStrm */) {}

    /**
     * @brief Gets the type of this message
     */
    virtual u32 GetType() const {
        return Define::EMessageType_Disconnect;
    }
};

} // namespace Net
} // namespace AP

#endif
