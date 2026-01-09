#ifndef APCLIENT_NET_MSG_CONNECT_MSG_H
#define APCLIENT_NET_MSG_CONNECT_MSG_H
#include <types.h>

#include "Net/IMessage.h"

#include <libkiwi.h>

namespace AP {
namespace Net {

/**
 * @brief PC client connection message
 */
class ConnectMsg : public IMessage {
public:
    /**
     * @brief Constructor
     *
     * @param rStrm Stream to packet content
     */
    ConnectMsg(kiwi::MemStream& rStrm);

    /**
     * @brief Gets the type of this command
     */
    virtual EKind GetKind() const {
        return EKind_Connect;
    }

    /**
     * @brief Accesses the peer socket address
     */
    const kiwi::SockAddr4& GetPeerAddr() const {
        return mPeerAddr;
    }

private:
    //! Peer socket address
    kiwi::SockAddr4 mPeerAddr;
};

} // namespace Net
} // namespace AP

#endif
