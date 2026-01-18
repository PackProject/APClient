#include <libkiwi.h>

namespace kiwi {
namespace detail {

/**
 * @brief Constructor
 */
AsyncSocketMgr::AsyncSocketMgr() : Thread("AsyncSocketMgr") {
    Resume();
}

/**
 * @brief Appends a new socket to the manager list
 *
 * @param pSocket New socket
 */
void AsyncSocketMgr::AddSocket(AsyncSocket* pSocket) {
    K_ASSERT_PTR(pSocket);

    AutoMutexLock lock(mListMutex);
    mSocketList.PushBack(pSocket);
}

/**
 * @brief Removes a socket from the manager list
 *
 * @param pSocket Socket
 */
void AsyncSocketMgr::RemoveSocket(AsyncSocket* pSocket) {
    AutoMutexLock lock(mListMutex);
    mSocketList.Remove(pSocket);
}

/**
 * @brief Thread function
 */
void AsyncSocketMgr::Run() {
    K_LOG("[AsyncSocketMgr] Start up\n");

    while (true) {
        mListMutex.Lock();

        K_FOREACH (it, mSocketList) {
            K_ASSERT((*it)->IsOpen());
            (*it)->Calc();
        }

        mListMutex.Unlock();
    }
}

} // namespace detail
} // namespace kiwi