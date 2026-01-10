#ifndef LIBKIWI_NET_NET_BUFFER_H
#define LIBKIWI_NET_NET_BUFFER_H
#include <libkiwi/debug/kiwiAssert.h>
#include <libkiwi/k_types.h>
#include <libkiwi/prim/kiwiOptional.h>

namespace kiwi {
//! @addtogroup libkiwi_net
//! @{
namespace detail {
//! @addtogroup libkiwi_net
//! @{

/**
 * @brief Network transfer buffer
 */
class NetBuffer {
public:
    /**
     * @brief Socket transfer callback
     *
     * @param size Transfer size
     * @param pArg Callback user argument
     */
    typedef void (*Callback)(u32 size, void* pArg);

public:
    /**
     * @brief Constructor
     */
    NetBuffer() {
        Init();
    }

    /**
     * @brief Constructor
     *
     * @param size Buffer size
     */
    explicit NetBuffer(u32 size);

    /**
     * @brief Destructor
     */
    ~NetBuffer() {
        Free();
    }

    /**
     * @brief Allocates a network buffer of the specified size
     *
     * @param size Buffer size
     */
    void Alloc(u32 size);

    /**
     * @brief Releases the network buffer
     */
    void Free();

    /**
     * @brief Reads data from the network buffer
     *
     * @param pDst Data destination
     * @param size Data size
     *
     * @return Number of bytes read
     */
    u32 Read(void* pDst, u32 size);

    /**
     * @brief Writes data to the network buffer
     *
     * @param pSrc Data source
     * @param size Data size
     *
     * @return Number of bytes written
     */
    u32 Write(const void* pSrc, u32 size);

    /**
     * @brief Receives data into the network buffer
     *
     * @param pSocket Network socket
     * @param[out] pPeerAddr Sender address
     * @param pCallback Socket transfer callback
     * @param pArg Callback user argument
     */
    void Recv(SocketBase* pSocket, SockAddrAny* pPeerAddr,
              Callback pCallback = nullptr, void* pArg = nullptr);

    /**
     * @brief Sends data from the network buffer
     *
     * @param pSocket Network socket
     * @param pPeerAddr Receiver address
     * @param pCallback Socket transfer callback
     * @param pArg Callback user argument
     */
    void Send(SocketBase* pSocket, const SockAddrAny* pPeerAddr,
              Callback pCallback = nullptr, void* pArg = nullptr);

    /**
     * @brief Accesses the underlying buffer data
     */
    const u8* Data() const {
        return mpBuffer;
    }

    /**
     * @brief Gets the number of bytes the buffer can hold
     */
    u32 Capacity() const {
        return mBufferSize;
    }

    /**
     * @brief Gets the number of bytes available to read
     */
    u32 Size() const {
        K_ASSERT(mReadOffset <= mWriteOffset);
        return mWriteOffset - mReadOffset;
    }

private:
    //! Context for asynchronous socket operations
    struct CommandBlock;

private:
    /**
     * @brief Initializes the buffer state
     */
    void Init();

    /**
     * @brief Socket transfer (send/recv) completion callback
     *
     * @param result Socket library result
     * @param size Number of bytes transferred
     * @param pArg User callback argument
     */
    static void SocketXferCallback(SOResult /* result */, u32 size, void* pArg);

private:
    //! Buffer data
    u8* mpBuffer;
    //! Buffer size
    u32 mBufferSize;

    //! Read position
    u32 mReadOffset;
    //! Write position
    u32 mWriteOffset;
};

//! @}
} // namespace detail
//! @}
} // namespace kiwi

#endif
