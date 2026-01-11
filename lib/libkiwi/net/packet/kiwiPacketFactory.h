#ifndef LIBKIWI_NET_PACKET_FACTORY_H
#define LIBKIWI_NET_PACKET_FACTORY_H
#include <libkiwi/k_types.h>
#include <libkiwi/net/packet/kiwiIPacketFactory.h>

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
    virtual T* Create(const SockAddrAny* pPeerAddr = nullptr) {
        T* pPacket = new T(pPeerAddr);
        K_ASSERT_PTR(pPacket);
        return pPacket;
    }
};

//! @}
} // namespace kiwi

#endif
