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

    mBsk3ptTimerFlag.SetDirect(0b1); // Start with one timer
    mBskVsTimerFlag.SetDirect(0b1); // Start with one timer
    mBskVsPassFlag = false;

    mBwlStdMoveFlag = false;
    mBwlStdTurnFlag = false;
    mBwl100MoveFlag = false;
    mBwl100TurnFlag = false;
    mBwlWalMoveFlag = false;
    mBwlWalTurnFlag = false;

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

    //Common
    mSportFlag.SetAll();
    mCategoryFlag.SetAll();

    //Swordplay
    mSwfVsBlockFlag = r.CoinFlip();
    mSwfPrcPauseFlag = r.CoinFlip();
    mSwfSglBlockFlag = r.CoinFlip();
    mSwfSglHeartFlag.Randomize();
    mSwfSglStageFlag.Randomize();

    //Wakeboarding
    mWkbTimerFlag.Randomize();
    mWkbStageFlag.Randomize();

    //Archery
    mArcTotalArrowsFlag.Randomize();
    mArcStageFlag.Randomize();
    
    //Basketball
    mBsk3ptTimerFlag.Randomize();
    mBskVsTimerFlag.Randomize();
    mBskVsPassFlag = r.CoinFlip();

    //Bowling
    mBwlStdMoveFlag = r.CoinFlip();
    mBwlStdTurnFlag = r.CoinFlip();
    mBwl100MoveFlag = r.CoinFlip();
    mBwl100TurnFlag = r.CoinFlip();
    mBwlWalMoveFlag = r.CoinFlip();
    mBwlWalTurnFlag = r.CoinFlip();

    //Canoeing
    mCanTimerFlag.Randomize();
    mCanStageFlag.Randomize();

    //Cycling
    mBicHeartFlag.Randomize();
    mBicStageFlag.Randomize();

    //Air Sports
    mPlnTimerFlag.Randomize();
    mPlnStageFlag.Randomize();
}

} // namespace AP