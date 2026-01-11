#include <libkiwi.h>

namespace kiwi {

/******************************************************************************
 *
 * IJob
 *
 ******************************************************************************/

/**
 * @brief Asynchronous job interface
 */
class AsyncSocket::IJob {
public:
    /**
     * @brief Destructor
     */
    virtual ~IJob() {}

    /**
     * @brief Updates the job state
     *
     * @return Whether the job has completed
     */
    virtual bool Calc() = 0;
};

/******************************************************************************
 *
 * ConnectJob
 *
 ******************************************************************************/

/**
 * @brief Asynchronous connect job
 */
class AsyncSocket::ConnectJob : public IJob {
public:
    /**
     * @brief Constructor
     *
     * @param pAsyncSocket Parent socket
     * @param pPeerAddr Peer address
     * @param pCallback Connect callback
     * @param pArg Callback user argument
     */
    ConnectJob(AsyncSocket* pAsyncSocket, const SockAddrAny& rPeerAddr,
               ConnectCallback pCallback, void* pArg)
        : mpSocket(nullptr),
          mPeerAddr(rPeerAddr),
          mpCallback(pCallback),
          mpArg(pArg) {

        K_ASSERT_PTR(pAsyncSocket);
        K_ASSERT_PTR(mpCallback);
        K_ASSERT(mPeerAddr.IsValid());

        // Need synchronous socket for internal communication
        mpSocket = new SyncSocket(pAsyncSocket->mHandle, pAsyncSocket->mFamily,
                                  pAsyncSocket->mType);
        K_ASSERT_PTR(mpSocket);

        mpSocket->SetBlocking(false);
    }

    /**
     * @brief Destructor
     */
    virtual ~ConnectJob() {
        delete mpSocket;
        mpSocket = nullptr;
    }

    /**
     * @brief Updates the job state
     *
     * @return Whether the job has completed
     */
    virtual bool Calc() {
        K_ASSERT_PTR(mpSocket);
        K_ASSERT(mPeerAddr.IsValid());

        bool success = mpSocket->Connect(mPeerAddr);
        SOResult result = LibSO::GetLastError();

        // Blocking, try again later
        if (result == SO_EWOULDBLOCK) {
            return false;
        }

        K_ASSERT_PTR(mpCallback);
        mpCallback(result, mpArg);

        // Terminate job regardless of success
        return true;
    }

private:
    //! Temporary socket for synchronous communication
    SyncSocket* mpSocket;
    //! Target peer address
    SockAddrAny mPeerAddr;

    //! Connect callback
    ConnectCallback mpCallback;
    //! Callback user argument
    void* mpArg;
};

/******************************************************************************
 *
 * AcceptJob
 *
 ******************************************************************************/

/**
 * @brief Asynchronous accept job
 */
class AsyncSocket::AcceptJob : public IJob {
public:
    /**
     * @brief Constructor
     *
     * @param pAsyncSocket Parent socket
     * @param pSrc Source buffer
     * @param len Buffer size
     * @param pCallback Transfer callback
     * @param pArg Callback user argument
     */
    AcceptJob(AsyncSocket* pAsyncSocket, AcceptCallback pCallback, void* pArg)
        : mpSocket(nullptr), mpCallback(pCallback), mpArg(pArg) {

        K_ASSERT_PTR(pAsyncSocket);
        K_ASSERT_PTR(mpCallback);

        // Need synchronous socket for internal communication
        mpSocket = new SyncSocket(pAsyncSocket->mHandle, pAsyncSocket->mFamily,
                                  pAsyncSocket->mType);
        K_ASSERT_PTR(mpSocket);
    }

    /**
     * @brief Destructor
     */
    virtual ~AcceptJob() {
        delete mpSocket;
        mpSocket = nullptr;
    }

    /**
     * @brief Updates the job state
     *
     * @return Whether the job has completed
     */
    virtual bool Calc() {
        K_ASSERT_PTR(mpSocket);

        SocketBase* pPeerSocket = mpSocket->Accept();
        SOResult result = LibSO::GetLastError();

        // Blocking, try again later
        if (result == SO_EWOULDBLOCK) {
            return false;
        }

        // TODO(kiwi) Can we get this through the callback?
        SockAddrAny addr;
        if (pPeerSocket != nullptr) {
            bool success = mpSocket->GetPeerAddr(addr);
            K_ASSERT(success);
        }

        K_ASSERT_PTR(mpCallback);
        mpCallback(result, pPeerSocket, addr, mpArg);

        // Terminate job regardless of success
        return true;
    }

private:
    //! Temporary socket for synchronous communication
    SyncSocket* mpSocket;

