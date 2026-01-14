#include "Net/GameMessageParser.h"

#include "Net/Define.h"
#include "Net/msg/ConnectMsg.h"
#include "Net/msg/DisconnectMsg.h"
#include "Net/msg/ItemMsg.h"
#include "Net/msg/LocationMsg.h"
#include "Net/msg/PrintMsg.h"

#include <libkiwi.h>

namespace AP {
namespace Net {

/**
 * @brief Attempts to parse a network message
 *
 * @param pData Raw message data
 * @param size Message data size
 */
kiwi::ap::IMessage* GameMessageParser::Parse(const void* pData, u32 size) {
    ASSERT_PTR(pData);
    ASSERT(size > 0);

    kiwi::MemStream strm(pData, size);

    // Every packet's data begins with the common fields
    Define::EMessageType type =
        static_cast<Define::EMessageType>(strm.Read_u8());

    switch (type) {
    case Define::EMessageType_Connect: {
        return new ConnectMsg(strm);
    }

    case Define::EMessageType_Disconnect: {
        return new DisconnectMsg(strm);
    }

    case Define::EMessageType_Print: {
        return new PrintMsg(strm);
    }

    case Define::EMessageType_Item: {
        return new ItemMsg(strm);
    }

    case Define::EMessageType_Location: {
        return new LocationMsg(strm);
    }

    default: {
        K_ASSERT_EX(false, "Unknown message type: %d\n", type);
        return nullptr;
    }
    }
}

} // namespace Net
} // namespace AP
