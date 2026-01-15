#ifndef APCLIENT_NET_MSG_AUTH_MSG_H
#define APCLIENT_NET_MSG_AUTH_MSG_H
#include <types.h>

#include "Net/Define.h"

#include <libkiwi.h>

namespace AP {
namespace Net {

/**
 * @brief PC client authentication message
 */
class AuthMsg : public kiwi::ap::IMessage {
public:
    /**
     * @brief Constructor
     *
     * @param rStrm Stream to packet content
     */
    AuthMsg(kiwi::MemStream& rStrm);

    /**
     * @brief Gets the type of this message
     */
    virtual u32 GetType() const {
        return Define::EMsgType_Auth;
    }

    /**
     * @brief Accesses the player slot name
     */
    const kiwi::WString& GetPlayerName() const {
        return mPlayerName;
    }

private:
    //! Player slot name
    kiwi::WString mPlayerName;
};

} // namespace Net
} // namespace AP

#endif
