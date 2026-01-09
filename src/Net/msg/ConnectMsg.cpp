#include "Net/msg/ConnectMsg.h"

#include <libkiwi.h>

namespace AP {
namespace Net {

/**
 * @brief Constructor
 *
 * @param rStrm Stream to packet content
 */
ConnectMsg::ConnectMsg(kiwi::MemStream& rStrm) {
    u32 addr = rStrm.Read_u32();
    u16 port = rStrm.Read_u16();

    mPeerAddr = kiwi::SockAddr4(addr, port);

    K_LOG_EX("Received ConnectMsg from: %s\n",
             kiwi::ToString(mPeerAddr).CStr());
}

} // namespace Net
} // namespace AP