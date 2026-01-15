#ifndef APCLIENT_NET_MSG_ITEM_MSG_H
#define APCLIENT_NET_MSG_ITEM_MSG_H
#include <types.h>

#include "Net/Define.h"
#include "const.h"

#include <libkiwi.h>

namespace AP {
namespace Net {

/**
 * @brief Item message
 */
class ItemMsg : public kiwi::ap::IMessage {
public:
    /**
     * @brief Constructor
     *
     * @param rStrm Stream to packet content
     */
    ItemMsg(kiwi::MemStream& rStrm);

    /**
     * @brief Gets the type of this message
     */
    virtual u32 GetType() const {
        return Define::EMsgType_Item;
    }

    /**
     * @brief Gets the ID of the item to award
     */
    ItemID GetItemID() const {
        return mItemID;
    }

private:
    // ID of the item to award
    ItemID mItemID;
};

} // namespace Net
} // namespace AP

#endif
