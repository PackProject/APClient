#ifndef LIBKIWI_NET_NET_CONNECTION_MGR_H
#define LIBKIWI_NET_NET_CONNECTION_MGR_H
#include <libkiwi/core/kiwiThread.h>
#include <libkiwi/k_types.h>
#include <libkiwi/prim/kiwiList.h>
#include <libkiwi/prim/kiwiMutex.h>
#include <libkiwi/util/kiwiStaticSingleton.h>

#include <revolution/OS.h>

namespace kiwi {
//! @addtogroup libkiwi_net
//! @{

// Forward declarations
class NetConnection;
class StdThread;

namespace detail {
//! @addtogroup libkiwi_net
//! @{

/**
 * @brief Network socket connection manager
 */
class NetConnectionMgr : public kiwi::Thread,
                         public StaticSingleton<NetConnectionMgr> {

    friend class StaticSingleton<NetConnectionMgr>;

public:
    /**
     * @brief Appends a new network connection to the manager list
     *
     * @param pConnection New network connection
     */
    void AddConnection(NetConnection* pConnection);

    /**
     * @brief Removes a network connection from the manager list
     *
     * @param pConnection Network connection
     */
    void RemoveConnection(NetConnection* pConnection);

private:
    /**
     * @brief Constructor
     */
    NetConnectionMgr();

    /**
     * @brief Thread function
     */
    virtual void Run();

private:
    //! Open connections
    TList<NetConnection*> mConnectionList;
    //! Connection list mutex
    Mutex mListMutex;
};

//! @}
} // namespace detail
//! @}
} // namespace kiwi

#endif
