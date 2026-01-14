#include "Net/msg/ItemMsg.h"

#include "Cmn/ItemMgr.h"
#include "const.h"

#include <libkiwi.h>

namespace AP {
namespace Net {

/**
 * @brief Constructor
 *
 * @param rStrm Stream to packet content
 */
ItemMsg::ItemMsg(kiwi::MemStream& rStrm) {
    mItemID = static_cast<ItemID>(rStrm.Read_u16());
    ASSERT(mItemID != ITEM_INVALID);
}

} // namespace Net
} // namespace AP