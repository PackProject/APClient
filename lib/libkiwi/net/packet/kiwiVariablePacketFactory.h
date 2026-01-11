#ifndef LIBKIWI_NET_VARIABLE_PACKET_FACTORY_H
#define LIBKIWI_NET_VARIABLE_PACKET_FACTORY_H
#include <libkiwi/debug/kiwiAssert.h>
#include <libkiwi/k_types.h>
#include <libkiwi/net/packet/kiwiIPacketFactory.h>

namespace kiwi {
//! @addtogroup libkiwi_net
//! @{

// Forward declarations
class VariablePacket;
class SockAddrAny;

/**
 * @brief Variable packet factory
 *
 * @tparam N Variable packet size
 */
template <u32 N> class VariablePacketFactory : public IPacketFactory {
    /**
     * @brief Creates a new network packet
     *
     * @param pPeerAddr Peer socket address
     */
    virtual VariablePacket* Create(const SockAddrAny* pPeerAddr = nullptr) {
        VariablePacket* pPacket = new VariablePacket(pPeerAddr);
        K_ASSERT_PTR(pPacket);

        pPacket->Alloc(N);
        return pPacket;
    }
};

//! @}
} // namespace kiwi

#endif
