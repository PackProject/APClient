#include "core/EchoSocket.h"

#include <libkiwi.h>

K_DYNAMIC_SINGLETON_IMPL(AP::EchoSocket);

namespace AP {

EchoSocket::EchoSocket() {
    bool success;

    mpSocket = new kiwi::SyncSocket( //
        SO_PF_INET,                  /* ipv4 */
        SO_SOCK_DGRAM                /* udp = datagram*/
    );

    ASSERT_PTR(mpSocket);
    mpSocket->SetBlocking(false);

    // Packet data buffer
    mpDataBuffer = new (kiwi::EMemory_MEM2) u8[MAX_PACKET_SIZE];
    ASSERT_PTR(mpDataBuffer);

    // Bind to any available local address
    kiwi::SockAddr4 addr(kiwi::port::AP_COMM);
    success = mpSocket->Bind(addr);
    ASSERT_EX(success, "Can't bind socket");

    // Host address now has the correct IP
    u16 port = addr.port;
    mpSocket->GetHostAddr(addr);
    addr.port = port;

    kiwi::cout << "Echo socket listening on: " << kiwi::ToString(addr)
               << kiwi::endl;

    for (;;) {
        // Receive packet from the peer
        kiwi::Optional<u32> nrecv =
            mpSocket->RecvBytesFrom(mpDataBuffer, MAX_PACKET_SIZE, mPeerAddr);

        if (!nrecv) {
            ASSERT_EX(false, "Socket error (errcode %d)",
                      kiwi::LibSO::GetLastError());
        }

        if (*nrecv > 0) {
            kiwi::cout << "Received data from " << kiwi::ToString(mPeerAddr)
                       << "(" << *nrecv << " bytes)" << kiwi::endl;

            mpSocket->SendBytesTo(mpDataBuffer, *nrecv, mPeerAddr);
        }
    }
}

} // namespace AP