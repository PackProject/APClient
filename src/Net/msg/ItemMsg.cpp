#include "Net/msg/ItemMsg.h"
#include "Cmn/ItemMgr.h"

#include <libkiwi.h>

namespace AP {
namespace Net {

/**
 * @brief Constructor
 * 
 * @param rStrm Stream to packet content
 */
ItemMsg::ItemMsg(kiwi::MemStream& rStrm) {
    u16 itemId = rStrm.Read_u16();

    Cmn::ItemMgr::GetInstance().SetItemState((ItemID)itemId, true);
}
}
}