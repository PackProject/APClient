#ifndef APCLIENT_NET_I_MESSAGE_H
#define APCLIENT_NET_I_MESSAGE_H
#include <types.h>

namespace AP {
namespace Net {

/**
 * @brief Network message interface
 */
class IMessage {
public:
    /**
     * @brief Command type
     */
    enum EKind {
        EKind_Connect,
        EKind_Disconnect,
        EKind_Print,
        EKind_Item,
    };

public:
    /**
     * @brief Destructor
     */
    virtual ~IMessage() {}

    /**
     * @brief Gets the type of this message
     */
    virtual EKind GetKind() const = 0;
};

} // namespace Net
} // namespace AP

#endif
