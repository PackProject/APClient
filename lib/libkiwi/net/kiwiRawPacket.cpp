#include <libkiwi.h>

namespace kiwi {

/**
 * @brief Constructor
 *
 * @param pPeerAddr Peer socket address
 */
RawPacket::RawPacket(const SockAddrAny* pPeerAddr)
    : PacketBase(pPeerAddr),
      mpSocket(nullptr),
      mStateMachine(this, EState_Max, EState_Idle) {

    mStateMachine.RegistState(EState_Idle, &RawPacket::State_Idle_calc);
    mStateMachine.RegistState(EState_Recv, &RawPacket::State_Recv_calc);
    mStateMachine.RegistState(EState_Send, &RawPacket::State_Send_calc);
}

/**
 * @brief Sets the packet content
 *
 * @param pContent Packet content
 * @param size Content size
 */
void RawPacket::SetContent(const void* pContent, u32 size) {
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
void RawPacket::Recv(SocketBase* pSocket) {
    K_ASSERT_PTR(pSocket);

    mpSocket = pSocket;
    mStateMachine.ChangeState(EState_Recv);
}

/**
 * @brief Sends the packet over the specified socket
 *
 * @param pSocket Network socket
 */
void RawPacket::Send(SocketBase* pSocket) {
    K_ASSERT_PTR(pSocket);

    mpSocket = pSocket;
    mStateMachine.ChangeState(EState_Send);
}

/**
 * @brief Updates the packet state
 *
 * @return Whether the previous operation has just completed
 */
bool RawPacket::Calc() {
    mStateMachine.Calculate();
    return mStateMachine.IsState(EState_Idle);
}

/**
 * @brief Updates the packet in the Idle state
 */
void RawPacket::State_Idle_calc() {
    // Unlink socket when operations finish
    mpSocket = nullptr;
}

/**
 * @brief Updates the packet in the Recv state
 */
void RawPacket::State_Recv_calc() {
    K_ASSERT_PTR(mpSocket);

    AutoMutexLock lock(mBufferMutex);

    if (mPeerAddr.IsValid()) {
        mBuffer.Recv(mpSocket, &mPeerAddr, BufferCallback, this);
    } else {
        mBuffer.Recv(mpSocket, nullptr, BufferCallback, this);
    }
}

/**
 * @brief Updates the packet in the Send state
 */
void RawPacket::State_Send_calc() {
    K_ASSERT_PTR(mpSocket);

    AutoMutexLock lock(mBufferMutex);

    if (mPeerAddr.IsValid()) {
        mBuffer.Send(mpSocket, &mPeerAddr, BufferCallback, this);
    } else {
        mBuffer.Send(mpSocket, nullptr, BufferCallback, this);
    }
}

/**
 * @brief Buffer transfer callback
 *
 * @param size Transfer size
 * @param pArg Callback user argument
 */
void RawPacket::BufferCallback(u32 size, void* pArg) {
    K_ASSERT_PTR(pArg);
    RawPacket* p = static_cast<RawPacket*>(pArg);

    switch (p->mStateMachine.GetState()) {
    case EState_Recv: {
        // Receive is complete when the ring buffer is full
        if (p->mBuffer.Size() == p->mBuffer.Capacity()) {
            p->mStateMachine.ChangeState(EState_Idle);
        }
        break;
    }

    case EState_Send: {
        // Send is complete when the ring buffer has been exhausted
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