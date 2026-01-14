#ifndef APCLIENT_NET_DEFINE_H
#define APCLIENT_NET_DEFINE_H
#include <types.h>

namespace AP {
namespace Net {
namespace Define {

/**
 * @brief Archipelago message types
 */
enum EMessageType {
    /* 0x00 */ EMessageType_Connect,
    /* 0x01 */ EMessageType_Disconnect,
    /* 0x02 */ EMessageType_Print,
    /* 0x03 */ EMessageType_Item,
    /* 0x04 */ EMessageType_Location,
};

//! General message acknowledgement byte
static const u8 ACK = 0xAA;

} // namespace Define
} // namespace Net
} // namespace AP

#endif
