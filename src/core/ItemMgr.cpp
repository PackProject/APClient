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
    // Common
    mSportFlag.ResetAll();
    mCategoryFlag.ResetAll();

    // Swordplay
    mSwfVsBlockFlag = false;
    mSwfPrcPauseFlag = false;
    mSwfSglBlockFlag = 0;
    mSwfSglHeartFlag.SetDirect(0b1); // Start with one heart
    mSwfSglStageFlag.SetDirect(0b1); // Start with one stage

    // Wakeboarding
    mWkbTimerFlag.SetDirect(0b1); // Start with one timer
    mWkbStageFlag.SetDirect(0b1); // Start with one stage

    // Frisbee Dog
    mFldThrowFlag.SetDirect(0b1); // Start with one throw
    mFldSecretPopFlag = false;

    // Frisbee Golf
    mDglDiscFlag.SetDirect(0b1);  // Start with one disc
    mDglStageFlag.SetDirect(0b1); // Start with one stage

    // Archery
    mArcAimFlag = false;
    mArcArrowFlag.SetDirect(0b1); // Start with one arrow
    mArcFruitFlag.ResetAll();
    mArcStageFlag.SetDirect(0b1); // Start with one difficulty

    // Basketball
    mBsk3ptTimerFlag.SetDirect(0b1); // Start with one timer
    mBsk3ptBonusFlag = false;
    mBskVsTimerFlag.SetDirect(0b1); // Start with one timer
    mBskVsPassFlag = false;
    mBskVs3ptFlag = false;
    mBskVsDunkFlag = false;

    // Table Tennis
    mPngSpinFlag = false;
    mPngSmashFlag = false;
    mPngCansFlag = false;

    // Golf
    mGlfHUDFlag = false;
    mGlfClubFlag.SetDirect(0b10000000); // Start with one club
    mGlfTurnFlag = false;
    mGlfSpinFlag = false;
    mGlfStageFlag.SetDirect(0b1); // Start with one difficulty
    mGlfViewLowFlag = false;
    mGlfViewSlopeFlag = false;

    // Bowling
    mBwlStdMoveFlag = false;
    mBwlStdTurnFlag = false;
    mBwlStdSpinFlag = false;
    mBwl100MoveFlag = false;
    mBwl100TurnFlag = false;
    mBwl100SpinFlag = false;
    mBwl100SecretBtnFlag = false;
    mBwlWalMoveFlag = false;
    mBwlWalTurnFlag = false;
    mBwlWalSpinFlag = false;

    // Power Cruising
    mJskBoostFlag = false;
    mJskRingTimerFlag.ResetAll();
    mJsk2xRingFlag = false;
    mJskFreeTimerFlag.SetDirect(0b1); // Start with one timer

    // Canoeing
    mCanTimerFlag.SetDirect(0b1); // Start with one timer
    mCanStageFlag.SetDirect(0b1); // Start with one stage

    // Cycling
    mBicHeartFlag.SetDirect(0b1); // Start with one heart
    mBicStageFlag.SetDirect(0b1); // Start with one stage

    // Air Sports
    mPlnTimerFlag.SetDirect(0b1); // Start with one timer
    mPlnStageFlag.SetDirect(0b1); // Start with one stage
}

/**
 * @brief Sets debug state
 */
void ItemMgr::Debug() {
    kiwi::Random r;

    // Common
    mSportFlag.SetAll();
    mCategoryFlag.SetAll();

    // Swordplay
    mSwfVsBlockFlag = r.CoinFlip();
    mSwfPrcPauseFlag = r.CoinFlip();
    mSwfSglBlockFlag = r.CoinFlip();
    mSwfSglHeartFlag.Randomize();
    mSwfSglStageFlag.Randomize();

    // Wakeboarding
    mWkbTimerFlag.Randomize();
    mWkbStageFlag.Randomize();

    // Frisbee Dog
    mFldThrowFlag.Randomize();
    mFldSecretPopFlag = r.CoinFlip();

    // Frisbee Golf
    mDglDiscFlag.Randomize();
    mDglStageFlag.Randomize();

    // Archery
    mArcAimFlag = r.CoinFlip();
    mArcArrowFlag.Randomize();
    mArcFruitFlag.Randomize();
    mArcStageFlag.Randomize();

    // Basketball
    mBsk3ptTimerFlag.Randomize();
    mBsk3ptBonusFlag = r.CoinFlip();
    mBskVsTimerFlag.Randomize();
    mBskVsPassFlag = r.CoinFlip();
    mBskVs3ptFlag = r.CoinFlip();
    mBskVsDunkFlag = r.CoinFlip();

    // Table Tennis
    mPngSpinFlag = r.CoinFlip();
    mPngSmashFlag = r.CoinFlip();
    mPngCansFlag = r.CoinFlip();

    // Golf
    //mGlfHUDFlag = r.CoinFlip();
    mGlfClubFlag.Randomize();
    mGlfTurnFlag = r.CoinFlip();
    mGlfSpinFlag = r.CoinFlip();
    mGlfStageFlag.Randomize();
    mGlfViewLowFlag = r.CoinFlip();
    mGlfViewSlopeFlag = r.CoinFlip();

    // Bowling
    mBwlStdMoveFlag = r.CoinFlip();
    mBwlStdTurnFlag = r.CoinFlip();
    mBwlStdSpinFlag = r.CoinFlip();
    mBwl100MoveFlag = r.CoinFlip();
    mBwl100TurnFlag = r.CoinFlip();
    mBwl100SpinFlag = r.CoinFlip();
    mBwl100SecretBtnFlag = r.CoinFlip();
    mBwlWalMoveFlag = r.CoinFlip();
    mBwlWalTurnFlag = r.CoinFlip();
    mBwlWalSpinFlag = r.CoinFlip();

    // Power Cruising
    mJskBoostFlag = r.CoinFlip();
    mJskRingTimerFlag.Randomize();
    mJsk2xRingFlag = r.CoinFlip();
    mJskFreeTimerFlag.Randomize();

    // Canoeing
    mCanTimerFlag.Randomize();
    mCanStageFlag.Randomize();

    // Cycling
    mBicHeartFlag.Randomize();
    mBicStageFlag.Randomize();

    // Air Sports
    mPlnTimerFlag.Randomize();
    mPlnStageFlag.Randomize();
}

} // namespace AP
