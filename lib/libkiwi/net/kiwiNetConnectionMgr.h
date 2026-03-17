#ifndef LIBKIWI_NET_NET_CONNECTION_MGR_H
#define LIBKIWI_NET_NET_CONNECTION_MGR_H
#include <libkiwi/k_types.h>
#include <libkiwi/prim/kiwiList.h>
#include <libkiwi/util/kiwiStaticSingleton.h>

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
class NetConnectionMgr : public StaticSingleton<NetConnectionMgr> {
    friend class StaticSingleton<NetConnectionMgr>;

public:
    /**
     * @brief Appends a new network connection to the manager list
     *
     * @param pConnection New network connection
     */
    void AddConnection(NetConnection* pConnection) {
        K_ASSERT_PTR(pConnection);
        mConnectionList.PushBack(pConnection);
    }

    /**
     * @brief Removes a network connection from the manager list
     *
     * @param pConnection Network connection
     */
    void RemoveConnection(NetConnection* pConnection) {
        mConnectionList.Remove(pConnection);
    }

private:
    /**
     * @brief Constructor
     */
    NetConnectionMgr();

    /**
     * @brief Destructor
     */
    ~NetConnectionMgr();

    /**
     * @brief Thread function
     */
    void ThreadFunc();

private:
    //! Manager thread
    StdThread* mpThread;
    //! Open connections
    TList<NetConnection*> mConnectionList;
};

//! @}
} // namespace detail
//! @}
} // namespace kiwi

#endif
