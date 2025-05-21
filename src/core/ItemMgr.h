#ifndef APCLIENT_CORE_ITEM_MGR_H
#define APCLIENT_CORE_ITEM_MGR_H
#include <types.h>

#include "core/const.h"

#include <Sports2/Sp2Cmn.h>

#include <libkiwi.h>

namespace AP {

/**
 * @brief Archipelago item manager
 */
class ItemMgr : public kiwi::DynamicSingleton<ItemMgr>, public kiwi::IBinary {
    friend class kiwi::DynamicSingleton<ItemMgr>;

public:
    enum ItemID {
        // Main Menu
        SWORDPLAY_DUEL_SPORT_UNLOCK = 0x0000,
        SWORDPLAY_SPEED_SLICE_SPORT_UNLOCK = 0x0001,
        SWORDPLAY_SHOWDOWN_SPORT_UNLOCK = 0x0002,
        WAKEBOARDING_SPORT_UNLOCK = 0x0003,
        FRISBEE_DOG_SPORT_UNLOCK = 0x0004,
        FRISBEE_GOLF_SPORT_UNLOCK = 0x0005,
        ARCHERY_SPORT_UNLOCK = 0x0006,
        BASKETBALL_3POINT_CONTEST_SPORT_UNLOCK = 0x0007,
        BASKETBALL_PICKUP_GAME_SPORT_UNLOCK = 0x0008,
        TABLE_TENNIS_MATCH_SPORT_UNLOCK = 0x0009,
        TABLE_TENNIS_RETURN_CHALLENGE_SPORT_UNLOCK = 0x000A,
        GOLF_SPORT_UNLOCK = 0x000B,
        BOWLING_STANDARD_GAME_SPORT_UNLOCK = 0x000C,
        BOWLING_100_PIN_GAME_SPORT_UNLOCK = 0x000D,
        BOWLING_SPIN_CONTROL_SPORT_UNLOCK = 0x000E,
        POWER_CRUISING_SPORT_UNLOCK = 0x000F,
        CANOEING_SPEED_CHALLENGE_SPORT_UNLOCK = 0x0010,
        CYCLING_SINGLE_RACE_UNLOCK = 0x0011,
        AIRSPORTS_SKYDIVING_UNLOCK = 0x0012,
        AIRSPORTS_ISLAND_FLYOVER_UNLOCK = 0x0013,
        SWORDPLAY_CATEGORY_UNLOCK = 0x0014,
        WAKEBOARD_CATEGORY_UNLOCK = 0x0015,
        FRISBEE_CATEGORY_UNLOCK = 0x0016,
        ARCHERY_CATEGORY_UNLOCK = 0x0017,
        BASKETBALL_CATEGORY_UNLOCK = 0x0018,
        TABLE_TENNIS_CATEGORY_UNLOCK = 0x0019,
        GOLF_CATEGORY_UNLOCK = 0x001A,
        BOWLING_CATEGORY_UNLOCK = 0x001B,
        POWER_CRUISING_CATEGORY_UNLOCK = 0x001C,
        CANOEING_CATEGORY_UNLOCK = 0x001D,
        CYCLING_CATEGORY_UNLOCK = 0x001E,
        AIRSPORTS_CATEGORY_UNLOCK = 0x001F,

        //Swordplay Duel
        SWORDPLAY_DUEL_BLOCK = 0x0100,

        //Swordplay Speed Slice
        SWORDPLAY_SPEED_SLICE_PAUSE = 0x0200,

        //Swordplay Showdown
        SWORDPLAY_SHOWDOWN_BLOCK = 0x0300,
        SWORDPLAY_SHOWDOWN_HEART = 0x0301,
        SWORDPLAY_SHOWDOWN_STAGE_1 = 0x0302,
        SWORDPLAY_SHOWDOWN_STAGE_2 = 0x0303,
        SWORDPLAY_SHOWDOWN_STAGE_3 = 0x0304,
        SWORDPLAY_SHOWDOWN_STAGE_4 = 0x0305,
        SWORDPLAY_SHOWDOWN_STAGE_5 = 0x0306,
        SWORDPLAY_SHOWDOWN_STAGE_6 = 0x0307,
        SWORDPLAY_SHOWDOWN_STAGE_7 = 0x0308,
        SWORDPLAY_SHOWDOWN_STAGE_8 = 0x0309,
        SWORDPLAY_SHOWDOWN_STAGE_9 = 0x030A,
        SWORDPLAY_SHOWDOWN_STAGE_10 = 0x030B,
        SWORDPLAY_SHOWDOWN_STAGE_11 = 0x030C,
        SWORDPLAY_SHOWDOWN_STAGE_12 = 0x030D,
        SWORDPLAY_SHOWDOWN_STAGE_13 = 0x030E,
        SWORDPLAY_SHOWDOWN_STAGE_14 = 0x030F,
        SWORDPLAY_SHOWDOWN_STAGE_15 = 0x0310,
        SWORDPLAY_SHOWDOWN_STAGE_16 = 0x0311,
        SWORDPLAY_SHOWDOWN_STAGE_17 = 0x0312,
        SWORDPLAY_SHOWDOWN_STAGE_18 = 0x0313,
        SWORDPLAY_SHOWDOWN_STAGE_19 = 0x0314,
        SWORDPLAY_SHOWDOWN_STAGE_20 = 0x0315,

        //Wakeboarding
        WAKEBOARDING_TIMER = 0x0400,
        WAKEBOARDING_BEGINNER = 0x0401,
        WAKEBOARDING_INTERMEDIATE = 0x0402,
        WAKEBOARDING_EXPERT = 0x0403,

        //Frisbee Dog
        FRISBEE_DOG_FRISBEES = 0x0500,
        FRISBEE_DOG_SECRET_POP = 0x0501,

