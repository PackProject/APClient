#include "Net/msg/LocationMsg.h"

#include "Cmn/CheckMgr.h"
#include "Net/NetworkMgr.h"
#include "checks.h"

#include <libkiwi.h>

namespace AP {
namespace Net {

/**
 * @brief Constructor
 *
 * @param rStrm Stream to packet content
 */
LocationMsg::LocationMsg(kiwi::MemStream& rStrm) {
    // mData.Clear();
}

kiwi::TVector<u32> LocationMsg::GetChecks() {
    mData.Clear();

#define X(ID, IDENTIFIER, STR)                                                 \
    if (Cmn::CheckMgr::GetInstance().GetCheckState((CheckID)ID)) {             \
        mData.PushBack(static_cast<u32>(ID));                                  \
    }

    AP_CHECKS_X_MACRO

#undef X

    for (int i = 0; i < mData.Size(); i++) {
        kiwi::cout << mData[i];
    }

    kiwi::cout << kiwi::endl;

    return mData;
}

} // namespace Net
} // namespace AP