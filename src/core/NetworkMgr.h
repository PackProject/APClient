#ifndef APCLIENT_CORE_NETWORK_MGR_H
#define APCLIENT_CORE_NETWORK_MGR_H
#include <types.h>

#include <libkiwi.h>

namespace AP {

/**
 * @brief Archipelago connection
 */
class NetworkMgr : public kiwi::DynamicSingleton<NetworkMgr> {
    friend class kiwi::DynamicSingleton<NetworkMgr>;

public:
    ;

private:
    //! Network server
    kiwi::NetServer* mpServer;
};

} // namespace AP

#endif
