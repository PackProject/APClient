#include "Net/NetworkMgr.h"

#include "Net/GameMessageParser.h"

#include <libkiwi.h>

K_DYNAMIC_SINGLETON_IMPL(AP::Net::NetworkMgr);

namespace AP {
namespace Net {

/**
 * @brief Constructor
 */
NetworkMgr::NetworkMgr() : Server(new GameMessageParser()) {
    kiwi::SockAddr4 addr = GetServerAddr();
    ASSERT(addr.IsValid());

    LOG_EX("[NetworkMgr] Listening for client: %s\n",
           kiwi::ToString(addr).CStr());
}

} // namespace Net
} // namespace AP