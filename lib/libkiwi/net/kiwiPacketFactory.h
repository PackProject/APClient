#ifndef LIBKIWI_NET_PACKET_FACTORY_H
#define LIBKIWI_NET_PACKET_FACTORY_H
#include <libkiwi/k_types.h>
#include <libkiwi/net/kiwiIPacketFactory.h>

namespace kiwi {
//! @addtogroup libkiwi_net
//! @{

// Forward declarations
class SockAddrAny;

/**
 * @brief Generic packet factory
 *
 * @tparam T Packet class type
 */
template <typename T> class TPacketFactory : public IPacketFactory {
    /**
     * @brief Creates a new network packet
     *
     * @param pPeerAddr Peer socket address
     */
    virtual PacketBase* Create(const SockAddrAny* pPeerAddr = nullptr) {
        return new T(pPeerAddr);
    }
};

//! @}
} // namespace kiwi

#endif
