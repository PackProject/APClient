#include "Net/msg/PrintMsg.h"

#include <libkiwi.h>

namespace AP {
namespace Net {

/**
 * @brief Constructor
 *
 * @param rStrm Stream to packet content
 */
PrintMsg::PrintMsg(kiwi::MemStream& rStrm) {
    while (!rStrm.IsEOF()) {
        kiwi::WString text = rStrm.Read_wstring();
        mMessageList.PushBack(text);
    }
}

} // namespace Net
} // namespace AP