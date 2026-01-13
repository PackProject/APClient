#ifndef APCLIENT_NET_MSG_LOCATION_MSG_H
#define APCLIENT_NET_MSG_LOCATION_MSG_H
#include <types.h>

#include "Net/IMessage.h"
#include "Net/NetworkMgr.h"

#include <libkiwi.h>

namespace AP {
namespace Net {

/**
 * @brief Location message
 */
class LocationMsg : public IMessage {
public:
    /**
     * @brief Constructor
     *
     * @param rStrm Stream to packet content
     */
    LocationMsg(kiwi::MemStream& rStrm);

    /**
     * @brief returns MemStream of all location data
     */
    kiwi::TVector<u32> GetLocationMsg();

    /**
     * @brief Gets the type of this command
     */
    virtual EKind GetKind() const {
        return EKind_Location;
    }
private:
    kiwi::TVector<u32> mData;
};

} // namespace Net
} // namespace AP

#endif
