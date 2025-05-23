#include <libkiwi.h>

namespace kiwi {

/**
 * @brief Allocates message buffer of the specified size
 *
 * @param size Packet size
 */
void Packet::Alloc(u32 size) {
    K_ASSERT(size > 0);
    K_ASSERT_EX(size < GetMaxContent(), "Must be fragmented!");

    // Free existing message
    if (mpBuffer != nullptr) {
        Free();
    }

    // Protocol may have memory overhead
    mBufferSize = size + GetOverhead();

    mpBuffer = new (32, EMemory_MEM2) u8[mBufferSize];
    K_ASSERT_PTR(mpBuffer);
    K_ASSERT(OSIsMEM2Region(mpBuffer));

    Clear();
}

/**
 * @brief Releases message buffer
 */
void Packet::Free() {
    AutoMutexLock lock(mBufferMutex);

    delete mpBuffer;
    mpBuffer = nullptr;

    Clear();
}

/**
 * @brief Clears existing state
 */
void Packet::Clear() {
    AutoMutexLock lock(mBufferMutex);

    mReadOffset = 0;
    mWriteOffset = 0;
}

/**
 * @brief Reads data from message buffer
 *
 * @param pDst Data destination
 * @param size Data size
 *
 * @return Number of bytes read
 */
u32 Packet::Read(void* pDst, u32 size) {
    K_ASSERT_PTR(mpBuffer);
    K_ASSERT(size <= GetMaxContent());

    AutoMutexLock lock(mBufferMutex);

    // Clamp size to avoid overflow
    size = Min(size, ReadRemain());

    // Copy data from buffer
    std::memcpy(pDst, mpBuffer + mReadOffset, size);
    mReadOffset += size;

    return size;
}

/**
 * @brief Writes data to message buffer
 *
 * @param pSrc Data source
 * @param size Data size
 *
 * @return Number of bytes written
 */
u32 Packet::Write(const void* pSrc, u32 size) {
    K_ASSERT_PTR(mpBuffer);
    K_ASSERT(size <= GetMaxContent());

    AutoMutexLock lock(mBufferMutex);

    // Clamp size to avoid overflow
    size = Min(size, WriteRemain());

    // Copy data to buffer
    std::memcpy(mpBuffer + mWriteOffset, pSrc, size);
    mWriteOffset += size;

    return size;
}

/**
 * @brief Receives message data from socket
 *
 * @param socket Socket descriptor
 *
 * @return Number of bytes received
 */
Optional<u32> Packet::Recv(SOSocket socket) {
    K_ASSERT(socket >= 0);
    K_ASSERT_PTR(mpBuffer);

    AutoMutexLock lock(mBufferMutex);

    // Read from socket (try to complete packet)
    s32 result = LibSO::RecvFrom(socket, mpBuffer + mWriteOffset, WriteRemain(),
                                 0, mAddress);

    // Blocking, just say zero
    if (result == SO_EWOULDBLOCK) {
        return 0;
    }

    // > 0 means bytes read from socket
    if (result >= 0) {
        mWriteOffset += result;
        return result;
    }

    return kiwi::nullopt;
}

/**
 * @brief Writes message data to socket
 *
 * @param socket Socket descriptor
 *
 * @return Number of bytes sent
 */
Optional<u32> Packet::Send(SOSocket socket) {
    K_ASSERT(socket >= 0);
    K_ASSERT_PTR(mpBuffer);

    AutoMutexLock lock(mBufferMutex);

    // Send through socket (try to complete packet)
    s32 result = LibSO::SendTo(socket, mpBuffer + mReadOffset, ReadRemain(), 0,
                               mAddress);

    // Blocking, just say zero
    if (result == SO_EWOULDBLOCK) {
        return 0;
    }

    // > 0 means bytes written to socket
    if (result >= 0) {
        mReadOffset += result;
        return result;
    }

    return kiwi::nullopt;
}

} // namespace kiwi
