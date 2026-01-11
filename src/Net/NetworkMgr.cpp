#include "Net/NetworkMgr.h"

#include "Net/IMessage.h"
#include "Net/IMessageListener.h"
#include "Net/msg/ConnectMsg.h"
#include "Net/msg/DisconnectMsg.h"
#include "Net/msg/ItemMsg.h"
#include "packets.h"

#include <libkiwi.h>

K_DYNAMIC_SINGLETON_IMPL(AP::Net::NetworkMgr);

namespace AP {
namespace Net {

/**
 * @brief Constructor
 */
NetworkMgr::NetworkMgr() {
    bool success = false;

    // Create server socket
    mpSocket = new kiwi::SyncSocket(SO_PF_INET, SO_SOCK_DGRAM);
    ASSERT_PTR(mpSocket);

    // TODO(kiwi) Can we remove this?
    mpSocket->SetBlocking(false);

    // Create server connection
    mpServer = new kiwi::NetServer(
        mpSocket, new kiwi::VariablePacketFactory<MAX_PACKET_SIZE>());

    ASSERT_PTR(mpServer);

    // Bind to any available local address
    kiwi::SockAddr4 addr(kiwi::port::AP_COMM);
    success = mpServer->Bind(addr);
    ASSERT_EX(success, "Can't bind socket");

    // Register callback to handle PC client packets
    mpServer->SetRecvCallback(PacketCallback, this);

    // Show IP address in the console
    u16 port = addr.port;
    mpSocket->GetHostAddr(addr);
    addr.port = port;

    LOG_EX("NetworkMgr listening on: %s\n", kiwi::ToString(addr).CStr());
}

/**
 * @brief Destructor
 */
NetworkMgr::~NetworkMgr() {
    delete mpServer;
    mpServer = nullptr;

    delete mpSocket;
    mpSocket = nullptr;
}

/**
 * @brief Packet receive callback
 *
 * @param pPacket Incoming packet
 * @param pArg Callback user argument
 */
void NetworkMgr::PacketCallback(kiwi::PacketBase* pPacket, void* pArg) {
    ASSERT_PTR(pPacket);
    ASSERT_PTR(pArg);

    IMessage* pMessage = nullptr;

    // Callback argument is this object
    NetworkMgr* p = static_cast<NetworkMgr*>(pArg);

    const void* pContent = pPacket->GetContent();
    u32 contentSize = pPacket->GetContentSize();
    kiwi::MemStream contentStrm(pContent, contentSize);

    // Every packet's data begins with the common fields
    u8 kind = contentStrm.Read_u8();

    // TODO(kiwi) Struct size is wrong even when byte-packed
    // #define HANDLE_PACKET(NAME)
    //     case IMessage::EKind_##NAME: {
    //         if (contentSize != sizeof(NAME##Packet)) {
    //             LOG_EX("Illegal " #NAME " Packet (want %d bytes, got %d)\n",
    //                    sizeof(ConnectPacket), contentSize);
    //         }
    //
    //         pMessage = new NAME##Msg(contentStrm);
    //         break;
    //     }

#define HANDLE_PACKET(NAME)                                                    \
    case IMessage::EKind_##NAME: {                                             \
        pMessage = new NAME##Msg(contentStrm);                                 \
        break;                                                                 \
    }

    switch (kind) {
        HANDLE_PACKET(Connect);
        HANDLE_PACKET(Disconnect);
        HANDLE_PACKET(Item);

    default: {
        ASSERT_EX(false, "Unknown packet type: %d", kind);
        break;
    }
    }

#undef HANDLE_PACKET

    // Notify listeners
    if (pMessage != nullptr) {
        K_FOREACH (it, p->mListenerList) {
            (*it)->OnMessage(pMessage);
        }
    }
}

} // namespace Net
} // namespace AP