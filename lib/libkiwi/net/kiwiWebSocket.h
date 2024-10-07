#ifndef LIBKIWI_NET_WEB_SOCKET_H
#define LIBKIWI_NET_WEB_SOCKET_H
#include <libkiwi/k_types.h>
#include <libkiwi/net/kiwiAsyncSocket.h>
#include <libkiwi/net/kiwiSyncSocket.h>
#include <libkiwi/prim/kiwiString.h>

namespace kiwi {
//! @addtogroup libkiwi_net
//! @{

/**
 * @brief Synchronous web socket
 */
class SyncWebSocket : public SyncSocket {
public:
    /**
     * @brief Constructor
     */
    SyncWebSocket() : SyncSocket(SO_PF_INET, SO_SOCK_STREAM) {}

    /**
     * @brief Connects to a peer
     *
     * @param rAddr Remote address
     * @param pCallback Connection callback
     * @param pArg Callback user argument
     * @return Success
     */
    virtual bool Connect(const SockAddrAny& rAddr, Callback pCallback = nullptr,
                         void* pArg = nullptr);
};

/**
 * @brief Asynchronous web socket
 */
class AsyncWebSocket : public AsyncSocket {};

//! @}
} // namespace kiwi

#endif