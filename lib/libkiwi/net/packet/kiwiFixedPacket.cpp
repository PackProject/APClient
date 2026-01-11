#include <libkiwi.h>

#include <revolution/SO.h>

namespace kiwi {

/**
 * @brief Constructor
 *
 * @param pPeerAddr Peer socket address
 */
FixedPacket::FixedPacket(const SockAddrAny* pPeerAddr)
    : PacketBase(pPeerAddr),
      mpSocket(nullptr),
      mStateMachine(this, EState_Max, EState_Idle) {

    mStateMachine.RegistState(EState_Idle, &FixedPacket::State_Idle_calc);
    mStateMachine.RegistState(EState_Recv, &FixedPacket::State_Recv_calc);
    mStateMachine.RegistState(EState_Send, &FixedPacket::State_Send_calc);
}

/**
 * @brief Sets the packet content
 *
 * @param pContent Packet content
 * @param size Content size
 */
void FixedPacket::SetContent(const void* pContent, u32 size) {
    K_ASSERT_PTR(pContent);
    K_ASSERT(size > 0);

    // May need to reallocate the buffer
    if (size > mBuffer.Capacity()) {
        Alloc(size);
    }

    u32 bytesWritten = mBuffer.Write(pContent, size);
    K_ASSERT(bytesWritten == size);
}

/**
 * @brief Receives the packet over the specified socket
 *
 * @param pSocket Network socket
 */
void FixedPacket::Recv(SocketBase* pSocket) {
    K_ASSERT_PTR(pSocket);

    mpSocket = pSocket;
    mStateMachine.ChangeState(EState_Recv);
}

/**
 * @brief Sends the packet over the specified socket
 *
 * @param pSocket Network socket
 */
void FixedPacket::Send(SocketBase* pSocket) {
    K_ASSERT_PTR(pSocket);

    mpSocket = pSocket;
    mStateMachine.ChangeState(EState_Send);
}

/**
 * @brief Updates the packet state
 *
 * @return Whether the previous operation has just completed
 */
bool FixedPacket::Calc() {
    mStateMachine.Calculate();
    return mStateMachine.IsState(EState_Idle);
}

/**
 * @brief Updates the packet in the Idle state
 */
void FixedPacket::State_Idle_calc() {
    // Unlink socket when operations finish
    mpSocket = nullptr;
}

/**
 * @brief Updates the packet in the Recv state
 */
void FixedPacket::State_Recv_calc() {
    K_ASSERT_PTR(mpSocket);

    AutoMutexLock lock(mBufferMutex);
    K_ASSERT_EX(mBuffer.IsValid(), "Fixed packet must be manually allocated");

    if (mPeerAddr.IsValid()) {
        mBuffer.Recv(mpSocket, &mPeerAddr, BufferCallback, this);
    } else {
        mBuffer.Recv(mpSocket, nullptr, BufferCallback, this);
    }
}

/**
 * @brief Updates the packet in the Send state
 */
void FixedPacket::State_Send_calc() {
    K_ASSERT_PTR(mpSocket);

    AutoMutexLock lock(mBufferMutex);
    K_ASSERT_EX(mBuffer.IsValid(), "Fixed packet must be manually allocated");

    if (mPeerAddr.IsValid()) {
        mBuffer.Send(mpSocket, &mPeerAddr, BufferCallback, this);
    } else {
        mBuffer.Send(mpSocket, nullptr, BufferCallback, this);
    }
}

/**
 * @brief Buffer transfer callback
 *
 * @param result Socket library result
 * @param size Transfer size
 * @param pArg Callback user argument
 */
void FixedPacket::BufferCallback(SOResult result, u32 size, void* pArg) {
    K_ASSERT_PTR(pArg);
    FixedPacket* p = static_cast<FixedPacket*>(pArg);

    switch (p->mStateMachine.GetState()) {
    case EState_Recv: {
        // Receive is complete when the buffer is full
        if (p->mBuffer.Size() == p->mBuffer.Capacity()) {
            p->mStateMachine.ChangeState(EState_Idle);
        }
        break;
    }

    case EState_Send: {
        // Send is complete when the buffer has been exhausted
        if (p->mBuffer.Size() == 0) {
            p->mStateMachine.ChangeState(EState_Idle);
        }
        break;
    }

    default: {
        K_UNREACHABLE();
        break;
    }
    }
}

} // namespace kiwi