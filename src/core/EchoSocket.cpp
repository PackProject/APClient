#include "core/EchoSocket.h"

#include <libkiwi.h>

K_DYNAMIC_SINGLETON_IMPL(AP::EchoSocket);

namespace AP {

/**
 * @brief Constructor
 */
EchoSocket::EchoSocket() {
    bool success;

    // Create server socket
    mpServerSocket = new kiwi::SyncSocket( //
        SO_PF_INET,                        /* ipv4 */
        SO_SOCK_DGRAM                      /* udp = datagram */
    );
    ASSERT_PTR(mpServerSocket);

    // Bind to any available local address
    kiwi::SockAddr4 addr(kiwi::port::AP_COMM);
    success = mpServerSocket->Bind(addr);
    ASSERT_EX(success, "Can't bind socket");

    // Create server connection
    mpServer = new kiwi::NetServer(mpServerSocket,
                                   new kiwi::TPacketFactory<kiwi::RawPacket>());
    ASSERT_PTR(mpServer);

    mpServer->SetRecvCallback(PacketCallback, this);

    // Show IP address in the console
    u16 port = addr.port;
    mpServerSocket->GetHostAddr(addr);
    addr.port = port;

    kiwi::cout << "Echo socket listening on: " << kiwi::ToString(addr)
               << kiwi::endl;
}

/**
 * @brief Destructor
 */
EchoSocket::~EchoSocket() {
    delete mpServer;
    mpServer = nullptr;

    delete mpServerSocket;
    mpServerSocket = nullptr;
}

/**
 * @brief Packet receive callback
 *
 * @param pPacket Incoming packet
 * @param pArg Callback user argument
 */
void EchoSocket::PacketCallback(kiwi::PacketBase* pPacket, void* /* pArg */) {
    K_ASSERT_PTR(pPacket);

    kiwi::cout << "Received " << pPacket->GetContentSize() << " bytes from "
               << kiwi::ToString(pPacket->GetPeerAddr()) << kiwi::endl;
}

} // namespace AP