#include "core/CheckMgr.h"

#include <libkiwi.h>

K_DYNAMIC_SINGLETON_IMPL(AP::CheckMgr);

namespace AP {

/**
 * @brief Binary file path
 */
const char* CheckMgr::PATH = "item.bin";

/**
 * @brief Constructor
 */
CheckMgr::CheckMgr() {
    Clear();
}

/**
 * @brief Deserializes binary contents (internal implementation)
 *
 * @param rHeader Binary file header
 */
void CheckMgr::DeserializeImpl(const Header& rHeader) {
    ;
}

/**
 * @brief Serializes binary contents (internal implementation)
 *
 * @param rHeader Binary file header
 */
void CheckMgr::SerializeImpl(Header& rHeader) const {
    ;
}

/**
 * @brief Clears check state
 */
void CheckMgr::Clear() {
    for(u16 i = 0x0000; i < CheckMgr::COUNT; i++)
    {
        SetCheckState(CheckID(i), false);
    }
}

/**
 * @brief Sets debug state
 */
void CheckMgr::Debug() {
    for(u16 i = 0x0000; i < CheckMgr::COUNT; i++)
    {
        kiwi::cout << "Check " << i << " is " << CheckMgr::GetCheckState(CheckID(i)) << kiwi::endl;
    }
}

bool CheckMgr::GetCheckState(CheckID id) const {
    return mCheckState.Get(id, false);
}

void CheckMgr::SetCheckState(CheckID id, bool state) {
    mCheckState.Insert(id, state);
}

u16 CheckMgr::GetItemID(CheckID id) const {
    u16 itemIDResult = mCheckToItemID.Get(id, 0xFFFF);
    K_ASSERT(itemIDResult != 0xFFFF);
    return itemIDResult;
}

void CheckMgr::SetItemID(CheckID id, u16 itemID) {
    mCheckToItemID.Insert(id, itemID);
}

} // namespace AP