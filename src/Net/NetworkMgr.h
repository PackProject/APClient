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

public:
    /**
     * @brief Gets the player slot name
     */
    const kiwi::WString& GetPlayerName() const {
        return mPlayerName;
    }

    /**
     * @brief Sets the player slot name
     *
     * @param rName Player slot name
     */
    void SetPlayerName(const kiwi::WString& rName) {
        mPlayerName = rName;
    }

private:
    /**
     * @brief Constructor
     */
    NetworkMgr();

private:
    //! Player slot name
    kiwi::WString mPlayerName;
};

} // namespace Net
} // namespace AP

#endif