    //! Accept callback
    AcceptCallback mpCallback;
    //! Callback user argument
    void* mpArg;
};

/******************************************************************************
 *
 * RecvJob
 *
 ******************************************************************************/

/**
 * @brief Asynchronous receive job
 */
class AsyncSocket::RecvJob : public IJob {
public:
    /**
     * @brief Constructor
     *
     * @param pAsyncSocket Parent socket
     * @param pDst Destination buffer
     * @param len Buffer size
     * @param[out] pPeerAddr Peer address
     * @param pCallback Transfer callback
     * @param pArg Callback user argument
     */
    RecvJob(AsyncSocket* pAsyncSocket, void* pDst, u32 len,
            SockAddrAny* pPeerAddr, XferCallback pCallback, void* pArg)
        : mpSocket(nullptr),
          mpPacket(nullptr),
          mpDst(pDst),
          mpPeerAddr(pPeerAddr),
          mpCallback(pCallback),
          mpArg(pArg) {

        K_ASSERT_PTR(pAsyncSocket);
        K_ASSERT_PTR(mpDst);
        K_ASSERT(!PtrUtil::IsStack(mpDst));
        K_ASSERT(mpPeerAddr == nullptr || !PtrUtil::IsStack(mpPeerAddr));
        K_ASSERT_PTR(mpCallback);

        // Need synchronous socket for internal communication
        mpSocket = new SyncSocket(pAsyncSocket->mHandle, pAsyncSocket->mFamily,
                                  pAsyncSocket->mType);
        K_ASSERT_PTR(mpSocket);

        mpPacket = new FixedPacket();
        mpPacket->Alloc(len);
        mpPacket->Recv(mpSocket);
    }

    /**
     * @brief Destructor
     */
    virtual ~RecvJob() {
        delete mpSocket;
        mpSocket = nullptr;

        delete mpPacket;
        mpPacket = nullptr;
    }

    /**
     * @brief Updates the job state
     *
     * @return Whether the job has completed
     */
    virtual bool Calc() {
        K_ASSERT_PTR(mpPacket);

        bool finish = mpPacket->Calc();
        SOResult result = LibSO::GetLastError();

        if (finish) {
            std::memcpy(mpDst, mpPacket->GetContent(),
                        mpPacket->GetContentSize());

            if (mpPeerAddr != nullptr) {
                *mpPeerAddr = mpPacket->GetPeerAddr();
            }

            K_ASSERT_PTR(mpCallback);
            mpCallback(result, mpPacket->GetContentSize(), mpArg);
        }

        return finish;
    }

private:
    //! Temporary socket for synchronous communication
    SyncSocket* mpSocket;
    //! Raw data packet
    FixedPacket* mpPacket;

    //! Destination buffer
    void* mpDst;
    //! Destination for peer address
    SockAddrAny* mpPeerAddr;

    //! Transfer callback
    XferCallback mpCallback;
    //! Callback user argument
    void* mpArg;
};

/******************************************************************************
 *
 * SendJob
 *
 ******************************************************************************/

/**
 * @brief Asynchronous send job
 */
class AsyncSocket::SendJob : public IJob {
public:
    /**
     * @brief Constructor
     *
     * @param pAsyncSocket Parent socket
     * @param pSrc Source buffer
     * @param len Buffer size
     * @param pPeerAddr Peer address
     * @param pCallback Transfer callback
     * @param pArg Callback user argument
     */
    SendJob(AsyncSocket* pAsyncSocket, const void* pSrc, u32 len,
            const SockAddrAny* pPeerAddr, XferCallback pCallback = nullptr,
            void* pArg = nullptr)
        : mpSocket(nullptr),
          mpPacket(nullptr),
          mpCallback(pCallback),
          mpArg(pArg) {

        K_ASSERT_PTR(pAsyncSocket);
        K_ASSERT_PTR(pSrc);
        K_ASSERT(!PtrUtil::IsStack(pSrc));
        K_ASSERT_PTR(mpCallback);

        // Need synchronous socket for internal communication
        mpSocket = new SyncSocket(pAsyncSocket->mHandle, pAsyncSocket->mFamily,
                                  pAsyncSocket->mType);
        K_ASSERT_PTR(mpSocket);

        mpPacket = new FixedPacket(pPeerAddr);
        mpPacket->Alloc(len);
        mpPacket->SetContent(pSrc, len);
        mpPacket->Send(mpSocket);
    }

    /**
     * @brief Destructor
     */
    virtual ~SendJob() {
        delete mpSocket;
        mpSocket = nullptr;

        delete mpPacket;
        mpPacket = nullptr;
    }

    /**
     * @brief Updates the job state
     *
     * @return Whether the job has completed
     */
    virtual bool Calc() {
        K_ASSERT_PTR(mpPacket);

        bool finish = mpPacket->Calc();
        SOResult result = LibSO::GetLastError();

        if (finish) {
            K_ASSERT_PTR(mpCallback);
            mpCallback(result, mpPacket->GetContentSize(), mpArg);
        }

        return finish;
    }

private:
    //! Temporary socket for synchronous communication
    SyncSocket* mpSocket;
    //! Raw data packet
    FixedPacket* mpPacket;

