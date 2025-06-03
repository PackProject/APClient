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
 * @param rBin Binary file contents
 */
void ItemMgr::DeserializeImpl(const Bin& rBin) {
    ;
}

/**
 * @brief Serializes binary contents (internal implementation)
 *
 * @param rBin Binary file contents
 */
void ItemMgr::SerializeImpl(Bin& rBin) const {
    ;
}

const char* ItemMgr::GetItemName(ItemMgr::ItemID id) {
    switch (id) {
    case SWORDPLAY_DUEL_SPORT_UNLOCK:
        return "Swordplay Duel Sport Unlock";
    case SWORDPLAY_SPEED_SLICE_SPORT_UNLOCK:
        return "Swordplay Speed Slice Sport Unlock";
    case SWORDPLAY_SHOWDOWN_SPORT_UNLOCK:
        return "Swordplay Showdown Sport Unlock";
    case WAKEBOARDING_SPORT_UNLOCK:
        return "Wakeboarding Sport Unlock";
    case FRISBEE_DOG_SPORT_UNLOCK:
        return "Frisbee Dog Sport Unlock";
    case FRISBEE_GOLF_SPORT_UNLOCK:
        return "Frisbee Golf Sport Unlock";
    case ARCHERY_SPORT_UNLOCK:
        return "Archery Sport Unlock";
    case BASKETBALL_3POINT_CONTEST_SPORT_UNLOCK:
        return "Basketball 3 Point Contest Sport Unlock";
    case BASKETBALL_PICKUP_GAME_SPORT_UNLOCK:
        return "Basketball Pickup Game Sport Unlock";
    case TABLE_TENNIS_MATCH_SPORT_UNLOCK:
        return "Table Tennis Match Sport Unlock";
    case TABLE_TENNIS_RETURN_CHALLENGE_SPORT_UNLOCK:
        return "Table Tennis Return Challenge Sport Unlock";
    case GOLF_SPORT_UNLOCK:
        return "Golf Sport Unlock";
    case BOWLING_STANDARD_GAME_SPORT_UNLOCK:
        return "Bowling Standard Game Sport Unlock";
    case BOWLING_100_PIN_GAME_SPORT_UNLOCK:
        return "Bowling 100 Pin Game Sport Unlock";
    case BOWLING_SPIN_CONTROL_SPORT_UNLOCK:
        return "Bowling Spin Control Sport Unlock";
    case POWER_CRUISING_SPORT_UNLOCK:
        return "Power Cruising Sport Unlock";
    case CANOEING_SPEED_CHALLENGE_SPORT_UNLOCK:
        return "Canoeing Speed Challenge Sport Unlock";
    case CYCLING_SINGLE_RACE_UNLOCK:
        return "Cycling Single Race Unlock";
    case AIRSPORTS_SKYDIVING_UNLOCK:
        return "Air Sports Skydiving Unlock";
    case AIRSPORTS_ISLAND_FLYOVER_UNLOCK:
        return "Air Sports Island Flyover Unlock";
    case SWORDPLAY_CATEGORY_UNLOCK:
        return "Swordplay Category Unlock";
    case WAKEBOARD_CATEGORY_UNLOCK:
        return "Wakeboard Category Unlock";
    case FRISBEE_CATEGORY_UNLOCK:
        return "Frisbee Category Unlock";
    case ARCHERY_CATEGORY_UNLOCK:
        return "Archery Category Unlock";
    case BASKETBALL_CATEGORY_UNLOCK:
        return "Basketball Category Unlock";
    case TABLE_TENNIS_CATEGORY_UNLOCK:
        return "Table Tennis Category Unlock";
    case GOLF_CATEGORY_UNLOCK:
        return "Golf Category Unlock";
    case BOWLING_CATEGORY_UNLOCK:
        return "Bowling Category Unlock";
    case POWER_CRUISING_CATEGORY_UNLOCK:
        return "Power Cruising Category Unlock";
    case CANOEING_CATEGORY_UNLOCK:
        return "Canoeing Category Unlock";
    case CYCLING_CATEGORY_UNLOCK:
        return "Cycling Category Unlock";
    case AIRSPORTS_CATEGORY_UNLOCK:
        return "Air Sports Category Unlock";
    case SWORDPLAY_DUEL_BLOCK:
        return "Swordplay Duel Block";
    case SWORDPLAY_SPEED_SLICE_PAUSE:
        return "Swordplay Speed Slice Pause";
    case SWORDPLAY_SHOWDOWN_BLOCK:
        return "Swordplay Showdown Block";
    case SWORDPLAY_SHOWDOWN_HEART:
        return "Swordplay Showdown Heart";
    case SWORDPLAY_SHOWDOWN_STAGE_1:
        return "Swordplay Showdown Stage 1";
    case SWORDPLAY_SHOWDOWN_STAGE_2:
        return "Swordplay Showdown Stage 2";
    case SWORDPLAY_SHOWDOWN_STAGE_3:
        return "Swordplay Showdown Stage 3";
    case SWORDPLAY_SHOWDOWN_STAGE_4:
        return "Swordplay Showdown Stage 4";
    case SWORDPLAY_SHOWDOWN_STAGE_5:
        return "Swordplay Showdown Stage 5";
    case SWORDPLAY_SHOWDOWN_STAGE_6:
        return "Swordplay Showdown Stage 6";
    case SWORDPLAY_SHOWDOWN_STAGE_7:
        return "Swordplay Showdown Stage 7";
    case SWORDPLAY_SHOWDOWN_STAGE_8:
        return "Swordplay Showdown Stage 8";
    case SWORDPLAY_SHOWDOWN_STAGE_9:
        return "Swordplay Showdown Stage 9";
    case SWORDPLAY_SHOWDOWN_STAGE_10:
        return "Swordplay Showdown Stage 10";
    case SWORDPLAY_SHOWDOWN_STAGE_11:
        return "Swordplay Showdown Stage 11";
    case SWORDPLAY_SHOWDOWN_STAGE_12:
        return "Swordplay Showdown Stage 12";
    case SWORDPLAY_SHOWDOWN_STAGE_13:
        return "Swordplay Showdown Stage 13";
    case SWORDPLAY_SHOWDOWN_STAGE_14:
        return "Swordplay Showdown Stage 14";
    case SWORDPLAY_SHOWDOWN_STAGE_15:
        return "Swordplay Showdown Stage 15";
    case SWORDPLAY_SHOWDOWN_STAGE_16:
        return "Swordplay Showdown Stage 16";
    case SWORDPLAY_SHOWDOWN_STAGE_17:
        return "Swordplay Showdown Stage 17";
    case SWORDPLAY_SHOWDOWN_STAGE_18:
        return "Swordplay Showdown Stage 18";
    case SWORDPLAY_SHOWDOWN_STAGE_19:
        return "Swordplay Showdown Stage 19";
    case SWORDPLAY_SHOWDOWN_STAGE_20:
        return "Swordplay Showdown Stage 20";
    case WAKEBOARDING_TIMER:
        return "Wakeboarding Timer";
    case WAKEBOARDING_BEGINNER:
        return "Wakeboarding Beginner";
    case WAKEBOARDING_INTERMEDIATE:
        return "Wakeboarding Intermediate";
    case WAKEBOARDING_EXPERT:
        return "Wakeboarding Expert";
    case FRISBEE_DOG_FRISBEES:
        return "Frisbee Dog Frisbees";
    case FRISBEE_DOG_SECRET_POP:
        return "Frisbee Dog Secret Pop";
    case FRISBEE_GOLF_HUD:
        return "Frisbee Golf Hud";
    case FRISBEE_GOLF_DRIVER:
        return "Frisbee Golf Driver";
    case FRISBEE_GOLF_MIDRANGE:
        return "Frisbee Golf Midrange";
    case FRISBEE_GOLF_PUTTER:
        return "Frisbee Golf Putter";
    case FRISBEE_GOLF_COURSE_0:
        return "Frisbee Golf Course 0";
    case FRISBEE_GOLF_COURSE_1:
        return "Frisbee Golf Course 1";
    case FRISBEE_GOLF_COURSE_2:
        return "Frisbee Golf Course 2";
    case FRISBEE_GOLF_COURSE_3:
        return "Frisbee Golf Course 3";
    case FRISBEE_GOLF_COURSE_4:
        return "Frisbee Golf Course 4";
    case FRISBEE_GOLF_COURSE_5:
        return "Frisbee Golf Course 5";
    case FRISBEE_GOLF_COURSE_6:
        return "Frisbee Golf Course 6";
    case FRISBEE_GOLF_COURSE_7:
        return "Frisbee Golf Course 7";
    case FRISBEE_GOLF_COURSE_8:
        return "Frisbee Golf Course 8";
    case FRISBEE_GOLF_COURSE_9:
        return "Frisbee Golf Course 9";
    case ARCHERY_AIM_CIRCLE:
        return "Archery Aim Circle";
    case ARCHERY_ARROW:
        return "Archery Arrow";
    case ARCHERY_FRUIT_BEGINNER:
        return "Archery Fruit Beginner";
    case ARCHERY_FRUIT_INTERMEDIATE:
        return "Archery Fruit Intermediate";
    case ARCHERY_FRUIT_EXPERT:
        return "Archery Fruit Expert";
    case ARCHERY_BEGINNER:
        return "Archery Beginner";
    case ARCHERY_INTERMEDIATE:
        return "Archery Intermediate";
    case ARCHERY_EXPERT:
        return "Archery Expert";
    case BASKETBALL_3PT_TIMER:
        return "Basketball 3PT Timer";
    case BASKETBALL_BONUS_BALLS:
        return "Basketball Bonus Balls";
    case BASKETBALL_PICKUP_TIMER:
        return "Basketball Pickup Timer";
    case BASKETBALL_PASS:
        return "Basketball Pass";
    case BASKETBALL_3PTS:
        return "Basketball 3PTS";
    case BASKETBALL_DUNK:
        return "Basketball Dunk";
    case TABLE_TENNIS_SPIN:
        return "Table Tennis Spin";
    case TABLE_TENNIS_SMASH:
        return "Table Tennis Smash";
    case TABLE_TENNIS_CANS:
        return "Table Tennis Cans";
    case GOLF_HUD:
        return "Golf Hud";
    case GOLF_DRIVER:
        return "Golf Driver";
    case GOLF_3_WOOD:
        return "Golf 3 Wood";
    case GOLF_3_IRON:
        return "Golf 3 Iron";
    case GOLF_5_IRON:
        return "Golf 5 Iron";
    case GOLF_7_IRON:
        return "Golf 7 Iron";
    case GOLF_9_IRON:
        return "Golf 9 Iron";
    case GOLF_WEDGE:
        return "Golf Wedge";
    case GOLF_PUTTER:
        return "Golf Putter";
    case GOLF_TURN:
        return "Golf Turn";
    case GOLF_BACKSPIN:
        return "Golf Backspin";
    case GOLF_COURSE_0:
        return "Golf Course 0";
    case GOLF_COURSE_1:
        return "Golf Course 1";
    case GOLF_COURSE_2:
        return "Golf Course 2";
    case GOLF_COURSE_3:
        return "Golf Course 3";
    case GOLF_COURSE_4:
        return "Golf Course 4";
    case GOLF_COURSE_5:
        return "Golf Course 5";
    case GOLF_COURSE_6:
        return "Golf Course 6";
    case GOLF_COURSE_7:
        return "Golf Course 7";
    case GOLF_COURSE_8:
        return "Golf Course 8";
    case GOLF_COURSE_9:
        return "Golf Course 9";
    case GOLF_VIEW_LOW:
        return "Golf View Low";
    case GOLF_VIEW_SLOPE:
        return "Golf View Slope";
    case BOWLING_10_PIN_MOVE:
        return "Bowling 10 Pin Move";
    case BOWLING_10_PIN_TURN:
        return "Bowling 10 Pin Turn";
    case BOWLING_10_PIN_SPIN:
        return "Bowling 10 Pin Spin";
    case BOWLING_100_PIN_MOVE:
        return "Bowling 100 Pin Move";
    case BOWLING_100_PIN_TURN:
        return "Bowling 100 Pin Turn";
    case BOWLING_100_PIN_SPIN:
        return "Bowling 100 Pin Spin";
    case BOWLING_100_PIN_SECRET_STRIKE:
        return "Bowling 100 Pin Secret Strike";
    case BOWLING_SPIN_CONTROL_MOVE:
        return "Bowling Spin Control Move";
    case BOWLING_SPIN_CONTROL_TURN:
        return "Bowling Spin Control Turn";
    case BOWLING_SPIN_CONTROL_SPIN:
        return "Bowling Spin Control Spin";
    case POWER_CRUISING_BOOST:
        return "Power Cruising Boost";
    case POWER_CRUISING_RING_TIMER:
        return "Power Cruising Ring Timer";
    case POWER_CRUISING_DOUBLE_RING:
        return "Power Cruising Double Ring";
    case POWER_CRUISING_FREE_CRUISING_TIMER:
        return "Power Cruising Free Cruising Timer";
    case CANOEING_TIMER:
        return "Canoeing Timer";
    case CANOEING_BEGINNER:
        return "Canoeing Beginner";
    case CANOEING_INTERMEDIATE:
        return "Canoeing Intermediate";
    case CANOEING_EXPERT:
        return "Canoeing Expert";
    case CYCLING_HEART:
        return "Cycling Heart";
    case CYCLING_STAGE_0:
        return "Cycling Stage 0";
    case CYCLING_STAGE_1:
        return "Cycling Stage 1";
    case CYCLING_STAGE_2:
        return "Cycling Stage 2";
    case CYCLING_STAGE_3:
        return "Cycling Stage 3";
    case CYCLING_STAGE_4:
        return "Cycling Stage 4";
    case CYCLING_STAGE_5:
        return "Cycling Stage 5";
    case CYCLING_STAGE_6:
        return "Cycling Stage 6";
    case CYCLING_STAGE_7:
        return "Cycling Stage 7";
    case SKYDIVING_MII:
        return "Skydiving Mii";
    case ISLAND_FLYOVER_TIMER:
        return "Island Flyover Timer";
    case ISLAND_FLYOVER_DAY:
        return "Island Flyover Day";
    case ISLAND_FLYOVER_EVENING:
        return "Island Flyover Evening";
    case ISLAND_FLYOVER_NIGHT:
        return "Island Flyover Night";
    case ISLAND_FLYOVER_DOUBLE_BLASTERS:
        return "Island Flyover Double Blasters";
    case ISLAND_FLYOVER_NIGHT_LIGHTS:
        return "Island Flyover Night Lights";
    case ISLAND_FLYOVER_UNLOCK_BALLOONS:
        return "Island Flyover Unlock Balloons";
    case ISLAND_FLYOVER_UNLOCK_TWO_SEATER:
        return "Island Flyover Unlock Two Seater";
    case ISLAND_FLYOVER_UNLOCK_BOOST:
        return "Island Flyover Unlock Boosting";
    case ISLAND_FLYOVER_UNLOCK_BRAKE:
        return "Island Flyover Unlock Braking";

    default:
        kiwi::cout << "Unknown ID" << kiwi::endl;
    }
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
    //mJskBoostFlag = r.CoinFlip();
    mJskRingTimerFlag.Randomize();
    mJsk2xRingFlag = r.CoinFlip();
    mJskFreeTimerFlag.Randomize();
    mJskStageFlag.Randomize();

    // Canoeing
    mCanTimerFlag.Randomize();
    mCanStageFlag.Randomize();

    mCanTimerFlag.SetAll();

    // Cycling
    mBicHeartFlag.Randomize();
    mBicStageFlag.Randomize();

    // Skydiving
    mOmkMiiFlag.Randomize();

    // Air Sports
    mPlnTimerFlag.Randomize();
    mPlnStageFlag.Randomize();
    //mPlnDoubleBlastersFlag = r.CoinFlip();
    //mPlnNightLightsFlag = r.CoinFlip();
    //mPlnBalloonsFlag = r.CoinFlip();
    //mPlnTwoSeaterPlaneFlag = r.CoinFlip();
    //mPlnBoostFlag = r.CoinFlip();
    //mPlnBrakeFlag = r.CoinFlip();
}

} // namespace AP
