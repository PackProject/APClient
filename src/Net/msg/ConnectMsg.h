#ifndef APCLIENT_NET_MSG_CONNECT_MSG_H
#define APCLIENT_NET_MSG_CONNECT_MSG_H
#include <types.h>

#include "Net/Define.h"

#include <libkiwi.h>

namespace AP {
namespace Net {

/**
 * @brief PC client connection message
 */
class ConnectMsg : public kiwi::ap::IMessage {
public:
    /**
     * @brief Constructor
     *
     * @param rStrm Stream to packet content
     */
    ConnectMsg(kiwi::MemStream& rStrm);

    /**
     * @brief Gets the type of this message
     */
    virtual u32 GetType() const {
        return Define::EMessageType_Connect;
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
