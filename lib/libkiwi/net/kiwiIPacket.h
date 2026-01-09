#ifndef LIBKIWI_NET_I_PACKET_H
#define LIBKIWI_NET_I_PACKET_H
#include <libkiwi/k_types.h>

namespace kiwi {
//! @addtogroup libkiwi_net
//! @{

/**
 * @brief Network packet interface
 */
class IPacket {
public:
    /**
     * @brief Destructor
     */
    virtual ~IPacket() {}
};

//! @}
} // namespace kiwi

#endif
