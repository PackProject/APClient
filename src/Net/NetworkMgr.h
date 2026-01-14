#ifndef APCLIENT_NET_NETWORK_MGR_H
#define APCLIENT_NET_NETWORK_MGR_H
#include <types.h>

#include <libkiwi.h>

namespace AP {
namespace Net {

/**
 * @brief Network communication manager
 */
class NetworkMgr : public kiwi::ap::Server,
                   public kiwi::DynamicSingleton<NetworkMgr> {

    friend class kiwi::DynamicSingleton<NetworkMgr>;

private:
    /**
     * @brief Constructor
     */
    NetworkMgr();
};

} // namespace Net
} // namespace AP

#endif
