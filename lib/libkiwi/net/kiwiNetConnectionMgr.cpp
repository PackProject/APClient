#include <libkiwi.h>

namespace kiwi {
namespace detail {

/**
 * @brief Constructor
 */
NetConnectionMgr::NetConnectionMgr() : Thread("NetConnectionMgr") {
    Resume();
}

/**
 * @brief Appends a new network connection to the manager list
 *
 * @param pConnection New network connection
 */
void NetConnectionMgr::AddConnection(NetConnection* pConnection) {
    K_ASSERT_PTR(pConnection);

    AutoMutexLock lock(mListMutex);
    mConnectionList.PushBack(pConnection);
}

/**
 * @brief Removes a network connection from the manager list
 *
 * @param pConnection Network connection
 */
void NetConnectionMgr::RemoveConnection(NetConnection* pConnection) {
    AutoMutexLock lock(mListMutex);
    mConnectionList.Remove(pConnection);
}

/**
 * @brief Thread function
 */
void NetConnectionMgr::Run() {
    K_LOG("[NetConnectionMgr] Start up\n");

    while (true) {
        mListMutex.Lock();

        K_FOREACH (it, mConnectionList) {
            (*it)->Calc();
        }

        mListMutex.Unlock();
    }
}

} // namespace detail
} // namespace kiwi