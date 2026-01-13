#include "Net/NetworkMgr.h"

#include "Net/IMessage.h"
#include "Net/IMessageListener.h"
#include "Net/msg/ConnectMsg.h"
#include "Net/msg/DisconnectMsg.h"
#include "Net/msg/ItemMsg.h"
#include "Net/msg/LocationMsg.h"
#include "Net/msg/PrintMsg.h"
#include "const.h"

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
    mpServer->SetRecvCallback(PacketCallback);

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

    IMessage* pMessage = nullptr;
    NetworkMgr& r = GetInstance();

    const void* pContent = pPacket->GetContent();
    u32 contentSize = pPacket->GetContentSize();
    kiwi::MemStream contentStrm(pContent, contentSize);

    // Every packet's data begins with the common fields
    u8 kind = contentStrm.Read_u8();

#define HANDLE_PACKET(NAME)                                                    \
    case IMessage::EKind_##NAME: {                                             \
        pMessage = new NAME##Msg(contentStrm);                                 \
        break;                                                                 \
    }

    switch (kind) {
        HANDLE_PACKET(Connect);
        HANDLE_PACKET(Disconnect);
        HANDLE_PACKET(Print);
        HANDLE_PACKET(Item);
        HANDLE_PACKET(Location);

    default: {
        ASSERT_EX(false, "Unknown packet type: %d", kind);
        break;
    }
    }

#undef HANDLE_PACKET

    if (pMessage == nullptr) {
        return;
    }

    // Save client address from connect messages
    if (pMessage->GetKind() == IMessage::EKind_Connect) {
        r.mPeerAddr = static_cast<ConnectMsg*>(pMessage)->GetPeerAddr();
    }

    // Notify listeners
    K_FOREACH (it, r.mListenerList) {
        ASSERT_PTR(*it);
        (*it)->OnMessage(pMessage);
    }

    // TODO(kiwi) Move this somewhere else
    if (r.mPeerAddr.IsValid()) {
        // Location message response
        if (pMessage->GetKind() == IMessage::EKind_Location) {
            kiwi::TVector<u32> checks =
                static_cast<LocationMsg*>(pMessage)->GetChecks();

            if (checks.Empty()) {
                checks.PushBack(CHECK_INVALID);
            }

            r.mpServer->Send(checks.Data(), checks.Size() * sizeof(u32),
                             &r.mPeerAddr);
        }
        // Generic acknowledgement
        else {
            u8 ack = 0xAA;
            r.mpServer->Send(ack, &r.mPeerAddr);
        }
    }

    delete pMessage;
}

} // namespace Net
} // namespace AP