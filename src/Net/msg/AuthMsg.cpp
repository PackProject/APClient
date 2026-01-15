#include "Net/msg/AuthMsg.h"

#include <libkiwi.h>

namespace AP {
namespace Net {

/**
 * @brief Constructor
 *
 * @param rStrm Stream to packet content
 */
AuthMsg::AuthMsg(kiwi::MemStream& rStrm) {
    mPlayerName = rStrm.Read_wstring();
}

} // namespace Net
} // namespace AP