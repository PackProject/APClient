#include <core/ItemMgr.h>
#include <libkiwi.h>

K_DYNAMIC_SINGLETON_IMPL(AP::ItemMgr);

namespace AP {

/**
 * @brief Binary file path
 */
const char* ItemMgr::PATH = "item.bin";

/**
 * @brief Constructor
 */
ItemMgr::ItemMgr() {
    Clear();
}

/**
 * @brief Deserializes binary contents (internal implementation)
 *
 * @param rHeader Binary file header
 */
void ItemMgr::DeserializeImpl(const Header& rHeader) {
    ;
}

/**
 * @brief Serializes binary contents (internal implementation)
 *
 * @param rHeader Binary file header
 */
void ItemMgr::SerializeImpl(Header& rHeader) const {
    ;
}

/**
 * @brief Clears item state
 */
void ItemMgr::Clear() {
    mSportFlag = 0;
    mCategoryFlag = 0;

    mSwfVsBlockFlag = false;
    mSwfPrcPauseFlag = false;
    mSwfSglBlockFlag = 0;
    mSwfSglHeartFlag = 0b001;
    mSwfSglStageFlag = 0;
}

} // namespace AP