#ifndef LIBKIWI_NET_NET_CONNECTION_H
#define LIBKIWI_NET_NET_CONNECTION_H
#include <libkiwi/debug/kiwiAssert.h>
#include <libkiwi/k_types.h>

namespace kiwi {
//! @addtogroup libkiwi_net
//! @{

// Forward declarations
class IPacketFactory;
class PacketBase;
class SockAddrAny;
class SocketBase;

// Forward declarations
namespace detail {
class NetConnectionMgr;
} // namespace detail

/**
 * @brief Network socket connection wrapper
 */
class NetConnection {
    // Expose Calc only to the manager
    friend class detail::NetConnectionMgr;

public:
    /**
     * @brief Packet receive callback
     *
     * @param pPacket Incoming packet
     * @param pArg Callback user argument
     */
    typedef void (*RecvCallback)(PacketBase* pPacket, void* pArg);

public:
    /**
     * @brief Constructor
     *
     * @param pSocket Network socket (not owned by the connection!)
     * @param pPacketFactory Packet factory
     */
    NetConnection(SocketBase* pSocket, IPacketFactory* pPacketFactory);

    /**
     * @brief Destructor
     */
    virtual ~NetConnection();

    /**
     * @brief Binds socket to local address
     * @note Bind to port zero for a random port (written out)
     *
     * @param rAddr[in,out] Local address
     * @return Success
     */
    bool Bind(SockAddrAny& rAddr) {
        K_ASSERT_PTR(mpSocket);
        return mpSocket->Bind(rAddr);
    }

    /**
     * @brief Sends bytes over the connection
     *
     * @param pSrc Source buffer
     * @param size Buffer size
     * @param pPeerAddr Peer address (for datagram connections)
     */
    void Send(const void* pSrc, u32 size,
              const SockAddrAny* pPeerAddr = nullptr);

    /**
     * @brief Sends an object over the connection
     *
     * @tparam T Object type
     * @param rSrc Source object
     * @param pPeerAddr Peer address (for datagram connections)
     */
    template <typename T>
    void Send(const T& rSrc, const SockAddrAny* pPeerAddr = nullptr) {
        Send(&rSrc, sizeof(T), pPeerAddr);
    }

    /**
     * @brief Sets the packet factory used for this connection
     *
     * @param pPacketFactory New packet factory
     */
    void SetPacketFactory(IPacketFactory* pPacketFactory) {
        K_ASSERT_PTR(pPacketFactory);
        mpPacketFactory = pPacketFactory;
    }

    /**
     * @brief Sets the callback used to handle incoming packets
     *
     * @param pCallback Packet receive callback
     * @param pArg Callback user argument
     */
    void SetRecvCallback(RecvCallback pCallback, void* pArg = nullptr) {
        K_ASSERT_PTR(pCallback);
        mpRecvCallback = pCallback;
        mpRecvCallbackArg = pArg;
    }

protected:
    //! Network socket (not owning!)
    SocketBase* mpSocket;
    //! Packet factory
    IPacketFactory* mpPacketFactory;

    //! Incoming packet
    PacketBase* mpRecvPacket;
    //! Outgoing packets
    TList<PacketBase*> mSendPackets;

    //! Incoming packet callback
    RecvCallback mpRecvCallback;
    //! Callback user argument
    void* mpRecvCallbackArg;

private:
    /**
     * @brief Updates the connection state
     */
    void Calc();
};

//! @}
} // namespace kiwi

#endif
