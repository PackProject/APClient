#include <libkiwi.h>

namespace kiwi {

/**
 * @brief Constructor
 *
 * @param pSocket Network socket (not owned by the connection!)
 * @param pPacketFactory Packet factory
 */
NetConnection::NetConnection(SocketBase* pSocket,
                             IPacketFactory* pPacketFactory)
    : mpSocket(pSocket),
      mpPacketFactory(pPacketFactory),
      mpRecvPacket(nullptr),
      mpRecvCallback(nullptr) {

    K_ASSERT_PTR(mpSocket);
    K_ASSERT_PTR(mpPacketFactory);

    detail::NetConnectionMgr::GetInstance().AddConnection(this);
}

/**
 * @brief Destructor
 */
NetConnection::~NetConnection() {
    detail::NetConnectionMgr::GetInstance().RemoveConnection(this);

    // Not owned by the connection
    mpSocket = nullptr;

    delete mpPacketFactory;
    mpPacketFactory = nullptr;

    delete mpRecvPacket;
    mpRecvPacket = nullptr;

    // Release memory for outgoing packets
    for (TList<PacketBase*>::Iterator it = mSendPackets.Begin();
         it != mSendPackets.End();) {

        TList<PacketBase*>::Iterator curr = it++;
        delete &*curr;
    }
}

/**
 * @brief Sends bytes over the connection
 *
 * @param pSrc Source buffer
 * @param size Buffer size
 * @param pPeerAddr Peer address (for datagram connections)
 */
void NetConnection::Send(const void* pSrc, u32 size,
                         const SockAddrAny* pPeerAddr) {
    K_ASSERT_PTR(pSrc);
    K_ASSERT(size > 0);
    K_ASSERT(pPeerAddr == nullptr || pPeerAddr->IsValid());

    K_ASSERT_PTR(mpPacketFactory);
    PacketBase* pSendPacket = mpPacketFactory->Create(pPeerAddr);

    K_ASSERT_PTR(pSendPacket);
    pSendPacket->Alloc(size);
    pSendPacket->SetContent(pSrc, size);

    K_ASSERT_PTR(mpSocket);
    pSendPacket->Send(mpSocket);

    mSendPackets.PushBack(pSendPacket);
}

/**
 * @brief Updates the connection state
 */
void NetConnection::Calc() {
    K_ASSERT_PTR(mpSocket);

    // Packets will not be received until a callback is registered
    if (mpRecvCallback != nullptr) {
        // Always maintain one receive packet
        if (mpRecvPacket == nullptr) {
            K_ASSERT_PTR(mpPacketFactory);
            mpRecvPacket = mpPacketFactory->Create();

            K_ASSERT_PTR(mpRecvPacket);
            mpRecvPacket->Recv(mpSocket);
        }
        // Update receive operation
        else if (mpRecvPacket->Calc()) {
            mpRecvCallback(mpRecvPacket, mpRecvCallbackArg);

            delete mpRecvPacket;
            mpRecvPacket = nullptr;
        }
    }

    // Update next send operation
    if (!mSendPackets.Empty()) {
        PacketBase& rSendPacket = *mSendPackets.Front();

        if (rSendPacket.Calc()) {
            mSendPackets.PopFront();
            delete &rSendPacket;
        }
    }
}

} // namespace kiwi