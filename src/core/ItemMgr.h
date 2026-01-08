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
class ItemMgr : public kiwi::DynamicSingleton<ItemMgr> {
    friend class kiwi::DynamicSingleton<ItemMgr>;

public:
    /**
     * @brief Gets the readable name of the specified item ID
     *
     * @param id Item ID
     */
    static kiwi::String GetItemName(ItemID id);

    /**
     * @brief Resets the item state to the default settings
     */
    void Clear();

    /**
     * @brief Randomizes the item state for debugging purposes
     */
    void Debug();

    /**
     * @brief Gets the current state of the specified item
     *
     * @param id Item ID
     * @return Whether the item has been obtained
     */
    bool GetItemState(ItemID id) const;

    /**
     * @brief Sets the current state of the specified item
     *
     * @param id Item ID
     * @param state Whether the item has been obtained
     */
    void SetItemState(ItemID id, bool state);

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

    //! Number of stage unlock items
    static const u32 JSK_STAGE_COUNT = 6;

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
    bool IsJskStageUnlock(u32 id) const {
        return mJskStageFlag.GetBit(id);
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
    static const u32 OMK_MII_COUNT =
        4; // random value, will need to be changed later

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
    bool IsPlnDoubleBlasters() const {
        return mPlnDoubleBlastersFlag;
    }
    bool IsPlnNightLights() const {
        return mPlnNightLightsFlag;
    }
    bool IsPlnBalloons() const {
        return mPlnBalloonsFlag;
    }
    bool IsPlnTwoSeater() const {
        return mPlnTwoSeaterPlaneFlag;
    }
    bool IsPlnBoost() const {
        return mPlnBoostFlag;
    }
    bool IsPlnBrake() const {
        return mPlnBrakeFlag;
    }
    /**@}*/

private:
    /**
     * @brief Constructor
     */
    ItemMgr();

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
    //! Stage items
    kiwi::TBitFlag<u32, JSK_STAGE_COUNT> mJskStageFlag;
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
    //! Braking
    bool mPlnBrakeFlag;
    //! Boosting
    bool mPlnBoostFlag;
    /**@}*/
};

} // namespace AP

#endif
