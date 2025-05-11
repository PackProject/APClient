#include "core/ItemMgr.h"

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

    mWkbTimerFlag = 0;
    mWkbStageFlag = 0b1;
}

/**
 * @brief Sets debug state
 */
void ItemMgr::Debug() {
    kiwi::Random r;

    mSportFlag = 0xFFFFFFFF;
    mCategoryFlag = 0xFFFFFFFF;

    mSwfVsBlockFlag = r.CoinFlip();
    mSwfPrcPauseFlag = r.CoinFlip();
    mSwfSglBlockFlag = r.CoinFlip();
    mSwfSglHeartFlag = 0b001 | r.NextU32();
    mSwfSglStageFlag = 0xFFFFFFFF;

    mWkbTimerFlag = r.NextU32();
    mWkbStageFlag = r.NextU32();
}

} // namespace AP