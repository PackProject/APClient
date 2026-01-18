#ifndef LIBKIWI_NET_ASYNC_SOCKET_MGR_H
#define LIBKIWI_NET_ASYNC_SOCKET_MGR_H
#include <libkiwi/core/kiwiThread.h>
#include <libkiwi/debug/kiwiAssert.h>
#include <libkiwi/k_types.h>
#include <libkiwi/prim/kiwiList.h>
#include <libkiwi/prim/kiwiMutex.h>
#include <libkiwi/util/kiwiStaticSingleton.h>

namespace kiwi {
//! @addtogroup libkiwi_net
//! @{

// Forward declarations
class AsyncSocket;
class StdThread;

namespace detail {
//! @addtogroup libkiwi_net
//! @{

/**
 * @brief Asynchronous socket manager
 */
class AsyncSocketMgr : public kiwi::Thread,
                       public StaticSingleton<AsyncSocketMgr> {

    friend class StaticSingleton<AsyncSocketMgr>;

public:
    /**
     * @brief Appends a new socket to the manager list
     *
     * @param pSocket New socket
     */
    void AddSocket(AsyncSocket* pSocket);

    /**
     * @brief Removes a socket from the manager list
     *
     * @param pSocket Socket
     */
    void RemoveSocket(AsyncSocket* pSocket);

private:
    /**
     * @brief Constructor
     */
    AsyncSocketMgr();

    /**
     * @brief Thread function
     */
    virtual void Run();

private:
    //! Open sockets
    TList<AsyncSocket*> mSocketList;
    //! Socket list mutex
    Mutex mListMutex;
};

//! @}
} // namespace detail
//! @}
} // namespace kiwi

#endif
