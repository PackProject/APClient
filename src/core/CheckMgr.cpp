#include "core/CheckMgr.h"

#include "core/ItemMgr.h"
#include "core/checks.h"

#include <libkiwi.h>

K_DYNAMIC_SINGLETON_IMPL(AP::CheckMgr);

namespace AP {

/**
 * @brief Gets the readable name of the specified check ID
 */
kiwi::String CheckMgr::GetCheckName(CheckID id) {
#define X(ID, IDENT, STR)                                                      \
    case CHECK_##IDENT:                                                        \
        return STR;

    switch (id) {
        // Generate switch cases for each check
        AP_CHECKS_LIST;

    default:
        ASSERT_EX(false, "Unknown CheckID: %d", id);
        return "Unknown CheckID";
    }

#undef X
}

/**
 * @brief Constructor
 */
CheckMgr::CheckMgr() {
    Clear();
}

/**
 * @brief Clears check state
 */
void CheckMgr::Clear() {
#define X(ID, IDENT, STR) SetCheckState(CHECK_##IDENT, false);
    // Clear each check
    AP_CHECKS_LIST;
#undef X
}

/**
 * @brief Sets debug state
 */
void CheckMgr::Debug() {}

bool CheckMgr::GetCheckState(CheckID id) const {
    return mCheckState.Get(id, false);
}

void CheckMgr::SetCheckState(CheckID id, bool state) {
    kiwi::cout << "Check: " << GetCheckName(id) << " has been set to " << state
               << kiwi::endl;
    mCheckState.Insert(id, state);
}

u16 CheckMgr::GetItemID(CheckID id) const {
    u16 itemIDResult = mCheckToItemID.Get(id, 0xFFFF);
    ASSERT(itemIDResult != 0xFFFF);
    return itemIDResult;
}

void CheckMgr::SetItemID(CheckID id, u16 itemID) {
    mCheckToItemID.Insert(id, itemID);
}

void CheckMgr::GiveItemFromCheck(CheckID id) {
    // u16 itemID = GetItemID(id);
    // ItemMgr::GetInstance().GiveItemToPlayer(ItemMgr::ItemID(itemID)); // this
    // should be what's actually ran
    ItemMgr::GetInstance().GiveItemToPlayer(ItemMgr::BASKETBALL_3PT_TIMER);
    SetCheckState(id, true);
}

} // namespace AP
