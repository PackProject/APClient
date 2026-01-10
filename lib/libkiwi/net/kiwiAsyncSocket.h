#ifndef LIBKIWI_NET_ASYNC_SOCKET_H
#define LIBKIWI_NET_ASYNC_SOCKET_H
#include <libkiwi/k_types.h>
#include <libkiwi/net/kiwiAsyncSocketMgr.h>
#include <libkiwi/net/kiwiSocketBase.h>
#include <libkiwi/prim/kiwiList.h>
#include <libkiwi/util/kiwiStateMachine.h>

#include <revolution/OS.h>

namespace kiwi {
//! @addtogroup libkiwi_net
//! @{

// Forward declarations
namespace detail {
class AsyncSocketMgr;
} // namespace detail

/**
 * @brief Asynchronous socket
 */
class AsyncSocket : public SocketBase {
    // Expose Calc only to the manager
    friend class detail::AsyncSocketMgr;

public:
    /**
     * @brief Constructor
     *
     * @param family Socket protocol family
     * @param type Socket type
     */
    AsyncSocket(SOProtoFamily family, SOSockType type)
        : SocketBase(family, type),
          mStateMachine(this, EState_Max, EState_Idle) {

        Init();
    }

    /**
     * @brief Constructor
     *
     * @param socket Socket file descriptor
     * @param type Socket protocol family
     * @param type Socket type
     */
    AsyncSocket(SOSocket socket, SOProtoFamily family, SOSockType type)
        : SocketBase(socket, family, type),
          mStateMachine(this, EState_Max, EState_Idle) {

        Init();
    }

    /**
     * @brief Destructor
     */
    virtual ~AsyncSocket();

    /**
     * @brief Connects to a peer
     *
     * @param rAddr Remote address
     * @param pCallback Connection callback
     * @param pArg Callback user argument
     * @return Success
     */
    virtual bool Connect(const SockAddrAny& rAddr, ConnectCallback pCallback,
                         void* pArg);

    /**
     * @brief Accepts a peer connection over a new socket
     *
     * @param pCallback Acceptance callback
     * @param pArg Callback user argument
     * @return New socket
     */
    virtual AsyncSocket* Accept(AcceptCallback pCallback, void* pArg);

private:
    /**
     * @brief State machine state
     */
    enum EState {
        EState_Idle,    //!< Process send/recv jobs
        EState_Connect, //!< Trying to connect to peer
        EState_Accept,  //!< Trying to accept peer

        EState_Max
    };

    //! Asynchronous job interface
    class IJob;

    //! Asynchronous connect job
    class ConnectJob;
    friend class ConnectJob;

    //! Asynchronous accept job
    class AcceptJob;
    friend class AcceptJob;

    //! Asynchronous receive job
    class RecvJob;
    friend class RecvJob;

    //! Asynchronous send job
    class SendJob;
    friend class SendJob;

private:
    /**
     * @brief Initializes socket state
     */
    void Init();

    /**
     * @brief Updates the socket state
     */
    void Calc() {
        mStateMachine.Calculate();
    }

    /**
     * @brief Updates the packet in the Idle state
     */
    K_STATE_DECL(Idle);

    /**
     * @brief Updates the packet in the Connect state
     */
    K_STATE_DECL(Connect);

    /**
     * @brief Updates the packet in the Accept state
     */
    K_STATE_DECL(Accept);

    /**
     * @brief Receives data and records sender address (internal implementation)
     *
     * @param pDst Destination buffer
     * @param len Buffer size
     * @param[out] rRecv Number of bytes received
     * @param[out] pAddr Sender address
     * @param pCallback Completion callback
     * @param pArg Callback user argument
     * @return Socket library result
     */
    virtual SOResult RecvImpl(void* pDst, u32 len, u32& rRecv,
                              SockAddrAny* pAddr, XferCallback pCallback,
                              void* pArg);

    /**
     * @brief Sends data to specified connection (internal implementation)
     *
     * @param pSrc Source buffer
     * @param len Buffer size
     * @param[out] rSend Number of bytes sent
     * @param pAddr Sender address
     * @param pCallback Completion callback
     * @param pArg Callback user argument
     * @return Socket library result
     */
    virtual SOResult SendImpl(const void* pSrc, u32 len, u32& rSend,
                              const SockAddrAny* pAddr, XferCallback pCallback,
                              void* pArg);

private:
    //! Logic state machine
    StateMachine<AsyncSocket> mStateMachine;

    //! Active connect job
    IJob* mpConnectJob;
    //! Active accept job
    IJob* mpAcceptJob;

    //! Active receive jobs
    TList<IJob*> mRecvJobs;
    //! Active send jobs
    TList<IJob*> mSendJobs;
};

//! @}
} // namespace kiwi

#endif
