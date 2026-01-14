#ifndef LIBKIWI_AP_I_AP_MESSAGE_PARSER_H
#define LIBKIWI_AP_I_AP_MESSAGE_PARSER_H
#include <libkiwi/k_types.h>

namespace kiwi {
//! @addtogroup libkiwi_fun
//! @{
namespace ap {
//! @addtogroup libkiwi_fun
//! @{

// Forward declarations
class IMessage;

/**
 * @brief Archipelago message parser interface
 */
class IMessageParser {
public:
    /**
     * @brief Attempts to parse a network message
     *
     * @param pData Raw message data
     * @param size Message data size
     */
    virtual IMessage* Parse(const void* pData, u32 size) = 0;
};

//! @}
} // namespace ap
//! @}
} // namespace kiwi

#endif
