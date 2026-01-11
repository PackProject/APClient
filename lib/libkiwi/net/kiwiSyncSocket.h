#ifndef LIBKIWI_NET_SYNC_SOCKET_H
#define LIBKIWI_NET_SYNC_SOCKET_H
#include <libkiwi/k_types.h>
#include <libkiwi/net/kiwiSocketBase.h>

namespace kiwi {
//! @addtogroup libkiwi_net
//! @{

/**
 * @brief Synchronous socket
 */
class SyncSocket : public SocketBase {
public:
    /**
     * @brief Constructor
     *
     * @param family Socket protocol family
     * @param type Socket type
     */
    SyncSocket(SOProtoFamily family, SOSockType type)
        : SocketBase(family, type), mIsBlocking(true) {}

    /**
     * @brief Constructor
     *
     * @param socket Socket descriptor
     * @param family Socket protocol family
     * @param type Socket type
     */
    SyncSocket(SOSocket socket, SOProtoFamily family, SOSockType type)
        : SocketBase(socket, family, type) {}

    /**
     * @brief Connects to a peer
     *
     * @param rAddr Remote address
     * @param pCallback Connection callback
     * @param pArg Callback user argument
     * @return Success
     */
    virtual bool Connect(const SockAddrAny& rAddr,
                         ConnectCallback pCallback = nullptr,
                         void* pArg = nullptr);

    /**
     * @brief Accepts a peer connection over a new socket
     *
     * @param pCallback Acceptance callback
     * @param pArg Callback user argument
     * @return New socket
     */
    virtual SyncSocket* Accept(AcceptCallback pCallback = nullptr,
                               void* pArg = nullptr);

    /**
     * @brief Tests whether the socket is thread-blocking (at the PPC level)
     */
    bool IsBlocking() const {
        return mIsBlocking;
    }
    /**
     * @brief Toggles socket thread-blocking (at the PPC level)
     *
     * @param enable Whether to enable blocking
     */
    void SetBlocking(bool enable) {
        mIsBlocking = enable;
    }

private:
    /**
     * @brief Receives data and records sender address (internal implementation)
     *
     * @param pDst Destination buffer
     * @param len Buffer size
     * @param[out] rRecv Number of bytes received
     * @param[out] pAddr Sender address
     * @param pCallback Completion callback
     * @param pArg Callback user argument
     * @return Socket library result
     */
    virtual SOResult RecvImpl(void* pDst, u32 len, u32& rRecv,
                              SockAddrAny* pAddr, XferCallback pCallback,
                              void* pArg);

    /**
     * @brief Sends data to specified connection (internal implementation)
     *
     * @param pSrc Source buffer
     * @param len Buffer size
     * @param[out] rSend Number of bytes sent
     * @param pAddr Sender address
     * @param pCallback Completion callback
     * @param pArg Callback user argument
     * @return Socket library result
     */
    virtual SOResult SendImpl(const void* pSrc, u32 len, u32& rSend,
                              const SockAddrAny* pAddr, XferCallback pCallback,
                              void* pArg);

private:
    //! Whether socket operations are thread-blocking (at the PPC level)
    bool mIsBlocking;
};

//! @}
} // namespace kiwi

#endif