        //Frisbee Golf
        FRISBEE_GOLF_HUD = 0x0600,
        FRISBEE_GOLF_DRIVER = 0x0601,
        FRISBEE_GOLF_MIDRANGE = 0x0602,
        FRISBEE_GOLF_PUTTER = 0x0603,
        FRISBEE_GOLF_COURSE_0 = 0x0604,
        FRISBEE_GOLF_COURSE_1 = 0x0605,
        FRISBEE_GOLF_COURSE_2 = 0x0606,
        FRISBEE_GOLF_COURSE_3 = 0x0607,
        FRISBEE_GOLF_COURSE_4 = 0x0608,
        FRISBEE_GOLF_COURSE_5 = 0x0609,
        FRISBEE_GOLF_COURSE_6 = 0x060A,
        FRISBEE_GOLF_COURSE_7 = 0x060B,
        FRISBEE_GOLF_COURSE_8 = 0x060C,
        FRISBEE_GOLF_COURSE_9 = 0x060D,

        //Archery
        ARCHERY_AIM_CIRCLE = 0x0700,
        ARCHERY_ARROW = 0x0701,
        ARCHERY_FRUIT_BEGINNER = 0x702,
        ARCHERY_FRUIT_INTERMEDIATE = 0x703,
        ARCHERY_FRUIT_EXPERT = 0x704,
        ARCHERY_BEGINNER = 0x705,
        ARCHERY_INTERMEDIATE = 0x706,
        ARCHERY_EXPERT = 0x707,

        //Basketball 3-Point Contest
        BASKETBALL_3PT_TIMER = 0x0800,
        BASKETBALL_BONUS_BALLS = 0x0801,

        //Basketball Pickup Game
        BASKETBALL_PICKUP_TIMER = 0x0900,
        BASKETBALL_PASS = 0x0901,
        BASKETBALL_3PTS = 0x0902,
        BASKETBALL_DUNK = 0x0903,

        //Table Tennis
        TABLE_TENNIS_SPIN = 0x0A00,
        TABLE_TENNIS_SMASH = 0x0A01,
        TABLE_TENNIS_CANS = 0x0A02,

        //Golf
        GOLF_HUD = 0x0B00,
        GOLF_DRIVER = 0x0B01,
        GOLF_3_WOOD = 0x0B02,
        GOLF_3_IRON = 0x0B03,
        GOLF_5_IRON = 0x0B04,
        GOLF_7_IRON = 0x0B05,
        GOLF_9_IRON = 0x0B06,
        GOLF_WEDGE = 0x0B07,
        GOLF_PUTTER = 0x0B08,
        GOLF_TURN = 0x0B09,
        GOLF_BACKSPIN = 0x0B0A,
        GOLF_COURSE_0 = 0x0B0B,
        GOLF_COURSE_1 = 0x0B0C,
        GOLF_COURSE_2 = 0x0B0D,
        GOLF_COURSE_3 = 0x0B0E,
        GOLF_COURSE_4 = 0x0B0F,
        GOLF_COURSE_5 = 0x0B10,
        GOLF_COURSE_6 = 0x0B11,
        GOLF_COURSE_7 = 0x0B12,
        GOLF_COURSE_8 = 0x0B13,
        GOLF_COURSE_9 = 0x0B14,
        GOLF_VIEW_LOW = 0x0B15,
        GOLF_VIEW_SLOPE = 0x0B16,

        //Bowling 10 Pin
        BOWLING_10_PIN_MOVE = 0x0C00,
        BOWLING_10_PIN_TURN = 0x0C01,
        BOWLING_10_PIN_SPIN = 0x0C02,

        //Bowling 100 Pin
        BOWLING_100_PIN_MOVE = 0x0D00,
        BOWLING_100_PIN_TURN = 0x0D01,
        BOWLING_100_PIN_SPIN = 0x0D02,
        BOWLING_100_PIN_SECRET_STRIKE = 0x0D03,

        //Bowling Spin Control
        BOWLING_SPIN_CONTROL_MOVE = 0x0E00,
        BOWLING_SPIN_CONTROL_TURN = 0x0E01,
        BOWLING_SPIN_CONTROL_SPIN = 0x0E02,

        //Power Cruising
        POWER_CRUISING_BOOST = 0x0F00,
        POWER_CRUISING_RING_TIMER = 0x0F01,
        POWER_CRUISING_DOUBLE_RING = 0x0F02,
        POWER_CRUISING_FREE_CRUISING_TIMER = 0x0F03,

        //Canoeing
        CANOEING_TIMER = 0x1000,
        CANOEING_BEGINNER = 0x1001,
        CANOEING_INTERMEDIATE = 0x1002,
        CANOEING_EXPERT = 0x1003,

        //Cycling
        CYCLING_HEART = 0x1100,
        CYCLING_STAGE_0 = 0x1101,
        CYCLING_STAGE_1 = 0x1102,
        CYCLING_STAGE_2 = 0x1103,
        CYCLING_STAGE_3 = 0x1104,
        CYCLING_STAGE_4 = 0x1105,
        CYCLING_STAGE_5 = 0x1106,
        CYCLING_STAGE_6 = 0x1107,
        CYCLING_STAGE_7 = 0x1108,

        // Skydiving
        SKYDIVING_MII = 0x1200,

        // Island Flyover
        ISLAND_FLYOVER_TIMER = 0x1300,
        ISLAND_FLYOVER_DAY = 0x1301,
        ISLAND_FLYOVER_EVENING = 0x1302,
        ISLAND_FLYOVER_NIGHT = 0x1303,
        ISLAND_FLYOVER_DOUBLE_BLASTERS = 0x1304,
        ISLAND_FLYOVER_NIGHT_LIGHTS = 0x1305,
        ISLAND_FLYOVER_UNLOCK_BALLOONS = 0x1306,
        ISLAND_FLYOVER_UNLOCK_TWO_SEATER = 0x1307,

        FINAL_ITEM_ID
    };

public:
    const char* GetItemName (ItemID itemID);

public:
    /**
     * @brief Sets debug state
     */
    void Debug();

    /**
     * @name Main Menu
     */
    /**@{*/
    bool IsSportUnlock(ESport sport) {
        return mSportFlag.GetBit(sport);
    }
    bool IsCategoryUnlock(Sp2::Cmn::ESaveSeq seq) const {
        return mCategoryFlag.GetBit(seq);
    }
    /**@}*/

    /**
     * @name Swordplay (Duel)
     */
    /**@{*/
    bool IsSwfVsBlock() const {
        return mSwfVsBlockFlag;
    }
    /**@}*/

    /**
     * @name Swordplay (Speed Slice)
     */
    /**@{*/
    bool IsSwfPrcPause() const {
        return mSwfPrcPauseFlag;
    }
    /**@}*/

