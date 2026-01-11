#include <libkiwi.h>

#include <cstring>

namespace kiwi {
namespace detail {

/******************************************************************************
 *
 * CommandBlock
 *
 ******************************************************************************/

/**
 * @brief Context for asynchronous socket operations
 */
struct NetBuffer::CommandBlock {
    /**
     * @brief Command type
     */
    enum EType {
        EType_None,
        EType_Recv, //!< Trying to receive data
        EType_Send, //!< Trying to send data
    };

    //! Socket operation that was requested
    EType type;
    //! Buffer that requested the socket operation
    NetBuffer* pBuffer;

    //! Buffer callback provided by the user
    Callback pCallback;
    //! Buffer callback user argument
    void* pArg;

    /**
     * @brief Constructor
     */
    CommandBlock()
        : type(EType_None),
          pBuffer(nullptr),
          pCallback(nullptr),
          pArg(nullptr) {}
};

/******************************************************************************
 *
 * NetBuffer
 *
 ******************************************************************************/

/**
 * @brief Constructor
 *
 * @param size Buffer size
 */
NetBuffer::NetBuffer(u32 size) {
    Init();
    Alloc(size);
}

/**
 * @brief Allocates a network buffer of the specified size
 *
 * @param size Buffer size
 */
void NetBuffer::Alloc(u32 size) {
    K_ASSERT(size > 0);

    // Release existing buffer
    Free();

    // Buffer needs to be in MEM2 so IOS can access it
    mpBuffer = new (32, EMemory_MEM2) u8[size];
    K_ASSERT_PTR(mpBuffer);
    K_ASSERT(OSIsMEM2Region(mpBuffer));

    mBufferSize = size;
    mReadOffset = mWriteOffset = 0;
}

/**
 * @brief Releases the network buffer
 */
void NetBuffer::Free() {
    delete[] mpBuffer;
    Init();
}

/**
 * @brief Expands the existing buffer to at least the specified size
 *
 * @param size Buffer size
 */
void NetBuffer::Reserve(u32 size) {
    K_ASSERT(size > 0);

    if (size < mBufferSize) {
        return;
    }

    // Buffer needs to be in MEM2 so IOS can access it
    u8* pNewBuffer = new (32, EMemory_MEM2) u8[size];
    K_ASSERT_PTR(pNewBuffer);
    K_ASSERT(OSIsMEM2Region(pNewBuffer));

    // Copy existing contents
    if (mpBuffer != nullptr) {
        std::memcpy(pNewBuffer, mpBuffer, mBufferSize);
        delete[] mpBuffer;
    }

    mpBuffer = pNewBuffer;
    mBufferSize = size;
}

/**
 * @brief Reads data from the network buffer
 *
 * @param pDst Data destination
 * @param size Data size
 *
 * @return Number of bytes read
 */
u32 NetBuffer::Read(void* pDst, u32 size) {
    K_ASSERT_PTR(pDst);
    K_ASSERT(size < mBufferSize);
    K_ASSERT_PTR(mpBuffer);

    // Don't allow overflow
    size = kiwi::Min(size, mBufferSize - mReadOffset);

    std::memcpy(pDst, mpBuffer + mReadOffset, size);
    mReadOffset += size;

    return size;
}

/**
 * @brief Writes data to the network buffer
 *
 * @param pSrc Data source
 * @param size Data size
 *
 * @return Number of bytes written
 */
u32 NetBuffer::Write(const void* pSrc, u32 size) {
    K_ASSERT_PTR(pSrc);
    K_ASSERT(size < mBufferSize);
    K_ASSERT_PTR(mpBuffer);

    // Don't allow overflow
    size = kiwi::Min(size, mBufferSize - mWriteOffset);

    std::memcpy(mpBuffer + mWriteOffset, pSrc, size);
    mWriteOffset += size;

    return size;
}

/**
 * @brief Receives data into the network buffer
 *
 * @param pSocket Network socket
 * @param[out] pPeerAddr Sender address
 * @param pCallback Socket transfer callback
 * @param pArg Callback user argument
 */
void NetBuffer::Recv(SocketBase* pSocket, SockAddrAny* pPeerAddr,
                     Callback pCallback, void* pArg) {
    K_ASSERT_PTR(pSocket);
    K_ASSERT_PTR(mpBuffer);

    // Context structure to help unwind the callback chain
    CommandBlock* pCmdBlock = new CommandBlock();
    K_ASSERT_PTR(pCmdBlock);

    pCmdBlock->type = CommandBlock::EType_Recv;
    pCmdBlock->pBuffer = this;
    pCmdBlock->pCallback = pCallback;
    pCmdBlock->pArg = pArg;

    // Try to complete receiving in one go
    K_ASSERT(mWriteOffset >= mReadOffset);
    u32 length = Capacity() - (mWriteOffset - mReadOffset);

    if (pPeerAddr != nullptr) {
        pSocket->RecvBytesFrom(mpBuffer + mWriteOffset, length, *pPeerAddr,
                               SocketXferCallback, pCmdBlock);
    } else {
        pSocket->RecvBytes(mpBuffer + mWriteOffset, length, SocketXferCallback,
                           pCmdBlock);
    }
}

/**
 * @brief Sends data from the network buffer
 *
 * @param pSocket Network socket
 * @param pPeerAddr Receiver address
 * @param pCallback Socket transfer callback
 * @param pArg Callback user argument
 */
void NetBuffer::Send(SocketBase* pSocket, const SockAddrAny* pPeerAddr,
                     Callback pCallback, void* pArg) {
    K_ASSERT_PTR(pSocket);
    K_ASSERT_PTR(mpBuffer);

    // Context structure to help unwind the callback chain
    CommandBlock* pCmdBlock = new CommandBlock();
    K_ASSERT_PTR(pCmdBlock);

    pCmdBlock->type = CommandBlock::EType_Send;
    pCmdBlock->pBuffer = this;
    pCmdBlock->pCallback = pCallback;
    pCmdBlock->pArg = pArg;

    // Try to complete sending in one go
    u32 length = Size();

    if (pPeerAddr != nullptr) {
        pSocket->SendBytesTo(mpBuffer + mReadOffset, length, *pPeerAddr,
                             SocketXferCallback, pCmdBlock);
    } else {
        pSocket->SendBytes(mpBuffer + mReadOffset, length, SocketXferCallback,
                           pCmdBlock);
    }
}

/**
 * @brief Initializes the buffer state
 */
void NetBuffer::Init() {
    mpBuffer = nullptr;
    mBufferSize = 0;
    mReadOffset = mWriteOffset = 0;
}

/**
 * @brief Socket transfer (send/recv) completion callback
 *
 * @param result Socket library result
 * @param size Number of bytes transferred
 * @param pArg User callback argument
 */
void NetBuffer::SocketXferCallback(SOResult result, u32 size, void* pArg) {
    K_ASSERT_PTR(pArg);

    // Context structure to help unwind the callback chain
    CommandBlock* pCmdBlock = static_cast<CommandBlock*>(pArg);
    NetBuffer* p = pCmdBlock->pBuffer;

    // Adjust the buffer indices based on which operation happened
    switch (pCmdBlock->type) {
    case CommandBlock::EType_Recv: {
        p->mWriteOffset += size;
        K_ASSERT(p->mWriteOffset <= p->mBufferSize);
        break;
    }

    case CommandBlock::EType_Send: {
        p->mReadOffset += size;
        K_ASSERT(p->mReadOffset <= p->mBufferSize);
        break;
    }

    default: {
        K_UNREACHABLE();
        break;
    }
    }

    // Unwind the callback chain
    if (pCmdBlock->pCallback != nullptr) {
        pCmdBlock->pCallback(result, size, pCmdBlock->pArg);
    }

    // Release context memory
    delete pCmdBlock;
}

} // namespace detail
} // namespace kiwi
