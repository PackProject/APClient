#include <libkiwi.h>

namespace kiwi {
namespace ap {

/**
 * @brief Constructor
 *
 * @param pParser Message parser
 * @param port Local port
 */
Server::Server(IMessageParser* pParser, u16 port)
    : mpSocket(nullptr), mPort(0), mpConnection(nullptr), mpParser(pParser) {

    K_ASSERT_PTR(mpParser);

    mpSocket = new SyncSocket(SO_PF_INET, SO_SOCK_DGRAM);
    K_ASSERT_PTR(mpSocket);
    mpSocket->SetBlocking(false);

    // Variable packets only enforce an upper size bound
    IPacketFactory* pPacketFactory =
        new VariablePacketFactory<MAX_PACKET_SIZE>();
    K_ASSERT_PTR(pPacketFactory);

    mpConnection = new NetServer(mpSocket, pPacketFactory);
    K_ASSERT_PTR(mpConnection);

    // Bind to any available local address
    SockAddr4 addr(port);
    bool success = mpConnection->Bind(addr);
    ASSERT_EX(success, "Can't bind server socket on port %d", addr.port);
    mPort = addr.port;

    mpConnection->SetRecvCallback(PacketCallback, this);

    // Save server address
    mpSocket->GetHostAddr(mServerAddr);
    mServerAddr.port = mPort;
}

/**
 * @brief Destructor
 */
Server::~Server() {
    delete mpConnection;
    mpConnection = nullptr;

    delete mpSocket;
    mpSocket = nullptr;

    delete mpParser;
    mpParser = nullptr;
}

/**
 * @brief Packet receive callback
 *
 * @param pPacket Incoming packet
 * @param pArg Callback user argument
 */
void Server::PacketCallback(PacketBase* pPacket, void* pArg) {
    K_ASSERT_PTR(pPacket);
    K_ASSERT_PTR(pArg);

    // Callback argument is this object
    Server* p = static_cast<Server*>(pArg);
    K_ASSERT_PTR(p->mpParser);

    K_LOG_EX("[Server] ContentSize: %d\n", pPacket->GetContentSize());

    IMessage* pMessage =
        p->mpParser->Parse(pPacket->GetContent(), pPacket->GetContentSize());

    if (pMessage == nullptr) {
        return;
    }

    // Notify listeners
    K_FOREACH (it, p->mListenerList) {
        K_ASSERT_PTR(*it);
        (*it)->OnReceiveMessage(pMessage);
    }

    // Listener responses
    K_FOREACH (it, p->mListenerList) {
        K_ASSERT_PTR(*it);
        (*it)->OnRespondMessage(pMessage, p->mpConnection);
    }

    // Release message memory
    delete pMessage;
}

} // namespace ap
} // namespace kiwi