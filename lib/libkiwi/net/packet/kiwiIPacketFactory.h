#ifndef LIBKIWI_NET_I_PACKET_FACTORY_H
#define LIBKIWI_NET_I_PACKET_FACTORY_H
#include <libkiwi/k_types.h>

namespace kiwi {
//! @addtogroup libkiwi_net
//! @{

// Forward declarations
class PacketBase;

/**
 * @brief Packet factory interface
 */
class IPacketFactory {
public:
    /**
     * @brief Destructor
     */
    virtual ~IPacketFactory() {}

    /**
     * @brief Creates a new network packet
     *
     * @param pPeerAddr Peer socket address
     */
    virtual PacketBase* Create(const SockAddrAny* pPeerAddr = nullptr) = 0;
};

//! @}
} // namespace kiwi

#endif
