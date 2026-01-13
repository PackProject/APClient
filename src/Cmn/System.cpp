#include "Cmn/System.h"

#include "Cmn/CheckMgr.h"
#include "Cmn/CosmeticMgr.h"
#include "Cmn/ItemMgr.h"
#include "Net/NetworkMgr.h"
#include "Net/TextDisplay.h"

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
#if !defined(NDEBUG)
    ItemMgr::GetInstance().Debug();
    CosmeticMgr::GetInstance().Debug();
    CheckMgr::GetInstance().Debug();
#endif

    Net::NetworkMgr::CreateInstance();
    Net::TextDisplay::CreateInstance();
}

} // namespace Cmn
} // namespace AP
