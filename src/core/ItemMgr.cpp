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
    mSportFlag.ResetAll();
    mCategoryFlag.ResetAll();

    mSwfVsBlockFlag = false;
    mSwfPrcPauseFlag = false;
    mSwfSglBlockFlag = 0;
    mSwfSglHeartFlag.SetDirect(0b1); // Start with one heart
    mSwfSglStageFlag.SetDirect(0b1); // Start with one stage

    mWkbTimerFlag.SetDirect(0b1); // Start with one timer
    mWkbStageFlag.SetDirect(0b1); // Start with one stage

    mArcTotalArrowsFlag.SetDirect(0b1); // Start with one arrow
    mArcStageFlag.SetDirect(0b1); // Start with one stage

    mBskTimerFlag.SetDirect(0b1); // Start with one timer

    mCanTimerFlag.SetDirect(0b1); // Start with one timer
    mCanStageFlag.SetDirect(0b1); // Start with one stage

    mBicHeartFlag.SetDirect(0b1); // Start with one heart
    mBicStageFlag.SetDirect(0b1); // Start with one stage

    mPlnTimerFlag.SetDirect(0b1); // Start with one timer
    mPlnStageFlag.SetDirect(0b1); // Start with one stage
}

/**
 * @brief Sets debug state
 */
void ItemMgr::Debug() {
    kiwi::Random r;

    mSportFlag.SetAll();
    mCategoryFlag.SetAll();

    mSwfVsBlockFlag = r.CoinFlip();
    mSwfPrcPauseFlag = r.CoinFlip();
    mSwfSglBlockFlag = r.CoinFlip();
    mSwfSglHeartFlag.Randomize();
    mSwfSglStageFlag.Randomize();

    mWkbTimerFlag.Randomize();
    mWkbStageFlag.Randomize();

    mArcTotalArrowsFlag.Randomize();
    mArcStageFlag.Randomize();
    
    mBskTimerFlag.Randomize();

    mCanTimerFlag.Randomize();
    mCanStageFlag.Randomize();

    mBicHeartFlag.Randomize();
    mBicStageFlag.Randomize();

    mPlnTimerFlag.Randomize();
    mPlnStageFlag.Randomize();
}

} // namespace AP