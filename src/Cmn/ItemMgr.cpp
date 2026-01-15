#include "Cmn/ItemMgr.h"

#include "items.h"

#include <libkiwi.h>

K_DYNAMIC_SINGLETON_IMPL(AP::Cmn::ItemMgr);

namespace AP {
namespace Cmn {

/**
 * @brief Gets the readable name of the specified item ID
 *
 * @param id Item ID
 */
kiwi::String ItemMgr::GetItemName(ItemID id) {
#define X(ID, IDENT, STR)                                                      \
    case ITEM_##IDENT: {                                                       \
        return STR;                                                            \
    }

    switch (id) {
        // Generate switch cases for each item
        AP_ITEMS_X_MACRO;

    default: {
        ASSERT_EX(false, "Unknown ItemID: %d", id);
        return "Unknown ItemID";
    }
    }

#undef X
}

/**
 * @brief Constructor
 */
ItemMgr::ItemMgr() {
    Clear();
}

/**
 * @brief Resets the item state to the default settings
 */
void ItemMgr::Clear() {
    // Common
    mSportFlag.ResetAll();
    mCategoryFlag.ResetAll();

    // Swordplay
    mSwfVsBlockFlag = false;
    mSwfPrcPauseFlag = false;
    mSwfSglBlockFlag = false;
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
    mJskBoostFlag = true;
    mJskRingTimerFlag.ResetAll();
    mJsk2xRingFlag = false;
    mJskFreeTimerFlag.SetDirect(0b1); // Start with one timer
    mJskStageFlag.SetDirect(0b1);     // Start with one stage

    // Canoeing
    mCanTimerFlag.SetDirect(0b1); // Start with one timer
    mCanStageFlag.SetDirect(0b1); // Start with one stage

    // Cycling
    mBicHeartFlag.SetDirect(0b1); // Start with one heart
    mBicStageFlag.SetDirect(0b1); // Start with one stage

    // Skydiving
    mOmkMiiFlag.ResetAll();

    // Air Sports
    mPlnTimerFlag.SetDirect(0b1); // Start with one timer
    mPlnStageFlag.SetDirect(0b1); // Start with one stage
    mPlnDoubleBlastersFlag = false;
    mPlnNightLightsFlag = false;
    mPlnBalloonsFlag = false;
    mPlnTwoSeaterPlaneFlag = false;
    mPlnBoostFlag = true;
    mPlnBrakeFlag = true;
}

/**
 * @brief Randomizes the item state for debugging purposes
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
    mGlfHUDFlag = r.CoinFlip();
    mGlfClubFlag.Randomize();
    mGlfTurnFlag = r.CoinFlip();
    mGlfSpinFlag = r.CoinFlip();
    mGlfStageFlag = r.CoinFlip();
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
    mJskStageFlag.Randomize();

    // Canoeing
    mCanTimerFlag.Randomize();
    mCanStageFlag.Randomize();

    // Cycling
    mBicHeartFlag.Randomize();
    mBicStageFlag.Randomize();

    // Skydiving
    mOmkMiiFlag.Randomize();

    // Air Sports
    mPlnTimerFlag.Randomize();
    mPlnStageFlag.Randomize();
    mPlnDoubleBlastersFlag = r.CoinFlip();
    mPlnNightLightsFlag = r.CoinFlip();
    mPlnBalloonsFlag = r.CoinFlip();
    mPlnTwoSeaterPlaneFlag = r.CoinFlip();
    mPlnBoostFlag = r.CoinFlip();
    mPlnBrakeFlag = r.CoinFlip();
}

/**
 * @brief Gets the current state of the specified item
 *
 * @param id Item ID
 * @return Whether the item has been obtained
 */
bool ItemMgr::GetItemState(ItemID id) const {
    switch (id) {
    // Sport unlocks
    case ITEM_SWORDPLAY_DUEL_SPORT_UNLOCK:
    case ITEM_SWORDPLAY_SPEED_SLICE_SPORT_UNLOCK:
    case ITEM_SWORDPLAY_SHOWDOWN_SPORT_UNLOCK:
    case ITEM_WAKEBOARDING_SPORT_UNLOCK:
    case ITEM_FRISBEE_DOG_SPORT_UNLOCK:
    case ITEM_FRISBEE_GOLF_SPORT_UNLOCK:
    case ITEM_ARCHERY_SPORT_UNLOCK:
    case ITEM_BASKETBALL_3POINT_CONTEST_SPORT_UNLOCK:
    case ITEM_BASKETBALL_PICKUP_GAME_SPORT_UNLOCK:
    case ITEM_TABLE_TENNIS_MATCH_SPORT_UNLOCK:
    case ITEM_TABLE_TENNIS_RETURN_CHALLENGE_SPORT_UNLOCK:
    case ITEM_GOLF_SPORT_UNLOCK:
    case ITEM_BOWLING_STANDARD_GAME_SPORT_UNLOCK:
    case ITEM_BOWLING_100_PIN_GAME_SPORT_UNLOCK:
    case ITEM_BOWLING_SPIN_CONTROL_SPORT_UNLOCK:
    case ITEM_POWER_CRUISING_SPORT_UNLOCK:
    case ITEM_CANOEING_SPEED_CHALLENGE_SPORT_UNLOCK:
    case ITEM_CYCLING_SINGLE_RACE_UNLOCK:
    case ITEM_AIRSPORTS_SKYDIVING_UNLOCK:
    case ITEM_AIRSPORTS_ISLAND_FLYOVER_UNLOCK: {
        return mSportFlag.GetBit(id - ITEM_SWORDPLAY_DUEL_SPORT_UNLOCK);
    }

    // Category unlocks
    case ITEM_SWORDPLAY_CATEGORY_UNLOCK:
    case ITEM_WAKEBOARD_CATEGORY_UNLOCK:
    case ITEM_FRISBEE_CATEGORY_UNLOCK:
    case ITEM_ARCHERY_CATEGORY_UNLOCK:
    case ITEM_BASKETBALL_CATEGORY_UNLOCK:
    case ITEM_TABLE_TENNIS_CATEGORY_UNLOCK:
    case ITEM_GOLF_CATEGORY_UNLOCK:
    case ITEM_BOWLING_CATEGORY_UNLOCK:
    case ITEM_POWER_CRUISING_CATEGORY_UNLOCK:
    case ITEM_CANOEING_CATEGORY_UNLOCK:
    case ITEM_CYCLING_CATEGORY_UNLOCK:
    case ITEM_AIRSPORTS_CATEGORY_UNLOCK: {
        return mCategoryFlag.GetBit(id - ITEM_SWORDPLAY_CATEGORY_UNLOCK);
    }

    // Swordplay
    case ITEM_SWORDPLAY_DUEL_BLOCK: {
        return mSwfVsBlockFlag;
    }
    case ITEM_SWORDPLAY_SPEED_SLICE_PAUSE: {
        return mSwfPrcPauseFlag;
    }
    case ITEM_SWORDPLAY_SHOWDOWN_BLOCK: {
        return mSwfVsBlockFlag;
    }

    case ITEM_SWORDPLAY_SHOWDOWN_HEART: {
        return mSwfSglHeartFlag.Count();
    }
    case ITEM_SWORDPLAY_SHOWDOWN_STAGE_1:
    case ITEM_SWORDPLAY_SHOWDOWN_STAGE_2:
    case ITEM_SWORDPLAY_SHOWDOWN_STAGE_3:
    case ITEM_SWORDPLAY_SHOWDOWN_STAGE_4:
    case ITEM_SWORDPLAY_SHOWDOWN_STAGE_5:
    case ITEM_SWORDPLAY_SHOWDOWN_STAGE_6:
    case ITEM_SWORDPLAY_SHOWDOWN_STAGE_7:
    case ITEM_SWORDPLAY_SHOWDOWN_STAGE_8:
    case ITEM_SWORDPLAY_SHOWDOWN_STAGE_9:
    case ITEM_SWORDPLAY_SHOWDOWN_STAGE_10:
    case ITEM_SWORDPLAY_SHOWDOWN_STAGE_11:
    case ITEM_SWORDPLAY_SHOWDOWN_STAGE_12:
    case ITEM_SWORDPLAY_SHOWDOWN_STAGE_13:
    case ITEM_SWORDPLAY_SHOWDOWN_STAGE_14:
    case ITEM_SWORDPLAY_SHOWDOWN_STAGE_15:
    case ITEM_SWORDPLAY_SHOWDOWN_STAGE_16:
    case ITEM_SWORDPLAY_SHOWDOWN_STAGE_17:
    case ITEM_SWORDPLAY_SHOWDOWN_STAGE_18:
    case ITEM_SWORDPLAY_SHOWDOWN_STAGE_19:
    case ITEM_SWORDPLAY_SHOWDOWN_STAGE_20: {
        return mSwfSglStageFlag.GetBit(id - ITEM_SWORDPLAY_SHOWDOWN_STAGE_1);
    }

    // Wakeboarding
    case ITEM_WAKEBOARDING_TIMER: {
        return mWkbTimerFlag.Count();
    }
    case ITEM_WAKEBOARDING_BEGINNER:
    case ITEM_WAKEBOARDING_INTERMEDIATE:
    case ITEM_WAKEBOARDING_EXPERT: {
        return mWkbStageFlag.GetBit(id - ITEM_WAKEBOARDING_BEGINNER);
    }

    // Frisbee Dog
    case ITEM_FRISBEE_DOG_PROG_FRISBEES: {
        return mFldThrowFlag.Count();
    }
    case ITEM_FRISBEE_DOG_SECRET_POP: {
        return mFldSecretPopFlag;
    }

    // Frisbee Golf
    case ITEM_FRISBEE_GOLF_HUD: {
        return mDglHUDFlag;
    }
    case ITEM_FRISBEE_GOLF_DRIVER: {
    case ITEM_FRISBEE_GOLF_MIDRANGE:
    case ITEM_FRISBEE_GOLF_PUTTER:
        return mDglDiscFlag.GetBit(id - ITEM_FRISBEE_GOLF_DRIVER);
    }
    case ITEM_FRISBEE_GOLF_COURSE_0: {
    case ITEM_FRISBEE_GOLF_COURSE_1:
    case ITEM_FRISBEE_GOLF_COURSE_2:
    case ITEM_FRISBEE_GOLF_COURSE_3:
    case ITEM_FRISBEE_GOLF_COURSE_4:
    case ITEM_FRISBEE_GOLF_COURSE_5:
    case ITEM_FRISBEE_GOLF_COURSE_6:
    case ITEM_FRISBEE_GOLF_COURSE_7:
    case ITEM_FRISBEE_GOLF_COURSE_8:
    case ITEM_FRISBEE_GOLF_COURSE_9:
        return mDglStageFlag.GetBit(id - ITEM_FRISBEE_GOLF_COURSE_0);
    }

    // Archery
    case ITEM_ARCHERY_AIM_CIRCLE: {
        return mArcAimFlag;
    }
    case ITEM_ARCHERY_ARROW: {
        return mArcArrowFlag.Count();
    }
    case ITEM_ARCHERY_FRUIT_BEGINNER: {
    case ITEM_ARCHERY_FRUIT_INTERMEDIATE:
    case ITEM_ARCHERY_FRUIT_EXPERT:
        return mArcFruitFlag.GetBit(id - ITEM_ARCHERY_FRUIT_BEGINNER);
    }
    case ITEM_ARCHERY_BEGINNER:
    case ITEM_ARCHERY_INTERMEDIATE:
    case ITEM_ARCHERY_EXPERT: {
        return mArcStageFlag.GetBit(id - ITEM_ARCHERY_BEGINNER);
    }

    // Basketball
    case ITEM_BASKETBALL_3PT_TIMER: {
        return mBsk3ptTimerFlag.Count();
    }
    case ITEM_BASKETBALL_BONUS_BALLS: {
        return mBsk3ptBonusFlag;
    }
    case ITEM_BASKETBALL_PICKUP_TIMER: {
        return mBskVsTimerFlag.Count();
    }
    case ITEM_BASKETBALL_PASS: {
        return mBskVsPassFlag;
    }
    case ITEM_BASKETBALL_3PTS: {
        return mBskVs3ptFlag;
    }
    case ITEM_BASKETBALL_DUNK: {
        return mBskVsDunkFlag;
    }

    // Table Tennis
    case ITEM_TABLE_TENNIS_SPIN: {
        return mPngSpinFlag;
    }
    case ITEM_TABLE_TENNIS_SMASH: {
        return mPngSmashFlag;
    }
    case ITEM_TABLE_TENNIS_CANS: {
        return mPngCansFlag;
    }

    // Golf
    case ITEM_GOLF_HUD: {
        return mGlfHUDFlag;
    }
    case ITEM_GOLF_DRIVER: {
    case ITEM_GOLF_3_WOOD:
    case ITEM_GOLF_3_IRON:
    case ITEM_GOLF_5_IRON:
    case ITEM_GOLF_7_IRON:
    case ITEM_GOLF_9_IRON:
    case ITEM_GOLF_WEDGE:
    case ITEM_GOLF_PUTTER:
        return mGlfClubFlag.GetBit(id - ITEM_GOLF_DRIVER);
    }
    case ITEM_GOLF_TURN: {
        return mGlfTurnFlag;
    }
    case ITEM_GOLF_BACKSPIN: {
        return mGlfSpinFlag;
    }
    case ITEM_GOLF_COURSE_0: {
    case ITEM_GOLF_COURSE_1:
    case ITEM_GOLF_COURSE_2:
    case ITEM_GOLF_COURSE_3:
    case ITEM_GOLF_COURSE_4:
    case ITEM_GOLF_COURSE_5:
    case ITEM_GOLF_COURSE_6:
    case ITEM_GOLF_COURSE_7:
    case ITEM_GOLF_COURSE_8:
    case ITEM_GOLF_COURSE_9:
        return mGlfStageFlag.GetBit(id - ITEM_GOLF_COURSE_0);
    }
    case ITEM_GOLF_VIEW_LOW: {
        return mGlfViewLowFlag;
    }
    case ITEM_GOLF_VIEW_SLOPE: {
        return mGlfViewSlopeFlag;
    }

    // Bowling
    case ITEM_BOWLING_10_PIN_MOVE: {
        return mBwlStdMoveFlag;
    }
    case ITEM_BOWLING_10_PIN_TURN: {
        return mBwlStdTurnFlag;
    }
    case ITEM_BOWLING_10_PIN_SPIN: {
        return mBwlStdSpinFlag;
    }
    case ITEM_BOWLING_100_PIN_MOVE: {
        return mBwl100MoveFlag;
    }
    case ITEM_BOWLING_100_PIN_TURN: {
        return mBwl100TurnFlag;
    }
    case ITEM_BOWLING_100_PIN_SPIN: {
        return mBwl100SpinFlag;
    }
    case ITEM_BOWLING_100_PIN_SECRET_STRIKE: {
        return mBwl100SecretBtnFlag;
    }
    case ITEM_BOWLING_SPIN_CONTROL_MOVE: {
        return mBwlWalMoveFlag;
    }
    case ITEM_BOWLING_SPIN_CONTROL_TURN: {
        return mBwlWalTurnFlag;
    }
    case ITEM_BOWLING_SPIN_CONTROL_SPIN: {
        return mBwlWalSpinFlag;
    }

    // Power Cruising
    case ITEM_POWER_CRUISING_BOOST: {
        return mJskBoostFlag;
    }
    case ITEM_POWER_CRUISING_RING_TIMER: {
        return mJskRingTimerFlag.Count();
    }
    case ITEM_POWER_CRUISING_DOUBLE_RING: {
        return mJsk2xRingFlag;
    }
    case ITEM_POWER_CRUISING_FREE_CRUISING_TIMER: {
        return mJskFreeTimerFlag.Count();
    }

    // Canoeing
    case ITEM_CANOEING_TIMER: {
        return mCanTimerFlag.Count();
    }
    case ITEM_CANOEING_BEGINNER: {
    case ITEM_CANOEING_INTERMEDIATE:
    case ITEM_CANOEING_EXPERT:
        return mCanStageFlag.GetBit(id - ITEM_CANOEING_BEGINNER);
    }

    // Cycling
    case ITEM_CYCLING_HEART: {
        return mBicHeartFlag.Count();
    }
    case ITEM_CYCLING_STAGE_0: {
    case ITEM_CYCLING_STAGE_1:
    case ITEM_CYCLING_STAGE_2:
    case ITEM_CYCLING_STAGE_3:
    case ITEM_CYCLING_STAGE_4:
    case ITEM_CYCLING_STAGE_5:
    case ITEM_CYCLING_STAGE_6:
    case ITEM_CYCLING_STAGE_7:
        return mBicStageFlag.GetBit(id - ITEM_CYCLING_STAGE_0);
    }

    // Skydiving
    case ITEM_SKYDIVING_MII: {
        return mOmkMiiFlag.Count();
    }

    // Air Sports
    case ITEM_ISLAND_FLYOVER_TIMER: {
        return mPlnTimerFlag.Count();
    }
    case ITEM_ISLAND_FLYOVER_DAY: {
    case ITEM_ISLAND_FLYOVER_EVENING:
    case ITEM_ISLAND_FLYOVER_NIGHT:
        return mPlnStageFlag.GetBit(id - ITEM_ISLAND_FLYOVER_DAY);
    }
    case ITEM_ISLAND_FLYOVER_DOUBLE_BLASTERS: {
        return mPlnDoubleBlastersFlag;
    }
    case ITEM_ISLAND_FLYOVER_NIGHT_LIGHTS: {
        return mPlnNightLightsFlag;
    }
    case ITEM_ISLAND_FLYOVER_UNLOCK_BALLOONS: {
        return mPlnBalloonsFlag;
    }
    case ITEM_ISLAND_FLYOVER_UNLOCK_TWO_SEATER: {
        return mPlnTwoSeaterPlaneFlag;
    }
    case ITEM_ISLAND_FLYOVER_UNLOCK_BOOST: {
        return mPlnBoostFlag;
    }
    case ITEM_ISLAND_FLYOVER_UNLOCK_BRAKE: {
        return mPlnBrakeFlag;
    }

    default: {
        ASSERT_EX(false, "Unknown ItemID: %d", id);
        return false;
    }
    }
}

/**
 * @brief Sets the current state of the specified item
 *
 * @param id Item ID
 * @param state Whether the item has been obtained
 */
void ItemMgr::SetItemState(ItemID id, bool state) {
    kiwi::cout << "Item: " << GetItemName(id) << " has been set to " << state
               << kiwi::endl;

    switch (id) {
    // Sport unlocks
    case ITEM_SWORDPLAY_DUEL_SPORT_UNLOCK:
    case ITEM_SWORDPLAY_SPEED_SLICE_SPORT_UNLOCK:
    case ITEM_SWORDPLAY_SHOWDOWN_SPORT_UNLOCK:
    case ITEM_WAKEBOARDING_SPORT_UNLOCK:
    case ITEM_FRISBEE_DOG_SPORT_UNLOCK:
    case ITEM_FRISBEE_GOLF_SPORT_UNLOCK:
    case ITEM_ARCHERY_SPORT_UNLOCK:
    case ITEM_BASKETBALL_3POINT_CONTEST_SPORT_UNLOCK:
    case ITEM_BASKETBALL_PICKUP_GAME_SPORT_UNLOCK:
    case ITEM_TABLE_TENNIS_MATCH_SPORT_UNLOCK:
    case ITEM_TABLE_TENNIS_RETURN_CHALLENGE_SPORT_UNLOCK:
    case ITEM_GOLF_SPORT_UNLOCK:
    case ITEM_BOWLING_STANDARD_GAME_SPORT_UNLOCK:
    case ITEM_BOWLING_100_PIN_GAME_SPORT_UNLOCK:
    case ITEM_BOWLING_SPIN_CONTROL_SPORT_UNLOCK:
    case ITEM_POWER_CRUISING_SPORT_UNLOCK:
    case ITEM_CANOEING_SPEED_CHALLENGE_SPORT_UNLOCK:
    case ITEM_CYCLING_SINGLE_RACE_UNLOCK:
    case ITEM_AIRSPORTS_SKYDIVING_UNLOCK:
    case ITEM_AIRSPORTS_ISLAND_FLYOVER_UNLOCK: {
        mSportFlag.SetBit(id - ITEM_SWORDPLAY_DUEL_SPORT_UNLOCK);
        break;
    }

    // Category unlocks
    case ITEM_SWORDPLAY_CATEGORY_UNLOCK:
    case ITEM_WAKEBOARD_CATEGORY_UNLOCK:
    case ITEM_FRISBEE_CATEGORY_UNLOCK:
    case ITEM_ARCHERY_CATEGORY_UNLOCK:
    case ITEM_BASKETBALL_CATEGORY_UNLOCK:
    case ITEM_TABLE_TENNIS_CATEGORY_UNLOCK:
    case ITEM_GOLF_CATEGORY_UNLOCK:
    case ITEM_BOWLING_CATEGORY_UNLOCK:
    case ITEM_POWER_CRUISING_CATEGORY_UNLOCK:
    case ITEM_CANOEING_CATEGORY_UNLOCK:
    case ITEM_CYCLING_CATEGORY_UNLOCK:
    case ITEM_AIRSPORTS_CATEGORY_UNLOCK: {
        mCategoryFlag.SetBit(id - ITEM_SWORDPLAY_CATEGORY_UNLOCK);
        break;
    }

    // Swordplay
    case ITEM_SWORDPLAY_DUEL_BLOCK: {
        mSwfVsBlockFlag = true;
        break;
    }
    case ITEM_SWORDPLAY_SPEED_SLICE_PAUSE: {
        mSwfPrcPauseFlag = true;
        break;
    }
    case ITEM_SWORDPLAY_SHOWDOWN_BLOCK: {
        mSwfVsBlockFlag = true;
        break;
    }

    case ITEM_SWORDPLAY_SHOWDOWN_HEART: {
        mSwfSglHeartFlag.SetFirstUnset();
        break;
    }
    case ITEM_SWORDPLAY_SHOWDOWN_STAGE_1:
    case ITEM_SWORDPLAY_SHOWDOWN_STAGE_2:
    case ITEM_SWORDPLAY_SHOWDOWN_STAGE_3:
    case ITEM_SWORDPLAY_SHOWDOWN_STAGE_4:
    case ITEM_SWORDPLAY_SHOWDOWN_STAGE_5:
    case ITEM_SWORDPLAY_SHOWDOWN_STAGE_6:
    case ITEM_SWORDPLAY_SHOWDOWN_STAGE_7:
    case ITEM_SWORDPLAY_SHOWDOWN_STAGE_8:
    case ITEM_SWORDPLAY_SHOWDOWN_STAGE_9:
    case ITEM_SWORDPLAY_SHOWDOWN_STAGE_10:
    case ITEM_SWORDPLAY_SHOWDOWN_STAGE_11:
    case ITEM_SWORDPLAY_SHOWDOWN_STAGE_12:
    case ITEM_SWORDPLAY_SHOWDOWN_STAGE_13:
    case ITEM_SWORDPLAY_SHOWDOWN_STAGE_14:
    case ITEM_SWORDPLAY_SHOWDOWN_STAGE_15:
    case ITEM_SWORDPLAY_SHOWDOWN_STAGE_16:
    case ITEM_SWORDPLAY_SHOWDOWN_STAGE_17:
    case ITEM_SWORDPLAY_SHOWDOWN_STAGE_18:
    case ITEM_SWORDPLAY_SHOWDOWN_STAGE_19:
    case ITEM_SWORDPLAY_SHOWDOWN_STAGE_20: {
        mSwfSglStageFlag.SetBit(id - ITEM_SWORDPLAY_SHOWDOWN_STAGE_1);
        break;
    }

    // Wakeboarding
    case ITEM_WAKEBOARDING_TIMER: {
        mWkbTimerFlag.SetFirstUnset();
        break;
    }
    case ITEM_WAKEBOARDING_BEGINNER:
    case ITEM_WAKEBOARDING_INTERMEDIATE:
    case ITEM_WAKEBOARDING_EXPERT: {
        mWkbStageFlag.SetBit(id - ITEM_WAKEBOARDING_BEGINNER);
        break;
    }

    // Frisbee Dog
    case ITEM_FRISBEE_DOG_PROG_FRISBEES: {
        mFldThrowFlag.SetFirstUnset();
        break;
    }
    case ITEM_FRISBEE_DOG_SECRET_POP: {
        mFldSecretPopFlag = true;
        break;
    }

    // Frisbee Golf
    case ITEM_FRISBEE_GOLF_HUD: {
        mDglHUDFlag = true;
        break;
    }
    case ITEM_FRISBEE_GOLF_DRIVER: {
    case ITEM_FRISBEE_GOLF_MIDRANGE:
    case ITEM_FRISBEE_GOLF_PUTTER:
        mDglDiscFlag.SetBit(id - ITEM_FRISBEE_GOLF_DRIVER);
        break;
    }
    case ITEM_FRISBEE_GOLF_COURSE_0: {
    case ITEM_FRISBEE_GOLF_COURSE_1:
    case ITEM_FRISBEE_GOLF_COURSE_2:
    case ITEM_FRISBEE_GOLF_COURSE_3:
    case ITEM_FRISBEE_GOLF_COURSE_4:
    case ITEM_FRISBEE_GOLF_COURSE_5:
    case ITEM_FRISBEE_GOLF_COURSE_6:
    case ITEM_FRISBEE_GOLF_COURSE_7:
    case ITEM_FRISBEE_GOLF_COURSE_8:
    case ITEM_FRISBEE_GOLF_COURSE_9:
        mDglStageFlag.SetBit(id - ITEM_FRISBEE_GOLF_COURSE_0);
        break;
    }

    // Archery
    case ITEM_ARCHERY_AIM_CIRCLE: {
        mArcAimFlag = true;
        break;
    }
    case ITEM_ARCHERY_ARROW: {
        mArcArrowFlag.SetFirstUnset();
        break;
    }
    case ITEM_ARCHERY_FRUIT_BEGINNER: {
    case ITEM_ARCHERY_FRUIT_INTERMEDIATE:
    case ITEM_ARCHERY_FRUIT_EXPERT:
        mArcFruitFlag.SetBit(id - ITEM_ARCHERY_FRUIT_BEGINNER);
        break;
    }
    case ITEM_ARCHERY_BEGINNER:
    case ITEM_ARCHERY_INTERMEDIATE:
    case ITEM_ARCHERY_EXPERT: {
        mArcStageFlag.SetBit(id - ITEM_ARCHERY_BEGINNER);
        break;
    }

    // Basketball
    case ITEM_BASKETBALL_3PT_TIMER: {
        mBsk3ptTimerFlag.SetFirstUnset();
        break;
    }
    case ITEM_BASKETBALL_BONUS_BALLS: {
        mBsk3ptBonusFlag = true;
        break;
    }
    case ITEM_BASKETBALL_PICKUP_TIMER: {
        mBskVsTimerFlag.SetFirstUnset();
        break;
    }
    case ITEM_BASKETBALL_PASS: {
        mBskVsPassFlag = true;
        break;
    }
    case ITEM_BASKETBALL_3PTS: {
        mBskVs3ptFlag = true;
        break;
    }
    case ITEM_BASKETBALL_DUNK: {
        mBskVsDunkFlag = true;
        break;
    }

    // Table Tennis
    case ITEM_TABLE_TENNIS_SPIN: {
        mPngSpinFlag = true;
        break;
    }
    case ITEM_TABLE_TENNIS_SMASH: {
        mPngSmashFlag = true;
        break;
    }
    case ITEM_TABLE_TENNIS_CANS: {
        mPngCansFlag = true;
        break;
    }

    // Golf
    case ITEM_GOLF_HUD: {
        mGlfHUDFlag = true;
        break;
    }
    case ITEM_GOLF_DRIVER: {
    case ITEM_GOLF_3_WOOD:
    case ITEM_GOLF_3_IRON:
    case ITEM_GOLF_5_IRON:
    case ITEM_GOLF_7_IRON:
    case ITEM_GOLF_9_IRON:
    case ITEM_GOLF_WEDGE:
    case ITEM_GOLF_PUTTER:
        mGlfClubFlag.SetBit(id - ITEM_GOLF_DRIVER);
        break;
    }
    case ITEM_GOLF_TURN: {
        mGlfTurnFlag = true;
        break;
    }
    case ITEM_GOLF_BACKSPIN: {
        mGlfSpinFlag = true;
        break;
    }
    case ITEM_GOLF_COURSE_0: {
    case ITEM_GOLF_COURSE_1:
    case ITEM_GOLF_COURSE_2:
    case ITEM_GOLF_COURSE_3:
    case ITEM_GOLF_COURSE_4:
    case ITEM_GOLF_COURSE_5:
    case ITEM_GOLF_COURSE_6:
    case ITEM_GOLF_COURSE_7:
    case ITEM_GOLF_COURSE_8:
    case ITEM_GOLF_COURSE_9:
        mGlfStageFlag.SetBit(id - ITEM_GOLF_COURSE_0);
        break;
    }
    case ITEM_GOLF_VIEW_LOW: {
        mGlfViewLowFlag = true;
        break;
    }
    case ITEM_GOLF_VIEW_SLOPE: {
        mGlfViewSlopeFlag = true;
        break;
    }

    // Bowling
    case ITEM_BOWLING_10_PIN_MOVE: {
        mBwlStdMoveFlag = true;
        break;
    }
    case ITEM_BOWLING_10_PIN_TURN: {
        mBwlStdTurnFlag = true;
        break;
    }
    case ITEM_BOWLING_10_PIN_SPIN: {
        mBwlStdSpinFlag = true;
        break;
    }
    case ITEM_BOWLING_100_PIN_MOVE: {
        mBwl100MoveFlag = true;
        break;
    }
    case ITEM_BOWLING_100_PIN_TURN: {
        mBwl100TurnFlag = true;
        break;
    }
    case ITEM_BOWLING_100_PIN_SPIN: {
        mBwl100SpinFlag = true;
        break;
    }
    case ITEM_BOWLING_100_PIN_SECRET_STRIKE: {
        mBwl100SecretBtnFlag = true;
        break;
    }
    case ITEM_BOWLING_SPIN_CONTROL_MOVE: {
        mBwlWalMoveFlag = true;
        break;
    }
    case ITEM_BOWLING_SPIN_CONTROL_TURN: {
        mBwlWalTurnFlag = true;
        break;
    }
    case ITEM_BOWLING_SPIN_CONTROL_SPIN: {
        mBwlWalSpinFlag = true;
        break;
    }

    // Power Cruising
    case ITEM_POWER_CRUISING_BOOST: {
        mJskBoostFlag = true;
        break;
    }
    case ITEM_POWER_CRUISING_RING_TIMER: {
        mJskRingTimerFlag.SetFirstUnset();
        break;
    }
    case ITEM_POWER_CRUISING_DOUBLE_RING: {
        mJsk2xRingFlag = true;
        break;
    }
    case ITEM_POWER_CRUISING_FREE_CRUISING_TIMER: {
        mJskFreeTimerFlag.SetFirstUnset();
        break;
    }

    // Canoeing
    case ITEM_CANOEING_TIMER: {
        mCanTimerFlag.SetFirstUnset();
        break;
    }
    case ITEM_CANOEING_BEGINNER: {
    case ITEM_CANOEING_INTERMEDIATE:
    case ITEM_CANOEING_EXPERT:
        mCanStageFlag.SetBit(id - ITEM_CANOEING_BEGINNER);
        break;
    }

    // Cycling
    case ITEM_CYCLING_HEART: {
        mBicHeartFlag.SetFirstUnset();
        break;
    }
    case ITEM_CYCLING_STAGE_0: {
    case ITEM_CYCLING_STAGE_1:
    case ITEM_CYCLING_STAGE_2:
    case ITEM_CYCLING_STAGE_3:
    case ITEM_CYCLING_STAGE_4:
    case ITEM_CYCLING_STAGE_5:
    case ITEM_CYCLING_STAGE_6:
    case ITEM_CYCLING_STAGE_7:
        mBicStageFlag.SetBit(id - ITEM_CYCLING_STAGE_0);
        break;
    }

    // Skydiving
    case ITEM_SKYDIVING_MII: {
        mOmkMiiFlag.SetFirstUnset();
        break;
    }

    // Air Sports
    case ITEM_ISLAND_FLYOVER_TIMER: {
        mPlnTimerFlag.SetFirstUnset();
        break;
    }
    case ITEM_ISLAND_FLYOVER_DAY: {
    case ITEM_ISLAND_FLYOVER_EVENING:
    case ITEM_ISLAND_FLYOVER_NIGHT:
        mPlnStageFlag.SetBit(id - ITEM_ISLAND_FLYOVER_DAY);
        break;
    }
    case ITEM_ISLAND_FLYOVER_DOUBLE_BLASTERS: {
        mPlnDoubleBlastersFlag = true;
        break;
    }
    case ITEM_ISLAND_FLYOVER_NIGHT_LIGHTS: {
        mPlnNightLightsFlag = true;
        break;
    }
    case ITEM_ISLAND_FLYOVER_UNLOCK_BALLOONS: {
        mPlnBalloonsFlag = true;
        break;
    }
    case ITEM_ISLAND_FLYOVER_UNLOCK_TWO_SEATER: {
        mPlnTwoSeaterPlaneFlag = true;
        break;
    }
    case ITEM_ISLAND_FLYOVER_UNLOCK_BOOST: {
        mPlnBoostFlag = true;
        break;
    }
    case ITEM_ISLAND_FLYOVER_UNLOCK_BRAKE: {
        mPlnBrakeFlag = true;
        break;
    }
    case ITEM_XP_SPEED_SLICE: {
        // TODO: implement
        break;
    }
    case ITEM_XP_SHOWDOWN: {
        // TODO: implement
        break;
    }
    case ITEM_XP_WAKEBOARDING: {
        // TODO: implement
        break;
    }
    case ITEM_XP_FRISBEE_DOG: {
        // TODO: implement
        break;
    }
    case ITEM_XP_ARCHERY: {
        // TODO: implement
        break;
    }
    case ITEM_XP_3PC: {
        // TODO: implement
        break;
    }
    case ITEM_XP_PICKUP_GAME: {
        // TODO: implement
        break;
    }
    case ITEM_XP_RETURN_CHALLENGE: {
        // TODO: implement
        break;
    }
    case ITEM_XP_MATCH: {
        // TODO: implement
        break;
    }
    case ITEM_XP_GOLF: {
        // TODO: implement
        break;
    }
    case ITEM_XP_BOWLING_STD: {
        // TODO: implement
        break;
    }
    case ITEM_XP_BOWLING_HUNDRED: {
        // TODO: implement
        break;
    }
    case ITEM_XP_BOWLING_SPIN_CONTROL: {
        // TODO: implement
        break;
    }
    case ITEM_XP_POWER_CRUISING: {
        // TODO: implement
        break;
    }
    case ITEM_XP_CANOEING: {
        // TODO: implement
        break;
    }
    case ITEM_XP_CYCLING: {
        // TODO: implement
        break;
    }
    case ITEM_XP_SKYDIVING: {
        // TODO: implement
        break;
    }
    case ITEM_SWORDPLAY_SHOWDOWN_EXTRA_HEART: {
        // TODO: implement
        break;
    }
    case ITEM_CYCLING_EXTRA_HEART: {
        // TODO: implement
        break;
    }
    case ITEM_RANDOM_COSMETIC: {
        // TODO: implement
        break;
    }


    default: {
        ASSERT_EX(false, "Unknown ItemID: %d", id);
        break;
    }
    }
}

} // namespace Cmn
} // namespace AP
