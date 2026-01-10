#ifndef LIBKIWI_NET_SIZED_PACKET_H
#define LIBKIWI_NET_SIZED_PACKET_H
#include <libkiwi/debug/kiwiAssert.h>
#include <libkiwi/k_types.h>
#include <libkiwi/net/kiwiPacketBase.h>

namespace kiwi {
//! @addtogroup libkiwi_net
//! @{

/**
 * @brief Network packet prepended with its size
 */
class SizedPacket : public PacketBase {
public:
    /**
     * @brief Sized packet header
     */
    struct Header {
        //! Size of the following packet data
        /* 0x00 */ u32 size;
    };

public:
    /**
     * @brief Constructor
     *
     * @param pPeerAddr Peer socket address
     */
    explicit SizedPacket(const SockAddrAny* pPeerAddr = nullptr)
        : PacketBase(pPeerAddr) {}

private:
    /**
     * @brief State machine state
     */
    enum EState {
        EState_Idle,        //!< Waiting for request
        EState_RecvHeader,  //!< Trying to receive packet header
        EState_RecvContent, //!< Trying to receive packet content
        EState_Send,        //!< Trying to send packet

        EState_Max
    };
};

//! @}
} // namespace kiwi

#endif
