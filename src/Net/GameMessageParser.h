#ifndef APCLIENT_NET_GAME_MESSAGE_PARSER_H
#define APCLIENT_NET_GAME_MESSAGE_PARSER_H
#include <types.h>

#include <libkiwi.h>

namespace AP {
namespace Net {

/**
 * @brief Archipelago message parser
 */
class GameMessageParser : public kiwi::ap::IMessageParser {
public:
    /**
     * @brief Attempts to parse a network message
     *
     * @param pData Raw message data
     * @param size Message data size
     */
    virtual kiwi::ap::IMessage* Parse(const void* pData, u32 size);
};

} // namespace Net
} // namespace AP

#endif