    /**
     * @name Swordplay (Showdown)
     */
    /**@{*/
    //! Number of heart items
    static const u32 SWF_SGL_HEART_COUNT = 3;
    //! Number of stage unlock items
    static const u32 SWF_SGL_STAGE_COUNT = 10 * 2;

    bool IsSwfSglBlock() const {
        return mSwfSglBlockFlag;
    }
    u32 GetSwfSglHeartNum() const {
        return mSwfSglHeartFlag.Count();
    }
    bool IsSwfSglStageUnlock(u32 id) const {
        return mSwfSglStageFlag.GetBit(id);
    }
    /**@}*/

    /**
     * @name Wakeboarding
     */
    /**@{*/
    //! Number of timer items
    static const u32 WKB_TIMER_COUNT = 3;
    //! Number of stage unlock items
    static const u32 WKB_STAGE_COUNT = 3;
    //! Timer increment (in seconds)
    static const u32 WKB_TIMER_VALUE = 24;

    u32 GetWkbTimerNum() const {
        return mWkbTimerFlag.Count();
    }
    bool IsWkbStageUnlock(u32 id) const {
        return mWkbStageFlag.GetBit(id);
    }
    /**@}*/

    /**
     * @name Frisbee Dog
     */
    /**@{*/
    //! Number of throw items
    static const u32 FLD_THROW_COUNT = 10;

    u32 GetFldThrowNum() const {
        return mFldThrowFlag.Count();
    }
    bool IsFldSecretPop() const {
        return mFldSecretPopFlag;
    }
    /**@}*/

    /**
     * @name Frisbee Golf
     */
    /**@{*/
    //! Number of frisbee items
    static const u32 DGL_DISC_COUNT = 3;
    //! Number of stage items
    static const u32 DGL_STAGE_COUNT = 10;

    bool IsDglHUD() const {
        return mDglHUDFlag;
    }
    u32 GetDglDiscNum() const {
        return mDglDiscFlag.Count();
    }
    bool IsDglStageUnlock(u32 id) const {
        return mDglStageFlag.GetBit(id);
    }
    /**@}*/

    /**
     * @name Archery
     */
    /**@{*/
    //! Number of arrow items
    static const u32 ARC_ARROW_COUNT = 3;
    //! Number of fruit items (1 per stage)
    static const u32 ARC_FRUIT_COUNT = 3;
    //! Number of stage items
    static const u32 ARC_STAGE_COUNT = 3;

    bool IsArcAim() const {
        return mArcAimFlag;
    }
    u32 GetArcArrowNum() const {
        return mArcArrowFlag.Count();
    }
    bool IsArcFruitUnlock(u32 id) const {
        return mArcFruitFlag.GetBit(id);
    }
    bool IsArcStageUnlock(u32 id) const {
        return mArcStageFlag.GetBit(id);
    }
    /**@}*/

    /**
     * @name Basketball (3-Point Contest)
     */
    /**@{*/
    //! Number of timer items
    static const u32 BSK_3PT_TIMER_COUNT = 5;
    //! Timer increment (in seconds)
    static const u32 BSK_3PT_TIMER_VALUE = 13;

    u32 GetBsk3ptTimerNum() const {
        return mBsk3ptTimerFlag.Count();
    }
    bool IsBsk3ptBonus() const {
        return mBsk3ptBonusFlag;
    }
    /**@}*/

    /**
     * @name Basketball (Pickup Game)
     */
    /**@{*/
    //! Number of timer items
    static const u32 BSK_VS_TIMER_COUNT = 5;
    //! Timer increment (in seconds)
    static const u32 BSK_VS_TIMER_VALUE = 36;

    u32 GetBskVsTimerNum() const {
        return mBskVsTimerFlag.Count();
    }
    bool IsBskVsPass() const {
        return mBskVsPassFlag;
    }
    bool IsBskVs3pt() const {
        return mBskVs3ptFlag;
    }
    bool IsBskVsDunk() const {
        return mBskVsDunkFlag;
    }
    /**@}*/

    /**
     * @name Table Tennis
     */
    /**@{*/
    bool IsPngSpin() const {
        return mPngSpinFlag;
    }
    bool IsPngSmash() const {
        return mPngSmashFlag;
    }
    bool IsPngCans() const {
        return mPngCansFlag;
    }
    /**@}*/

    /**
     * @name Golf
     */
    /**@{*/
    //! Number of club items
    static const u32 GLF_CLUB_COUNT = 8;
    //! Number of stage items
    static const u32 GLF_STAGE_COUNT = 10;

    bool IsGlfHUD() const {
        return mGlfHUDFlag;
    }
    bool IsGlfClubUnlock(u32 id) const {
        return mGlfClubFlag.GetBit(id);
    }
    int GetGlfMaxClubID() const {
        return mGlfClubFlag.Count();
    }
    bool IsGlfTurn() const {
        return mGlfTurnFlag;
    }
    bool IsGlfSpin() const {
        return mGlfSpinFlag;
    }
    bool IsGlfStageUnlock(u32 id) const {
        return mGlfStageFlag.GetBit(id);
    }
    bool IsGlfViewLow() const {
        return mGlfViewLowFlag;
    }
    bool IsGlfViewSlope() const {
        return mGlfViewSlopeFlag;
    }
    /**@}*/

    /**
     * @name Bowling (Standard Game)
     */
    /**@{*/
    bool IsBwlStdMove() const {
        return mBwlStdMoveFlag;
    }
    bool IsBwlStdTurn() const {
        return mBwlStdTurnFlag;
    }
    bool IsBwlStdSpin() const {
        return mBwlStdSpinFlag;
    }
    /**@}*/

    /**
     * @name Bowling (100-Pin Game)
     */
    /**@{*/
    bool IsBwl100Move() const {
        return mBwl100MoveFlag;
    }
    bool IsBwl100Turn() const {
        return mBwl100TurnFlag;
    }
    bool IsBwl100Spin() const {
        return mBwl100SpinFlag;
    }
    bool IsBwl100SecretBtn() const {
        return mBwl100SecretBtnFlag;
    }
    /**@}*/

