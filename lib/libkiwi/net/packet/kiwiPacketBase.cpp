#include <libkiwi.h>

namespace kiwi {

/**
 * @brief Constructor
 *
 * @param pPeerAddr Peer socket address
 */
PacketBase::PacketBase(const SockAddrAny* pPeerAddr) {
    K_ASSERT(pPeerAddr == nullptr || pPeerAddr->IsValid());

    // Peer address is provided for outgoing packets
    if (pPeerAddr != nullptr) {
        mPeerAddr = *pPeerAddr;
    } else {
        mPeerAddr = SockAddr4();
    }
}

/**
 * @brief Allocates a packet buffer of the specified size
 *
 * @param size Packet size
 */
void PacketBase::Alloc(u32 size) {
    K_ASSERT(size > 0);
    K_ASSERT_EX(size < GetMaxContent(), "Must be fragmented!");

    AutoMutexLock lock(mBufferMutex);
    mBuffer.Alloc(size + GetOverhead());
}

/**
 * @brief Expands the existing packet buffer to at least the specified size
 *
 * @param size Buffer size
 */
void PacketBase::Reserve(u32 size) {
    K_ASSERT(size > 0);
    K_ASSERT_EX(size < GetMaxContent(), "Must be fragmented!");

    AutoMutexLock lock(mBufferMutex);
    mBuffer.Reserve(size + GetOverhead());
}

/**
 * @brief Reads data from the packet
 *
 * @param pDst Data destination
 * @param size Data size
 *
 * @return Number of bytes read
 */
u32 PacketBase::Read(void* pDst, u32 size) {
    K_ASSERT_PTR(pDst);

    AutoMutexLock lock(mBufferMutex);
    return mBuffer.Read(pDst, size);
}

/**
 * @brief Writes data to the packet
 *
 * @param pSrc Data source
 * @param size Data size
 *
 * @return Number of bytes written
 */
u32 PacketBase::Write(const void* pSrc, u32 size) {
    K_ASSERT_PTR(pSrc);

    AutoMutexLock lock(mBufferMutex);
    return mBuffer.Write(pSrc, size);
}

/**
 * @brief Releases the packet buffer
 */
void PacketBase::Free() {
    AutoMutexLock lock(mBufferMutex);
    mBuffer.Free();
}

} // namespace kiwi