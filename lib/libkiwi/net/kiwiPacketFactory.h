#ifndef LIBKIWI_NET_PACKET_FACTORY_H
#define LIBKIWI_NET_PACKET_FACTORY_H
#include <libkiwi/k_types.h>
#include <libkiwi/net/kiwiIPacketFactory.h>

namespace kiwi {
//! @addtogroup libkiwi_net
//! @{

/**
 * @brief Generic packet factory implementation
 *
 * @tparam T Packet class type
 */
template <typename T = Packet> class TPacketFactory : public IPacketFactory {
    /**
     * @brief Creates a new network packet
     */
    virtual Packet* Create() {
        return new T();
    }
};

//! @}
} // namespace kiwi

#endif
