#ifndef APCLIENT_CORE_ECHO_SOCKET_H
#define APCLIENT_CORE_ECHO_SOCKET_H
#include <types.h>

#include <libkiwi.h>

namespace AP {

class EchoSocket : public kiwi::DynamicSingleton<EchoSocket> {
    friend class kiwi::DynamicSingleton<EchoSocket>;

private:
    static const u32 MAX_PACKET_SIZE = 256;

private:
    static void SocketCallbackFunc(SOResult result, void* pArg);

    EchoSocket();

private:
    kiwi::SyncSocket* mpSocket;
    u8* mpDataBuffer;
    kiwi::SockAddr4 mPeerAddr;
};

} // namespace AP

#endif
