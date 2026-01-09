#ifndef LIBKIWI_NET_SIZED_PACKET_H
#define LIBKIWI_NET_SIZED_PACKET_H
#include <libkiwi/debug/kiwiAssert.h>
#include <libkiwi/k_types.h>
#include <libkiwi/net/kiwiPacket.h>

namespace kiwi {
//! @addtogroup libkiwi_net
//! @{

/**
 * @brief Network packet with its size prepended
 */
class SizedPacket : public Packet {
public:
    /**
     * @brief Sized packet header
     */
    struct Header {
        //! Size of the following packet data
        /* 0x00 */ u32 size;
    };

public:
    //! Message buffer limit to stay under MTU
    static const u16 MAX_BUFFER_SIZE = 1000;
    //! Message content limit
    static const u16 MAX_CONTENT_SIZE = MAX_BUFFER_SIZE - sizeof(Header);

public:
    /**
     * @brief Constructor
     *
     * @param pAddr Packet recipient
     */
    SizedPacket(const SockAddrAny* pAddr = nullptr)
        : Packet(sizeof(Header), pAddr) {}

    /**
     * @brief Allocates message buffer of the specified size
     *
     * @param size Packet size
     */
    virtual void Alloc(u32 size);

    /**
     * @brief Accesses the protocol header
     */
    Header& GetHeader() {
        K_ASSERT_PTR(mpBuffer);
        return *reinterpret_cast<Header*>(mpBuffer);
    }
    /**
     * @brief Accesses the protocol header (read-only)
     */
    const Header& GetHeader() const {
        K_ASSERT_PTR(mpBuffer);
        return *reinterpret_cast<Header*>(mpBuffer);
    }

    /**
     * @brief Gets the maximum size of the message buffer
     */
    virtual u32 GetMaxBuffer() const {
        return MAX_BUFFER_SIZE;
    }

    /**
     * @brief Gets the current size of the message payload
     */
    virtual u32 GetContentSize() const {
        return GetHeader().size;
    }
    /**
     * @brief Gets the maximum size of the message payload
     */
    virtual u32 GetMaxContent() const {
        return MAX_CONTENT_SIZE;
    }

    /**
     * @brief Gets the size of the message buffer overhead
     */
    virtual u32 GetOverhead() const {
        return sizeof(Header);
    }
};

//! @}
} // namespace kiwi

#endif
