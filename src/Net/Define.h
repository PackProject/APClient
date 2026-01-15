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
    /* 0x00 */ EMsgType_Connect,
    /* 0x01 */ EMsgType_Disconnect,
    /* 0x02 */ EMsgType_Auth,
    /* 0x03 */ EMsgType_Print,
    /* 0x04 */ EMsgType_Item,
    /* 0x05 */ EMsgType_Location,
};

//! General message acknowledgement byte
static const u8 ACK = 0xAA;

} // namespace Define
} // namespace Net
} // namespace AP

#endif
