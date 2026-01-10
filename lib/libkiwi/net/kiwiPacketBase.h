#ifndef LIBKIWI_NET_PACKET_BASE_H
#define LIBKIWI_NET_PACKET_BASE_H
#include <libkiwi/k_types.h>
#include <libkiwi/net/kiwiNetBuffer.h>

namespace kiwi {
//! @addtogroup libkiwi_net
//! @{

// Forward declarations
class SockAddrAny;

/**
 * @brief Base class for network packet implementations
 */
class PacketBase {
public:
    /**
     * @brief Constructor
     *
     * @param pPeerAddr Peer socket address
     */
    explicit PacketBase(const SockAddrAny* pPeerAddr = nullptr);

    /**
     * @brief Destructor
     */
    virtual ~PacketBase() {
        Free();
    }

    /**
     * @brief Allocates a packet buffer of the specified size
     *
     * @param size Packet size
     */
    void Alloc(u32 size);

    /**
     * @brief Gets the size of the overhead needed for the packet header
     */
    virtual u32 GetOverhead() const = 0;

    /**
     * @brief Gets the current capacity of the packet buffer
     */
    virtual u32 GetSize() const {
        return mBuffer.Capacity();
    }
    /**
     * @brief Gets the maximum capacity of the packet buffer
     */
    virtual u32 GetMaxSize() const {
        return ULONG_MAX;
    }

    /**
     * @brief Gets the current capacity of the packet content
     */
    virtual u32 GetContentSize() const {
        return GetSize() - GetOverhead();
    }
    /**
     * @brief Gets the maximum capacity of the packet content
     */
    virtual u32 GetMaxContent() const {
        return GetMaxSize() - GetOverhead();
    }

    /**
     * @brief Accesses the packet content
     */
    virtual const void* GetContent() const {
        return mBuffer.Data() + GetOverhead();
    }

    /**
     * @brief Sets the packet content
     *
     * @param pContent Packet content
     * @param size Content size
     */
    virtual void SetContent(const void* pContent, u32 size) = 0;

    /**
     * @brief Receives the packet over the specified socket
     *
     * @param pSocket Network socket
     */
    virtual void Recv(SocketBase* pSocket) = 0;

    /**
     * @brief Sends the packet over the specified socket
     *
     * @param pSocket Network socket
     */
    virtual void Send(SocketBase* pSocket) = 0;

    /**
     * @brief Updates the packet state
     *
     * @return Whether the previous operation has just completed
     */
    virtual bool Calc() = 0;

    /**
     * @brief Reads data from the packet
     *
     * @param pDst Data destination
     * @param size Data size
     *
     * @return Number of bytes read
     */
    u32 Read(void* pDst, u32 size);

    /**
     * @brief Writes data to the packet
     *
     * @param pSrc Data source
     * @param size Data size
     *
     * @return Number of bytes written
     */
    u32 Write(const void* pSrc, u32 size);

    /**
     * @brief Accesses the peer socket address
     */
    const SockAddrAny& GetPeerAddr() const {
        return mPeerAddr;
    }

protected:
    /**
     * @brief Releases the packet buffer
     */
    void Free();

protected:
    //! Packet data ring buffer
    detail::NetBuffer mBuffer;
    //! Buffer access mutex
    Mutex mBufferMutex;

    //! Peer socket address
    SockAddrAny mPeerAddr;
};

//! @}
} // namespace kiwi

#endif