    //! Transfer callback
    XferCallback mpCallback;
    //! Callback user argument
    void* mpArg;
};

/******************************************************************************
 *
 * AsyncSocket
 *
 ******************************************************************************/

/**
 * @brief Destructor
 */
AsyncSocket::~AsyncSocket() {
    detail::AsyncSocketMgr::GetInstance().RemoveSocket(this);

    // Release memory for receive jobs
    for (TList<IJob*>::Iterator it = mRecvJobs.Begin();
         it != mRecvJobs.End();) {

        TList<IJob*>::Iterator curr = it++;
        delete &*curr;
    }

    // Release memory for send jobs
    for (TList<IJob*>::Iterator it = mSendJobs.Begin();
         it != mSendJobs.End();) {

        TList<IJob*>::Iterator curr = it++;
        delete &*curr;
    }
}

/**
 * @brief Initializes socket state
 */
void AsyncSocket::Init() {
    mStateMachine.RegistState(EState_Idle, &AsyncSocket::State_Idle_calc);
    mStateMachine.RegistState(EState_Accept, &AsyncSocket::State_Accept_calc);
    mStateMachine.RegistState(EState_Connect, &AsyncSocket::State_Connect_calc);

    detail::AsyncSocketMgr::GetInstance().AddSocket(this);
}

/**
 * @brief Connects to a peer
 *
 * @param rAddr Remote address
 * @param pCallback Connection callback
 * @param pArg Callback user argument
 * @return Success
 */
bool AsyncSocket::Connect(const SockAddrAny& rAddr, ConnectCallback pCallback,
                          void* pArg) {
    K_ASSERT(IsOpen());

    ConnectJob* pJob = new ConnectJob(this, rAddr, pCallback, pArg);
    K_ASSERT_PTR(pJob);

    mpConnectJob = pJob;
    mStateMachine.ChangeState(EState_Connect);

    // Connect doesn't actually happen on this thread
    return false;
}

/**
 * @brief Accepts a peer connection over a new socket
 *
 * @param pCallback Acceptance callback
 * @param pArg Callback user argument
 * @return New socket
 */
AsyncSocket* AsyncSocket::Accept(AcceptCallback pCallback, void* pArg) {
    K_ASSERT(IsOpen());

    AcceptJob* pJob = new AcceptJob(this, pCallback, pArg);
    K_ASSERT_PTR(pJob);

    mpAcceptJob = pJob;
    mStateMachine.ChangeState(EState_Accept);

    // Accept doesn't actually happen on this thread
    return nullptr;
}

/**
 * @brief Updates the packet in the Idle state
 */
void AsyncSocket::State_Idle_calc() {
    K_ASSERT(IsOpen());

    // Update the oldest receive job
    if (!mRecvJobs.Empty()) {
        RecvJob& rJob = *static_cast<RecvJob*>(mRecvJobs.Front());

        if (rJob.Calc()) {
            mRecvJobs.PopFront();
            delete &rJob;
        }
    }

    // Update the oldest send job
    if (!mSendJobs.Empty()) {
        SendJob& rJob = *static_cast<SendJob*>(mSendJobs.Front());

        if (rJob.Calc()) {
            mSendJobs.PopFront();
            delete &rJob;
        }
    }
}

/**
 * @brief Updates the packet in the Connect state
 */
void AsyncSocket::State_Connect_calc() {
    K_ASSERT(IsOpen());

    if (mpConnectJob != nullptr && mpConnectJob->Calc()) {
        delete mpConnectJob;
        mpConnectJob = nullptr;

        mStateMachine.ChangeState(EState_Idle);
    }
}

/**
 * @brief Updates the packet in the Accept state
 */
void AsyncSocket::State_Accept_calc() {
    K_ASSERT(IsOpen());

    if (mpAcceptJob != nullptr && mpAcceptJob->Calc()) {
        delete mpAcceptJob;
        mpAcceptJob = nullptr;

        mStateMachine.ChangeState(EState_Idle);
    }
}

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
SOResult AsyncSocket::RecvImpl(void* pDst, u32 len, u32& rRecv,
                               SockAddrAny* pAddr, XferCallback pCallback,
                               void* pArg) {
    K_ASSERT(IsOpen());
    K_ASSERT_PTR(pDst);
    K_ASSERT_PTR(pCallback);

    // Not actually required but enforced for consistency with other sockets
    K_ASSERT(OSIsMEM2Region(pDst));

    // Asynchronous job
    RecvJob* pJob = new RecvJob(this, pDst, len, pAddr, pCallback, pArg);
    K_ASSERT_PTR(pJob);
    mRecvJobs.PushBack(pJob);

    // Receive doesn't actually happen on this thread
    rRecv = 0;
    return SO_EWOULDBLOCK;
}

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
SOResult AsyncSocket::SendImpl(const void* pSrc, u32 len, u32& rSend,
                               const SockAddrAny* pAddr, XferCallback pCallback,
                               void* pArg) {
    K_ASSERT(IsOpen());
    K_ASSERT_PTR(pSrc);
    K_ASSERT_PTR(pCallback);

    // Not actually required but enforced for consistency with other sockets
    K_ASSERT(OSIsMEM2Region(pSrc));

    // Asynchronous job
    SendJob* pJob = new SendJob(this, pSrc, len, pAddr, pCallback, pArg);
    K_ASSERT_PTR(pJob);
    mSendJobs.PushBack(pJob);

    // Send doesn't actually happen on this thread
    rSend = 0;
    return SO_EWOULDBLOCK;
}

} // namespace kiwi
