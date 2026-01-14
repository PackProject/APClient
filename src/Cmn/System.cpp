#include "Cmn/System.h"

#include "Cmn/CheckMgr.h"
#include "Cmn/CosmeticMgr.h"
#include "Cmn/ItemMgr.h"
#include "Cmn/SceneHook.h"
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
#if !defined(NDEBUG)
    ItemMgr::GetInstance().Debug();
    CosmeticMgr::GetInstance().Debug();
    CheckMgr::GetInstance().Debug();
#endif

    Net::NetworkMgr::CreateInstance();
    Cmn::SceneHook::CreateInstance();
}

} // namespace Cmn
} // namespace AP
