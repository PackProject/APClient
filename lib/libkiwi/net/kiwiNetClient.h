#ifndef LIBKIWI_NET_NET_CLIENT_H
#define LIBKIWI_NET_NET_CLIENT_H
#include <libkiwi/k_types.h>
#include <libkiwi/net/kiwiNetConnection.h>

namespace kiwi {
//! @addtogroup libkiwi_net
//! @{

/**
 * @brief Network client
 */
class NetClient : public NetConnection {
public:
    /**
     * @brief Constructor
     *
     * @param pSocket Network socket
     * @param pPacketFactory Packet factory
     */
    NetClient(SocketBase* pSocket, IPacketFactory* pPacketFactory)
        : NetConnection(pSocket, pPacketFactory) {}
};

//! @}
} // namespace kiwi

#endif
