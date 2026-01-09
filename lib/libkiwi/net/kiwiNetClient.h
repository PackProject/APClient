#ifndef LIBKIWI_NET_NET_CLIENT_H
#define LIBKIWI_NET_NET_CLIENT_H
#include <libkiwi/k_types.h>

#include <revolution/SO.h>

namespace kiwi {
//! @addtogroup libkiwi_net
//! @{

// Forward declarations
class IPacket;
class IPacketFactory;
class SocketBase;

/**
 * @brief Network client
 */
class NetClient {
public:
    /**
     * @brief Message receive callback
     *
     * @param pPacket Incoming packet (NULL if error occurred)
     * @param result Socket operation result
     * @param pArg Callback user argument
     */
    typedef void (*RecvCallback)(IPacket* pPacket, SOResult result, void* pArg);

public:
    /**
     * @brief Constructor
     *
     * @param pSocket Network socket
     * @param pPacketFactory Packet factory
     */
    NetClient(SocketBase* pSocket, IPacketFactory* pPacketFactory)
        : mpSocket(pSocket), mpPacketFactory(pPacketFactory) {}

    /**
     * @brief Attempts to receive a message over the network
     */
    IPacket* Recv();

private:
    //! Network socket
    SocketBase* mpSocket;
    //! Packet factory
    IPacketFactory* mpPacketFactory;
};

//! @}
} // namespace kiwi

#endif
