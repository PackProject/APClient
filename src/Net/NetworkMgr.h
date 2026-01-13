#ifndef APCLIENT_NET_NETWORK_MGR_H
#define APCLIENT_NET_NETWORK_MGR_H
#include <types.h>

#include <libkiwi.h>

namespace AP {
namespace Net {

// Forward declarations
class IMessageListener;

/**
 * @brief Archipelago connection
 */
class NetworkMgr : public kiwi::DynamicSingleton<NetworkMgr> {
    friend class kiwi::DynamicSingleton<NetworkMgr>;

public:
    /**
     * @brief Registers a new message listener
     *
     * @param pListener Message listener
     */
    void RegistListener(IMessageListener* pListener) {
        ASSERT_PTR(pListener);
        mListenerList.PushBack(pListener);
    }

private:
    //! Maximum datagram packet size from the PC client
    static const u32 MAX_PACKET_SIZE = 512;

private:
    /**
     * @brief Constructor
     */
    NetworkMgr();

    /**
     * @brief Destructor
     */
    ~NetworkMgr();

    /**
     * @brief Packet receive callback
     *
     * @param pPacket Incoming packet
     * @param pArg Callback user argument
     */
    static void PacketCallback(kiwi::PacketBase* pPacket, void* pArg);

private:
    //! Server socket
    kiwi::SyncSocket* mpSocket;
    //! Server connection
    kiwi::NetServer* mpServer;

    //! PC client socket address
    kiwi::SockAddrAny mPeerAddr;

    //! Registered message listeners
    kiwi::TList<IMessageListener*> mListenerList;
};

} // namespace Net
} // namespace AP

#endif
