#ifndef APCLIENT_NET_MSG_PRINT_MSG_H
#define APCLIENT_NET_MSG_PRINT_MSG_H
#include <types.h>

#include "Net/Define.h"

#include <libkiwi.h>

namespace AP {
namespace Net {

/**
 * @brief Print message
 */
class PrintMsg : public kiwi::ap::IMessage {
public:
    /**
     * @brief Constructor
     *
     * @param rStrm Stream to packet content
     */
    PrintMsg(kiwi::MemStream& rStrm);

    /**
     * @brief Gets the type of this message
     */
    virtual u32 GetType() const {
        return Define::EMessageType_Print;
    }

    /**
     * @brief Accesses the list of messages to display
     */
    const kiwi::TList<kiwi::WString>& GetMessageList() {
        return mMessageList;
    }

private:
    //! Messages to print
    kiwi::TList<kiwi::WString> mMessageList;
};

} // namespace Net
} // namespace AP

#endif
