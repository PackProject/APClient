#ifndef LIBKIWI_AP_I_AP_MESSAGE_H
#define LIBKIWI_AP_I_AP_MESSAGE_H
#include <libkiwi/k_types.h>

namespace kiwi {
//! @addtogroup libkiwi_fun
//! @{
namespace ap {
//! @addtogroup libkiwi_fun
//! @{

/**
 * @brief Archipelago message interface
 */
class IMessage {
public:
    /**
     * @brief Destructor
     */
    virtual ~IMessage() {}

    /**
     * @brief Gets the type of this message
     */
    virtual u32 GetType() const = 0;
};

//! @}
} // namespace ap
//! @}
} // namespace kiwi

#endif
