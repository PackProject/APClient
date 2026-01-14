#ifndef LIBKIWI_AP_AP_SERVER_H
#define LIBKIWI_AP_AP_SERVER_H
#include <libkiwi/k_types.h>
#include <libkiwi/net/kiwiPortRegistry.h>
#include <libkiwi/prim/kiwiList.h>
#include <libkiwi/prim/kiwiOptional.h>
#include <libkiwi/support/kiwiLibSO.h>

namespace kiwi {
//! @addtogroup libkiwi_fun
//! @{

// Forward declarations
class NetServer;
class PacketBase;
class SockAddrAny;
class SyncSocket;

namespace ap {
//! @addtogroup libkiwi_fun
//! @{

// Forward declarations
class IMessageListener;
class IMessageParser;

/**
 * @brief Archipelago server
 */
class Server {
public:
    /**
     * @brief Constructor
     *
     * @param pParser Message parser (owned by this server)
     * @param port Local port
     */
    Server(IMessageParser* pParser, u16 port = port::AP_COMM);

    /**
     * @brief Destructor
     */
    virtual ~Server();

    /**
     * @brief Registers a new message listener
     *
     * @param pListener Message listener
     */
    void RegistListener(IMessageListener* pListener) {
        K_ASSERT_PTR(pListener);
        mListenerList.PushBack(pListener);
    }

    /**
     * @brief Removes a message listener
     *
     * @param pListener Message listener
     */
    void RemoveListener(IMessageListener* pListener) {
        mListenerList.Remove(pListener);
    }

    /**
     * @brief Gets the local address of the server
     */
    const SockAddr4& GetServerAddr() const {
        return mServerAddr;
    }

    /**
     * @brief Gets the connection peer address
     */
    const SockAddrAny& GetPeerAddr() const {
        return mPeerAddr;
    }

    /**
     * @brief Sets the connection peer address
     *
     * @param rAddr Peer address
     */
    void SetPeerAddr(const SockAddrAny& rAddr) {
        K_ASSERT(rAddr.IsValid());
        mPeerAddr = rAddr;
    }

    /**
     * @brief Clears the connection peer address
     */
    void ResetPeerAddr() {
        mPeerAddr = SockAddrAny();
    }

private:
    //! Maximum datagram packet size from the PC client
    static const u32 MAX_PACKET_SIZE = 512;

private:
    /**
     * @brief Packet receive callback
     *
     * @param pPacket Incoming packet
     * @param pArg Callback user argument
     */
    static void PacketCallback(PacketBase* pPacket, void* pArg);

private:
    //! Server socket
    SyncSocket* mpSocket;
    //! Server socket port
    u16 mPort;
    //! Server connection
    NetServer* mpConnection;

    //! Server socket address
    SockAddr4 mServerAddr;
    //! Client socket address
    SockAddrAny mPeerAddr;

    //! Message parser (owning view)
    IMessageParser* mpParser;
    //! Registered message listeners
    TList<IMessageListener*> mListenerList;
};

//! @}
} // namespace ap
//! @}
} // namespace kiwi

#endif
