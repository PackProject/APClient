#ifndef APCLIENT_PACKETS_H
#define APCLIENT_PACKETS_H
#include <types.h>

// Packet types are packed structures
#pragma pack(push, 1)

namespace AP {

/**
 * @brief Common packet structure
 */
struct CommonPacket {
    /* 0x00 */ u32 kind; //!< Type of this packet
};

/**
 * @brief Connection packet (ConnectMsg)
 */
struct ConnectPacket : CommonPacket {
    /* 0x01 */ union {
        u32 raw;
        u8 octets[4];
    } ip; //!< PC client IP address

    /* 0x05 */ u16 port; //!< PC client port
};

/**
 * @brief Disconnection packet (DisconnectMsg)
 */
struct DisconnectPacket : CommonPacket {};

/**
 * @brief Item packet (ItemMsg)
 */
struct ItemPacket : CommonPacket {};

/**
 * @brief Location packet (LocationMsg)
 */
struct LocationPacket : CommonPacket {};

} // namespace AP

#pragma pack(pop)

#endif
