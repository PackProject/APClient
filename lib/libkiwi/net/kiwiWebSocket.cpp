#include <libkiwi.h>

namespace kiwi {

/**
 * @brief Connects to a peer
 *
 * @param rAddr Remote address
 * @param pCallback Connection callback
 * @param pArg Callback user argument
 * @return Success
 */
bool SyncWebSocket::Connect(const SockAddrAny& rAddr, Callback pCallback,
                            void* pArg) {
    K_ASSERT(IsOpen());

    // TODO: Is there a better way?
    if (rAddr.len == sizeof(SOSockAddrIn6)) {
        mFamily = SO_PF_INET6;
    }

    bool success = true;

    // Establish TCP connection
    success = success && SyncSocket::Connect(rAddr, pCallback, pArg);
    if (!success) {
        return false;
    }

    // Upgrade connection
    // TODO
    ;

    return success;
}

} // namespace kiwi
