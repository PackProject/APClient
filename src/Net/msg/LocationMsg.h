#ifndef APCLIENT_NET_MSG_LOCATION_MSG_H
#define APCLIENT_NET_MSG_LOCATION_MSG_H
#include <types.h>

#include "Net/Define.h"

#include <libkiwi.h>

namespace AP {
namespace Net {

/**
 * @brief Location message
 */
class LocationMsg : public kiwi::ap::IMessage {
public:
    /**
     * @brief Constructor
     *
     * @param rStrm Stream to packet content
     */
    LocationMsg(kiwi::MemStream& /* rStrm */) {}

    /**
     * @brief Gets the type of this message
     */
    virtual u32 GetType() const {
        return Define::EMessageType_Location;
    }
};

} // namespace Net
} // namespace AP

#endif