    /**
     * @name Bowling (Spin Control)
     */
    /**@{*/
    bool IsBwlWalMove() const {
        return mBwlWalMoveFlag;
    }
    bool IsBwlWalTurn() const {
        return mBwlWalTurnFlag;
    }
    bool IsBwlWalSpin() const {
        return mBwlWalSpinFlag;
    }
    /**@}*/

    /**
     * @name Power Cruising
     */
    /**@{*/
    //! Number of timer items
    static const u32 JSK_RING_TIMER_COUNT = 2;
    //! Timer increment (in seconds)
    static const u32 JSK_RING_TIMER_VALUE = 4;

    //! Number of timer items
    static const u32 JSK_FREE_TIMER_COUNT = 6;
    //! Timer increment (in seconds)
    static const u32 JSK_FREE_TIMER_VALUE = 60;

    bool IsJskBoost() const {
        return mJskBoostFlag;
    }
    u32 GetJskRingTimerNum() const {
        return mJskRingTimerFlag.Count();
    }
    bool IsJsk2xRing() const {
        return mJsk2xRingFlag;
    }
    u32 GetJskFreeTimerNum() const {
        return mJskFreeTimerFlag.Count();
    }
    /**@}*/

    /**
     * @name Canoeing
     */
    /**@{*/
    //! Number of timer items
    static const u32 CAN_TIMER_COUNT = 6;
    //! Number of stage unlock items
    static const u32 CAN_STAGE_COUNT = 3;
    //! Timer increment (in seconds)
    static const u32 CAN_TIMER_VALUE = 20;

    u32 GetCanTimerNum() const {
        return mCanTimerFlag.Count();
    }
    bool IsCanStageUnlock(u32 id) const {
        return mCanStageFlag.GetBit(id);
    }
    /**@}*/

    /**
     * @name Cycling
     */
    /**@{*/
    //! Number of heart items
    static const u32 BIC_HEART_COUNT = 3;
    //! Number of stage unlock items
    static const u32 BIC_STAGE_COUNT = 8;

    u32 GetBicHeartNum() const {
        return mBicHeartFlag.Count();
    }
    bool IsBicStageUnlock(u32 id) const {
        return mBicStageFlag.GetBit(id);
    }
    /**@}*/

    /**
     * @name Skydiving
     */
    /**@{*/
    //! Number of mii items
    static const u32 OMK_MII_COUNT = 4; // random value, will need to be changed later

    u32 GetOmkMiiNum() const {
        return mOmkMiiFlag.Count();
    }
    /**@}*/

    /**
     * @name Island Flyover
     */
    /**@{*/
    //! Number of timer items
    static const u32 PLN_TIMER_COUNT = 6;
    //! Number of stage unlock items
    static const u32 PLN_STAGE_COUNT = 3;
    //! Timer increment (in seconds)
    static const u32 PLN_TIMER_VALUE = 50;

    u32 GetPlnTimerNum() const {
        return mPlnTimerFlag.Count();
    }
    bool IsPlnStageUnlock(u32 id) const {
        return mPlnStageFlag.GetBit(id);
    }
    bool IsPlnDoubleBlastersUnlock() const {
        return mPlnDoubleBlastersFlag;
    }
    bool IsPlnNightLightsUnlock() const {
        return mPlnNightLightsFlag;
    }
    bool IsPlnBalloonsUnlock() const {
        return mPlnBalloonsFlag;
    }
    bool IsPlnTwoSeaterUnlock() const {
        return mPlnTwoSeaterPlaneFlag;
    }
    /**@}*/

private:
    //! Binary file magic
    static const u32 SIGNATURE = 'ITEM';
    //! Binary file version
    static const int VERSION = K_VERSION(1, 0);
    //! Binary file path
    static const char* PATH;

private:
    /**
     * @brief Binary file structure
     */
#pragma pack(push, 1)
    struct Bin : kiwi::IBinary::Block {
        /* 0x00    */ u32 sportFlag;    //!< Unlocked sports
        /* 0x04    */ u32 categoryFlag; //!< Unlocked categories

        /* 0x08:0  */ u32 swfVsBlockFlag : 1;   //!< Blocking ability
        /* 0x08:1  */ u32 swfPrcPauseFlag : 1;  //!< Pausing ability
        /* 0x08:2  */ u32 swfSglBlockFlag : 1;  //!< Blocking ability
        /* 0x08:3  */ u32 swfSglHeartFlag : 3;  //!< Heart items
        /* 0x08:6  */ u32 swfSglStageFlag : 20; //!< Unlocked stages

        /* 0x0C:0  */ u8 wkbTimerFlag : 5; //!< Timer items
        /* 0x0C:4  */ u8 wkbStageFlag : 3; //!< Unlocked difficulties

        /* 0x0D:0  */ u16 fldThrowFlag : 10;     //!< Throw items
        /* 0x0D:4  */ u16 fldPopBalloonFlag : 1; //!< A+2 balloon pop ability

        /* 0x0F:0  */ u16 dglDiscFlag : 3;   //!< Progressive disc
        /* 0x0F:3  */ u16 dglStageFlag : 10; //!< Unlocked courses

        /* 0x10:0  */ u16 arcAimFlag : 1;   //!< Aiming circle
        /* 0x10:1  */ u16 arcArrowFlag : 3; //!< Arrow items
        /* 0x10:3  */ u16 arcFruitFlag : 3; //!< Hidden fruits
        /* 0x10:6  */ u16 arcStageFlag : 3; //!< Unlocked stages

        // . . .
    };
#pragma pack(pop)

private:
    /**
     * @brief Constructor
     */
    ItemMgr();

    /**
     * @brief Gets the kind/magic of this object
     */
    virtual u32 GetBinaryKind() const {
        return SIGNATURE;
    }
    /**
     * @brief Gets the serialized size of this object
     */
    virtual u32 GetBinarySize() const {
        return sizeof(Bin);
    }
    /**
     * @brief Gets the expected version of this object
     */
    virtual u16 GetVersion() const {
        return VERSION;
    }

    /**
     * @brief Deserializes binary contents (internal implementation)
     *
     * @param rHeader Binary file header
     */
    virtual void DeserializeImpl(const Header& rHeader);
    /**
     * @brief Serializes binary contents (internal implementation)
     *
     * @param rHeader Binary file header
     */
    virtual void SerializeImpl(Header& rHeader) const;

