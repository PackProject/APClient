#include "Cmn/CheckMgr.h"

#include "Cmn/ItemMgr.h"
#include "checks.h"

#include <libkiwi.h>

K_DYNAMIC_SINGLETON_IMPL(AP::Cmn::CheckMgr);

namespace AP {
namespace Cmn {

/**
 * @brief Gets the readable name of the specified check ID
 *
 * @param id Item ID
 */
kiwi::String CheckMgr::GetCheckName(CheckID id) {
#define X(ID, IDENT, STR)                                                      \
    case CHECK_##IDENT:                                                        \
        return STR;

    switch (id) {
        // Generate switch cases for each check
        AP_CHECKS_X_MACRO;

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
 * @brief Resets the check state to the default settings
 */
void CheckMgr::Clear() {
#define X(ID, IDENT, STR) SetCheckState(CHECK_##IDENT, false);
    // Clear each check
    AP_CHECKS_X_MACRO;
#undef X
}

/**
 * @brief Randomizes the check state for debugging purposes
 */
void CheckMgr::Debug() {
    // TODO(kiwi) Implement this
}

/**
 * @brief Gets the current state of the specified check
 *
 * @param id Check ID
 * @return Whether the check has been completed
 */
bool CheckMgr::GetCheckState(CheckID id) const {
    ASSERT_EX(mCheckState.Contains(id), "Check not initialized: %d", id);
    return mCheckState.Get(id, false);
}

/**
 * @brief Sets the current state of the specified check
 *
 * @param id Check ID
 * @param state Whether the check has been completed
 */
void CheckMgr::SetCheckState(CheckID id, bool state) {
    kiwi::cout << "Check: " << GetCheckName(id) << " has been set to " << state
               << kiwi::endl;

    mCheckState.Insert(id, state);
}

/**
 * @brief Gets the item mapped to the specified check
 *
 * @param id Check ID
 * @return Item obtained from the check
 */
ItemID CheckMgr::GetCheckItem(CheckID id) const {
    ASSERT_EX(mCheckToItemID.Contains(id), "Check has no item set: %d", id);
    return mCheckToItemID.Get(id, ITEM_INVALID);
}

/**
 * @brief Maps an item to the specified check
 *
 * @param id Check ID
 * @param item Item ID
 */
void CheckMgr::SetCheckItem(CheckID id, ItemID item) {
    ASSERT_EX(!mCheckToItemID.Contains(id), "Check mapped twice: %d", id);
    mCheckToItemID.Insert(id, item);
}

} // namespace Cmn
} // namespace AP
