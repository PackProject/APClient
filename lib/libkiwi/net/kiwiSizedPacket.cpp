#include <libkiwi.h>

namespace kiwi {

/**
 * @brief Allocates message buffer of the specified size
 *
 * @param size Packet size
 */
void SizedPacket::Alloc(u32 size) {
    Packet::Alloc(size);
    GetHeader().size = size;
}

} // namespace kiwi