    /**
     * @brief Clears item state
     */
    void Clear();

private:
    /**
     * @name Main Menu
     */
    /**@{*/
    //! Unlocked sports
    kiwi::TBitFlag<u32, Sp2::Cmn::ESport_Max> mSportFlag;
    //! Unlocked categories
    kiwi::TBitFlag<u32, Sp2::Cmn::ESaveSeq_Max> mCategoryFlag;
    /**@}*/

    /**
     * @name Swordplay (Duel)
     */
    /**@{*/
    //! Blocking
    bool mSwfVsBlockFlag;
    /**@}*/

    /**
     * @name Swordplay (Speed Slice)
     */
    /**@{*/
    //! Pausing
    bool mSwfPrcPauseFlag;
    /**@}*/

    /**
     * @name Swordplay (Showdown)
     */
    /**@{*/
    //! Blocking
    bool mSwfSglBlockFlag;
    //! Heart items
    kiwi::TBitFlag<u32, SWF_SGL_HEART_COUNT> mSwfSglHeartFlag;
    //! Stage unlock items
    kiwi::TBitFlag<u32, SWF_SGL_STAGE_COUNT> mSwfSglStageFlag;
    /**@}*/

    /**
     * @name Wakeboarding
     */
    /**@{*/
    //! Timer items
    kiwi::TBitFlag<u32, WKB_TIMER_COUNT> mWkbTimerFlag;
    //! Stage unlock items
    kiwi::TBitFlag<u32, WKB_STAGE_COUNT> mWkbStageFlag;
    /**@}*/

    /**
     * @name Frisbee Dog
     */
    /**@{*/
    //! Throw items
    kiwi::TBitFlag<u32, FLD_THROW_COUNT> mFldThrowFlag;
    //! A+2 button combo to pop balloons
    bool mFldSecretPopFlag;
    /**@}*/

    /**
     * @name Frisbee Golf
     */
    /**@{*/
    //! Heads-up display
    bool mDglHUDFlag;
    //! Disc items (progressive)
    kiwi::TBitFlag<u32, DGL_DISC_COUNT> mDglDiscFlag;
    //! Stage unlock items
    kiwi::TBitFlag<u32, DGL_STAGE_COUNT> mDglStageFlag;
    /**@}*/

    /**
     * @name Archery
     */
    /**@{*/
    //! Aiming circle
    bool mArcAimFlag;
    //! Arrow items
    kiwi::TBitFlag<u32, ARC_ARROW_COUNT> mArcArrowFlag;
    //! Fruit unlock items
    kiwi::TBitFlag<u32, ARC_FRUIT_COUNT> mArcFruitFlag;
    //! Stage unlock items
    kiwi::TBitFlag<u32, ARC_STAGE_COUNT> mArcStageFlag;
    /**@}*/

    /**
     * @name Basketball (3-Point Contest)
     */
    /**@{*/
    //! Timer items
    kiwi::TBitFlag<u32, BSK_3PT_TIMER_COUNT> mBsk3ptTimerFlag;
    //! Bonus ball
    bool mBsk3ptBonusFlag;

    /**
     * @name Basketball (Pickup Game)
     */
    /**@{*/
    //! Timer items
    kiwi::TBitFlag<u32, BSK_VS_TIMER_COUNT> mBskVsTimerFlag;
    //! Passing
    bool mBskVsPassFlag;
    //! 3-point shots
    bool mBskVs3ptFlag;
    //! Dunking
    bool mBskVsDunkFlag;
    /**@}*/

    /**
     * @name Table Tennis
     */
    /**@{*/
    //! Spin
    bool mPngSpinFlag;
    //! Smash hit
    bool mPngSmashFlag;
    //! Return Challenge cans
    bool mPngCansFlag;
    /**@}*/

    /**
     * @name Golf
     */
    /**@{*/
    //! Heads-up display
    bool mGlfHUDFlag;
    //! Club items (progressive)
    kiwi::TBitFlag<u32, GLF_CLUB_COUNT> mGlfClubFlag;
    //! Turning
    bool mGlfTurnFlag;
    //! Backspin
    bool mGlfSpinFlag;
    //! Stage unlock items
    kiwi::TBitFlag<u32, GLF_STAGE_COUNT> mGlfStageFlag;
    //! Low-view when putting
    bool mGlfViewLowFlag;
    //! Slope view when putting
    bool mGlfViewSlopeFlag;
    /**@}*/

    /**
     * @name Bowling (Standard Game)
     */
    /**@{*/
    //! Moving
    bool mBwlStdMoveFlag;
    //! Turning
    bool mBwlStdTurnFlag;
    //! Spin
    bool mBwlStdSpinFlag;
    /**@}*/

    /**
     * @name Bowling (100-Pin Game)
     */
    /**@{*/
    //! Moving
    bool mBwl100MoveFlag;
    //! Turning
    bool mBwl100TurnFlag;
    //! Spin
    bool mBwl100SpinFlag;
    //! Secret strike button
    bool mBwl100SecretBtnFlag;
    /**@}*/

    /**
     * @name Bowling (Spin Control)
     */
    /**@{*/
    //! Moving
    bool mBwlWalMoveFlag;
    //! Turning
    bool mBwlWalTurnFlag;
    //! Spin
    bool mBwlWalSpinFlag;
    /**@}*/

    /**
     * @name Power Cruising
     */
    /**@{*/
    //! Boosting
    bool mJskBoostFlag;
    //! Ring timer items
    kiwi::TBitFlag<u32, JSK_RING_TIMER_COUNT> mJskRingTimerFlag;
    //! x2 ring multiplier
    bool mJsk2xRingFlag;
    //! Free cruising timer items
    kiwi::TBitFlag<u32, JSK_FREE_TIMER_COUNT> mJskFreeTimerFlag;
    /**@}*/

    /**
     * @name Canoeing
     */
    /**@{*/
    //! Timer items
    kiwi::TBitFlag<u32, CAN_TIMER_COUNT> mCanTimerFlag;
    //! Stage items
    kiwi::TBitFlag<u32, CAN_STAGE_COUNT> mCanStageFlag;
    /**@}*/

