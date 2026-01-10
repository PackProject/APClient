#ifndef APCLIENT_CORE_ECHO_SOCKET_H
#define APCLIENT_CORE_ECHO_SOCKET_H
#include <types.h>

#include <libkiwi.h>

namespace AP {

/**
 * @brief Data mirrorer for network testing
 */
class EchoSocket : public kiwi::DynamicSingleton<EchoSocket> {
    friend class kiwi::DynamicSingleton<EchoSocket>;

private:
    /**
     * @brief Constructor
     */
    EchoSocket();

    /**
     * @brief Destructor
     */
    ~EchoSocket();

    /**
     * @brief Packet receive callback
     *
     * @param pPacket Incoming packet
     * @param pArg Callback user argument
     */
    static void PacketCallback(kiwi::PacketBase* pPacket, void* pArg);

private:
    //! Server socket
    kiwi::SyncSocket* mpServerSocket;
    //! Socket connection wrapper
    kiwi::NetServer* mpServer;
};

} // namespace AP

#endif
