#ifndef LIBKIWI_NET_FIXED_PACKET_FACTORY_H
#define LIBKIWI_NET_FIXED_PACKET_FACTORY_H
#include <libkiwi/debug/kiwiAssert.h>
#include <libkiwi/k_types.h>
#include <libkiwi/net/packet/kiwiIPacketFactory.h>

namespace kiwi {
//! @addtogroup libkiwi_net
//! @{

// Forward declarations
class FixedPacket;
class SockAddrAny;

/**
 * @brief Fixed packet factory
 *
 * @tparam N Fixed packet size
 */
template <u32 N> class FixedPacketFactory : public IPacketFactory {
    /**
     * @brief Creates a new network packet
     *
     * @param pPeerAddr Peer socket address
     */
    virtual FixedPacket* Create(const SockAddrAny* pPeerAddr = nullptr) {
        FixedPacket* pPacket = new FixedPacket(pPeerAddr);
        K_ASSERT_PTR(pPacket);

        pPacket->Alloc(N);
        return pPacket;
    }
};

//! @}
} // namespace kiwi

#endif