    /**
     * @name Cycling
     */
    /**@{*/
    //! Heart items
    kiwi::TBitFlag<u32, BIC_HEART_COUNT> mBicHeartFlag;
    //! Stage items
    kiwi::TBitFlag<u32, BIC_STAGE_COUNT> mBicStageFlag;
    /**@}*/

    /**
     * @name Skydiving
     */
    /**@{*/
    //! number of miis
    kiwi::TBitFlag<u32, OMK_MII_COUNT> mOmkMiiFlag;

    /**
     * @name Island Flyover
     */
    /**@{*/
    //! Timer items
    kiwi::TBitFlag<u32, PLN_TIMER_COUNT> mPlnTimerFlag;
    //! Stage items
    kiwi::TBitFlag<u32, PLN_STAGE_COUNT> mPlnStageFlag;
    //! Double blasters
    bool mPlnDoubleBlastersFlag;
    //! Light on at night
    bool mPlnNightLightsFlag;
    //! Unlocks Balloons
    bool mPlnBalloonsFlag;
    //! Two Seater Plane
    bool mPlnTwoSeaterPlaneFlag;
    /**@}*/

public:
    void GiveItemToPlayer(ItemID id) {
        kiwi::cout << "Adding Item: " << GetItemName(id) << kiwi::endl;

        switch(id) {
            case SWORDPLAY_DUEL_SPORT_UNLOCK: 
                mSportFlag.SetBit(0);
                break;
            case SWORDPLAY_SPEED_SLICE_SPORT_UNLOCK: 
                mSportFlag.SetBit(1);
                break;
            case SWORDPLAY_SHOWDOWN_SPORT_UNLOCK: 
                mSportFlag.SetBit(2);
                break;
            case WAKEBOARDING_SPORT_UNLOCK: 
                mSportFlag.SetBit(3);
                break;
            case FRISBEE_DOG_SPORT_UNLOCK: 
                mSportFlag.SetBit(4);
                break;
            case FRISBEE_GOLF_SPORT_UNLOCK: 
                mSportFlag.SetBit(5);
                break;
            case ARCHERY_SPORT_UNLOCK: 
                mSportFlag.SetBit(6);
                break;
            case BASKETBALL_3POINT_CONTEST_SPORT_UNLOCK: 
                mSportFlag.SetBit(7);
                break;
            case BASKETBALL_PICKUP_GAME_SPORT_UNLOCK: 
                mSportFlag.SetBit(8);
                break;
            case TABLE_TENNIS_MATCH_SPORT_UNLOCK: 
                mSportFlag.SetBit(9);
                break;
            case TABLE_TENNIS_RETURN_CHALLENGE_SPORT_UNLOCK: 
                mSportFlag.SetBit(10);
                break;
            case GOLF_SPORT_UNLOCK: 
                mSportFlag.SetBit(11);
                break;
            case BOWLING_STANDARD_GAME_SPORT_UNLOCK: 
                mSportFlag.SetBit(12);
                break;
            case BOWLING_100_PIN_GAME_SPORT_UNLOCK: 
                mSportFlag.SetBit(13);
                break;
            case BOWLING_SPIN_CONTROL_SPORT_UNLOCK: 
                mSportFlag.SetBit(14);
                break;
            case POWER_CRUISING_SPORT_UNLOCK: 
                mSportFlag.SetBit(15);
                break;
            case CANOEING_SPEED_CHALLENGE_SPORT_UNLOCK: 
                mSportFlag.SetBit(16);
                break;
            case CYCLING_SINGLE_RACE_UNLOCK: 
                mSportFlag.SetBit(17);
                break;
            case AIRSPORTS_SKYDIVING_UNLOCK: 
                mSportFlag.SetBit(18);
                break;
            case AIRSPORTS_ISLAND_FLYOVER_UNLOCK: 
                mSportFlag.SetBit(19);
                break;
            case SWORDPLAY_CATEGORY_UNLOCK: 
                mCategoryFlag.SetBit(0);
                break;
            case WAKEBOARD_CATEGORY_UNLOCK: 
                mCategoryFlag.SetBit(1);
                break;
            case FRISBEE_CATEGORY_UNLOCK: 
                mCategoryFlag.SetBit(2);
                break;
            case ARCHERY_CATEGORY_UNLOCK: 
                mCategoryFlag.SetBit(3);
                break;
            case BASKETBALL_CATEGORY_UNLOCK: 
                mCategoryFlag.SetBit(4);
                break;
            case TABLE_TENNIS_CATEGORY_UNLOCK: 
                mCategoryFlag.SetBit(5);
                break;
            case GOLF_CATEGORY_UNLOCK: 
                mCategoryFlag.SetBit(6);
                break;
            case BOWLING_CATEGORY_UNLOCK: 
                mCategoryFlag.SetBit(7);
                break;
            case POWER_CRUISING_CATEGORY_UNLOCK: 
                mCategoryFlag.SetBit(8);
                break;
            case CANOEING_CATEGORY_UNLOCK: 
                mCategoryFlag.SetBit(9);
                break;
            case CYCLING_CATEGORY_UNLOCK: 
                mCategoryFlag.SetBit(10);
                break;
            case AIRSPORTS_CATEGORY_UNLOCK: 
                mCategoryFlag.SetBit(11);
                break;
            case SWORDPLAY_DUEL_BLOCK: 
                mSwfVsBlockFlag = true;
                break;
            case SWORDPLAY_SPEED_SLICE_PAUSE: 
                mSwfPrcPauseFlag = true;
                break;
            case SWORDPLAY_SHOWDOWN_BLOCK: 
                mSwfVsBlockFlag = true;
                break;
            case SWORDPLAY_SHOWDOWN_HEART: 
                mSwfSglHeartFlag.AddMinBit();
                break;
            case SWORDPLAY_SHOWDOWN_STAGE_1: 
                mSwfSglStageFlag.SetBit(0);
                break;
            case SWORDPLAY_SHOWDOWN_STAGE_2: 
                mSwfSglStageFlag.SetBit(1);
                break;
            case SWORDPLAY_SHOWDOWN_STAGE_3: 
                mSwfSglStageFlag.SetBit(2);
                break;
            case SWORDPLAY_SHOWDOWN_STAGE_4: 
                mSwfSglStageFlag.SetBit(3);
                break;
            case SWORDPLAY_SHOWDOWN_STAGE_5: 
                mSwfSglStageFlag.SetBit(4);
                break;
            case SWORDPLAY_SHOWDOWN_STAGE_6: 
                mSwfSglStageFlag.SetBit(5);;
                break;
            case SWORDPLAY_SHOWDOWN_STAGE_7: 
                mSwfSglStageFlag.SetBit(6);
                break;
            case SWORDPLAY_SHOWDOWN_STAGE_8: 
                mSwfSglStageFlag.SetBit(7);;
                break;
            case SWORDPLAY_SHOWDOWN_STAGE_9: 
                mSwfSglStageFlag.SetBit(8);
                break;
            case SWORDPLAY_SHOWDOWN_STAGE_10: 
                mSwfSglStageFlag.SetBit(9);
                break;
            case SWORDPLAY_SHOWDOWN_STAGE_11: 
                mSwfSglStageFlag.SetBit(10);
                break;
            case SWORDPLAY_SHOWDOWN_STAGE_12: 
                mSwfSglStageFlag.SetBit(11);
                break;
            case SWORDPLAY_SHOWDOWN_STAGE_13: 
                mSwfSglStageFlag.SetBit(12);
                break;
            case SWORDPLAY_SHOWDOWN_STAGE_14: 
                mSwfSglStageFlag.SetBit(13);
                break;
            case SWORDPLAY_SHOWDOWN_STAGE_15: 
                mSwfSglStageFlag.SetBit(14);
                break;
            case SWORDPLAY_SHOWDOWN_STAGE_16: 
                mSwfSglStageFlag.SetBit(15);
                break;
            case SWORDPLAY_SHOWDOWN_STAGE_17: 
                mSwfSglStageFlag.SetBit(16);
                break;
            case SWORDPLAY_SHOWDOWN_STAGE_18: 
                mSwfSglStageFlag.SetBit(17);
                break;
            case SWORDPLAY_SHOWDOWN_STAGE_19: 
                mSwfSglStageFlag.SetBit(18);
                break;
            case SWORDPLAY_SHOWDOWN_STAGE_20: 
                mSwfSglStageFlag.SetBit(19);
                break;
            case WAKEBOARDING_TIMER: 
                mWkbTimerFlag.AddMinBit();
                break;
            case WAKEBOARDING_BEGINNER: 
                mWkbStageFlag.SetBit(0);
                break;
            case WAKEBOARDING_INTERMEDIATE: 
                mWkbStageFlag.SetBit(1);
                break;
            case WAKEBOARDING_EXPERT: 
                mWkbStageFlag.SetBit(2);
                break;
            case FRISBEE_DOG_FRISBEES: 
                mFldThrowFlag.AddMinBit();
                break;
            case FRISBEE_DOG_SECRET_POP: 
                mFldSecretPopFlag = true;
                break;
            case FRISBEE_GOLF_HUD: 
                mDglHUDFlag = true;
                break;
            case FRISBEE_GOLF_DRIVER: 
                mDglDiscFlag.SetBit(0);
                break;
            case FRISBEE_GOLF_MIDRANGE: 
                mDglDiscFlag.SetBit(1);
                break;
            case FRISBEE_GOLF_PUTTER: 
                mDglDiscFlag.SetBit(2);
                break;
            case FRISBEE_GOLF_COURSE_0: 
                mDglStageFlag.SetBit(0);
                break;
            case FRISBEE_GOLF_COURSE_1: 
                mDglStageFlag.SetBit(1);
                break;
            case FRISBEE_GOLF_COURSE_2: 
                mDglStageFlag.SetBit(2);
                break;
            case FRISBEE_GOLF_COURSE_3: 
                mDglStageFlag.SetBit(3);
                break;
            case FRISBEE_GOLF_COURSE_4: 
                mDglStageFlag.SetBit(4);
                break;
            case FRISBEE_GOLF_COURSE_5: 
                mDglStageFlag.SetBit(5);
                break;
            case FRISBEE_GOLF_COURSE_6: 
                mDglStageFlag.SetBit(6);
                break;
            case FRISBEE_GOLF_COURSE_7: 
                mDglStageFlag.SetBit(7);
                break;
            case FRISBEE_GOLF_COURSE_8: 
                mDglStageFlag.SetBit(8);
                break;
            case FRISBEE_GOLF_COURSE_9: 
                mDglStageFlag.SetBit(9);
                break;
            case ARCHERY_AIM_CIRCLE: 
                mArcAimFlag = true;
                break;
            case ARCHERY_ARROW: 
                mArcArrowFlag.AddMinBit();
                break;
            case ARCHERY_FRUIT_BEGINNER: 
                mArcFruitFlag.SetBit(0);
                break;
            case ARCHERY_FRUIT_INTERMEDIATE: 
                mArcFruitFlag.SetBit(1);
                break;
            case ARCHERY_FRUIT_EXPERT: 
                mArcFruitFlag.SetBit(2);
                break;
            case ARCHERY_BEGINNER: 
                mArcStageFlag.SetBit(0);
                break;
            case ARCHERY_INTERMEDIATE: 
                mArcStageFlag.SetBit(1);
                break;
            case ARCHERY_EXPERT: 
                mArcStageFlag.SetBit(2);
                break;
            case BASKETBALL_3PT_TIMER: 
                mBsk3ptTimerFlag.AddMinBit();
                break;
            case BASKETBALL_BONUS_BALLS: 
                mBsk3ptBonusFlag = true;
                break;
            case BASKETBALL_PICKUP_TIMER: 
                mBskVsTimerFlag.AddMinBit();
                break;
            case BASKETBALL_PASS: 
                mBskVsPassFlag = true;
                break;
            case BASKETBALL_3PTS: 
                mBskVs3ptFlag = true;
                break;
            case BASKETBALL_DUNK: 
                mBskVsDunkFlag = true;
                break;
            case TABLE_TENNIS_SPIN: 
                mPngSpinFlag = true;
                break;
            case TABLE_TENNIS_SMASH: 
                mPngSmashFlag = true;
                break;
            case TABLE_TENNIS_CANS: 
                mPngCansFlag = true;
                break;
            case GOLF_HUD: 
                mGlfHUDFlag = true;
                break;
            case GOLF_DRIVER: 
                mGlfClubFlag.SetBit(0);
                break;
            case GOLF_3_WOOD: 
                mGlfClubFlag.SetBit(1);
                break;
            case GOLF_3_IRON: 
                mGlfClubFlag.SetBit(2);
                break;
            case GOLF_5_IRON: 
                mGlfClubFlag.SetBit(3);
                break;
            case GOLF_7_IRON: 
                mGlfClubFlag.SetBit(4);
                break;
            case GOLF_9_IRON: 
                mGlfClubFlag.SetBit(5);
                break;
            case GOLF_WEDGE: 
                mGlfClubFlag.SetBit(6);
                break;
            case GOLF_PUTTER: 
                mGlfClubFlag.SetBit(7);
                break;
            case GOLF_TURN: 
                mGlfTurnFlag = true;
                break;
            case GOLF_BACKSPIN: 
                mGlfSpinFlag = true;
                break;
            case GOLF_COURSE_0: 
                mGlfStageFlag.SetBit(0);
                break;
            case GOLF_COURSE_1: 
                mGlfStageFlag.SetBit(1);
                break;
            case GOLF_COURSE_2: 
                mGlfStageFlag.SetBit(2);
                break;
            case GOLF_COURSE_3: 
                mGlfStageFlag.SetBit(3);
                break;
            case GOLF_COURSE_4: 
                mGlfStageFlag.SetBit(4);
                break;
            case GOLF_COURSE_5: 
                mGlfStageFlag.SetBit(5);
                break;
            case GOLF_COURSE_6: 
                mGlfStageFlag.SetBit(6);
                break;
            case GOLF_COURSE_7: 
                mGlfStageFlag.SetBit(7);
                break;
            case GOLF_COURSE_8: 
                mGlfStageFlag.SetBit(8);
                break;
            case GOLF_COURSE_9: 
                mGlfStageFlag.SetBit(9);
                break;
            case GOLF_VIEW_LOW: 
                mGlfViewLowFlag = true;
                break;
            case GOLF_VIEW_SLOPE: 
                mGlfViewSlopeFlag = true;
                break;
            case BOWLING_10_PIN_MOVE: 
                mBwlStdMoveFlag = true;
                break;
            case BOWLING_10_PIN_TURN: 
                mBwlStdTurnFlag = true;
                break;
            case BOWLING_10_PIN_SPIN: 
                mBwlStdSpinFlag = true;
                break;
            case BOWLING_100_PIN_MOVE: 
                mBwl100MoveFlag = true;
                break;
            case BOWLING_100_PIN_TURN: 
                mBwl100TurnFlag = true;
                break;
            case BOWLING_100_PIN_SPIN:
                mBwl100SpinFlag = true;
                break;
            case BOWLING_100_PIN_SECRET_STRIKE: 
                mBwl100SecretBtnFlag = true;
                break;
            case BOWLING_SPIN_CONTROL_MOVE: 
                mBwlWalMoveFlag = true;
                break;
            case BOWLING_SPIN_CONTROL_TURN: 
                mBwlWalTurnFlag = true;
                break;
            case BOWLING_SPIN_CONTROL_SPIN: 
                mBwlWalSpinFlag = true;
                break;
            case POWER_CRUISING_BOOST: 
                mJskBoostFlag = true;
                break;
            case POWER_CRUISING_RING_TIMER: 
                mJskRingTimerFlag.AddMinBit();
                break;
            case POWER_CRUISING_DOUBLE_RING:
                mJsk2xRingFlag = true;
                break;
            case POWER_CRUISING_FREE_CRUISING_TIMER: 
                mJskFreeTimerFlag.AddMinBit();
                break;
            case CANOEING_TIMER: 
                mCanTimerFlag.AddMinBit();
                break;
            case CANOEING_BEGINNER: 
                mCanStageFlag.SetBit(0);
                break;
            case CANOEING_INTERMEDIATE: 
                mCanStageFlag.SetBit(1);
                break;
            case CANOEING_EXPERT: 
                mCanStageFlag.SetBit(2);
                break;
            case CYCLING_HEART: 
                mBicHeartFlag.AddMinBit();
                break;
            case CYCLING_STAGE_0: 
                mBicStageFlag.SetBit(0);
                break;
            case CYCLING_STAGE_1: 
                mBicStageFlag.SetBit(1);
                break;
            case CYCLING_STAGE_2: 
                mBicStageFlag.SetBit(2);
                break;
            case CYCLING_STAGE_3: 
                mBicStageFlag.SetBit(3);
                break;
            case CYCLING_STAGE_4: 
                mBicStageFlag.SetBit(4);
                break;
            case CYCLING_STAGE_5: 
                mBicStageFlag.SetBit(5);
                break;
            case CYCLING_STAGE_6: 
                mBicStageFlag.SetBit(6);
                break;
            case CYCLING_STAGE_7: 
                mBicStageFlag.SetBit(7);
                break;
            case SKYDIVING_MII: 
                mOmkMiiFlag.AddMinBit();
                break;
            case ISLAND_FLYOVER_TIMER: 
                mPlnTimerFlag.AddMinBit();
                break;
            case ISLAND_FLYOVER_DAY: 
                mPlnStageFlag.SetBit(0);
                break;
            case ISLAND_FLYOVER_EVENING:
                mPlnStageFlag.SetBit(1); 
                break;
            case ISLAND_FLYOVER_NIGHT: 
                mPlnStageFlag.SetBit(2);
                break;
            case ISLAND_FLYOVER_DOUBLE_BLASTERS: 
                mPlnDoubleBlastersFlag = true;
                break;
            case ISLAND_FLYOVER_NIGHT_LIGHTS: 
                mPlnNightLightsFlag = true;
                break;
            case ISLAND_FLYOVER_UNLOCK_BALLOONS: 
                mPlnBalloonsFlag = true;
                break;
            case ISLAND_FLYOVER_UNLOCK_TWO_SEATER: 
                mPlnTwoSeaterPlaneFlag = true;
                break;

            default:
                kiwi::cout << "Error giving item with id: " << id << kiwi::endl;
        }
    }
};

} // namespace AP

#endif
