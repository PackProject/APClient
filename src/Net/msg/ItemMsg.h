#ifndef APCLIENT_NET_MSG_ITEM_MSG_H
#define APCLIENT_NET_MSG_ITEM_MSG_H
#include <types.h>

#include "Net/IMessage.h"

#include <libkiwi.h>

namespace AP {
namespace Net {

/**
 * @brief Item message
 */
class ItemMsg : public IMessage {
public:
    /**
     * @brief Constructor
     *
     * @param rStrm Stream to packet content
     */
    ItemMsg(kiwi::MemStream& rStrm);

    /**
     * @brief Gets the type of this command
     */
    virtual EKind GetKind() const {
        return EKind_Item;
    }
};

} // namespace Net
} // namespace AP

#endif
