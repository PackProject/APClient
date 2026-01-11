#include "Cmn/System.h"

#include "Cmn/CheckMgr.h"
#include "Cmn/CosmeticMgr.h"
#include "Cmn/ItemMgr.h"
#include "Net/NetworkMgr.h"

namespace AP {
namespace Cmn {

/**
 * @brief Performs initialization for required objects
 */
void System::Initialize() {
    ItemMgr::CreateInstance();
    CosmeticMgr::CreateInstance();
    CheckMgr::CreateInstance();

    // TODO: Move to debug menu eventually
#ifndef NDEBUG
    ItemMgr::GetInstance().Debug();
    CosmeticMgr::GetInstance().Debug();
    CheckMgr::GetInstance().Debug();
#endif

    Net::NetworkMgr::CreateInstance();
}

} // namespace Cmn
} // namespace AP
