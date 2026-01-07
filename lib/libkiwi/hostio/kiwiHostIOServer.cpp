#include <libkiwi.h>

#include <cstring>

namespace kiwi {
namespace hostio {

K_DYNAMIC_SINGLETON_IMPL(Server);

/**
 * @brief Constructor
 */
Server::Server()
    : mpRootNode(nullptr),
      mpMainThread(nullptr),
      mpServerSocket(nullptr),
      mpClientSocket(nullptr) {

    mpMainThread = new Thread(ThreadFunc, *this);
    K_ASSERT_PTR(mpMainThread);
}

/**
 * @brief Destructor
 */
Server::~Server() {
    mpRootNode = nullptr;

    delete mpMainThread;
    mpMainThread = nullptr;

    CloseServer();

    delete mpClientSocket;
    mpClientSocket = nullptr;
}

/**
 * @brief Initializes the server connection
 */
void Server::RestartServer() {
    // Close any sockets
    if (mpServerSocket != nullptr) {
        CloseServer();
    }

    mpServerSocket = new SyncSocket(SO_PF_INET, SO_SOCK_STREAM);
    K_ASSERT_PTR(mpServerSocket);

    // Default local IP address
    mServerAddr = SockAddr4(port::HOST_IO);

    bool success = mpServerSocket->Bind(mServerAddr);
    K_ASSERT(success);

    success = mpServerSocket->Listen();
    K_ASSERT(success);

    // Host address now has the correct IP
    u16 port = mServerAddr.port;
    mpServerSocket->GetHostAddr(mServerAddr);
    mServerAddr.port = port;
}

/**
 * @brief Closes the server connections
 */
void Server::CloseServer() {
    // Close server socket
    if (mpServerSocket != nullptr) {
        bool success = mpServerSocket->Shutdown(SO_SHUT_RDWR);
        K_ASSERT(success);

        delete mpServerSocket;
        mpServerSocket = nullptr;
    }

    // Close client socket
    if (mpClientSocket != nullptr) {
        bool success = mpClientSocket->Shutdown(SO_SHUT_RDWR);
        K_ASSERT(success);

        delete mpClientSocket;
        mpClientSocket = nullptr;
    }
}

/**
 * @brief Thread function
 */
void Server::ThreadFunc() {
    while (true) {
        RestartServer();
        K_ASSERT_PTR(mpServerSocket);

        K_LOG_EX("Host I/O listening on %s\n",
                 kiwi::ToString(mServerAddr).CStr());

        // Server socket is non-blocking
        do {
            mpClientSocket = mpServerSocket->Accept();
        } while (LibSO::GetLastError() == SO_EWOULDBLOCK);

        K_LOG("Host I/O client connected!\n");

        // Event loop returns on disconnect, which will restart the server
        K_ASSERT_PTR(mpClientSocket);
        EventLoop();
    }
}

/**
 * @brief Event handler loop
 */
void Server::EventLoop() {
    K_ASSERT_PTR(mpClientSocket);

    while (true) {
        // First four bytes specify the event data size
        u32 eventSize = 0;
        Optional<u32> nrecv = mpClientSocket->Recv(eventSize);

        // Connection failure
        if (!nrecv) {
            return;
        }

        // Socket is blocking
        if (*nrecv == 0) {
            continue;
        }

        // Sanity check packet size for corruption
        K_ASSERT(eventSize < MAX_EVENT_BUFFER_SIZE);
        Packet packet(eventSize);

        // Fill event packet data
        while (!packet.IsWriteComplete()) {
            // Optional<u32> nrecv = packet.Recv(*mpClientSocket);

            // if (!nrecv) {
            //     return;
            // }
        }

        // Can't process events without a node tree
        if (mpRootNode == nullptr) {
            continue;
        }

        // Dispatch event to root node so it can propogate
        const Event* pEvent = static_cast<const Event*>(packet.GetContent());
        mpRootNode->OnEvent(pEvent);

        // Root node may have generated a message in response
        const MemStream& rStrm = mMessageContext.GetMessageStream();
        u32 msgSize = rStrm.GetSize();

        // Send it off to the host client
        if (msgSize > 0) {
            Packet packet(msgSize);

            u32 written = packet.Write(rStrm.GetBuffer(), msgSize);
            K_ASSERT(written == msgSize);

            while (!packet.IsReadComplete()) {
                // Optional<u32> nsend = packet.Send(*mpClientSocket);

                // if (!nsend) {
                //     K_ASSERT_EX(false, "Send message error");
                // }
            }
        }
    }
}

} // namespace hostio
} // namespace kiwi