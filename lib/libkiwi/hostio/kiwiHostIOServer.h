#ifndef LIBKIWI_HOSTIO_HOST_IO_SERVER_H
#define LIBKIWI_HOSTIO_HOST_IO_SERVER_H
#include <libkiwi/core/kiwiThread.h>
#include <libkiwi/hostio/kiwiHostIOContext.h>
#include <libkiwi/k_types.h>
#include <libkiwi/net/kiwiSyncSocket.h>
#include <libkiwi/support/kiwiLibSO.h>
#include <libkiwi/util/kiwiDynamicSingleton.h>

#include <revolution/OS.h>

namespace kiwi {
//! @addtogroup libkiwi_hostio
//! @{
namespace hostio {
//! @addtogroup libkiwi_hostio
//! @{

//! Forward declarations
class Reflexible;

/**
 * @brief Host I/O server
 */
class Server : public DynamicSingleton<Server> {
    friend class DynamicSingleton<Server>;

public:
    /**
     * @brief Sets the root tree node
     *
     * @param rNode New root node
     */
    void SetRootNode(Reflexible& rNode) {
        mpRootNode = &rNode;
    }

    /**
     * @brief Accesses the server's IP address
     */
    const SockAddr4& GetServerAddr() const {
        return mServerAddr;
    }

    /**
     * @brief Accesses the message data context
     */
    Context& GetMessageContext() {
        return mMessageContext;
    }

private:
    /**
     * @brief Constructor
     */
    Server();

    /**
     * @brief Destructor
     */
    virtual ~Server();

    /**
     * @brief Initializes the server connection
     */
    void RestartServer();

    /**
     * @brief Closes the server connections
     */
    void CloseServer();

    /**
     * @brief Thread function
     */
    void ThreadFunc();

    /**
     * @brief Event handler loop
     */
    void EventLoop();

private:
    //! Maximum event buffer size
    static const u32 MAX_EVENT_BUFFER_SIZE = K_MEM_KB_TO_B(4);

private:
    //! Tree root node (not owning!!!)
    Reflexible* mpRootNode;

    //! Main loop thread
    Thread* mpMainThread;

    //! Server socket
    SyncSocket* mpServerSocket;
    //! Server address
    SockAddr4 mServerAddr;

    //! Client (peer) socket
    SyncSocket* mpClientSocket;

    //! Message context
    Context mMessageContext;
};

//! @}
} // namespace hostio
//! @}
} // namespace kiwi

#endif
