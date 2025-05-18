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
    static const u32 BIC_STAGE_COUNT = 6;

    u32 GetBicHeartNum() const {
        return mBicHeartFlag.Count();
    }
    bool IsBicStageUnlock(u32 id) const {
        return mBicStageFlag.GetBit(id);
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
     * @name Island Flyover
     */
    /**@{*/
    //! Timer items
    kiwi::TBitFlag<u32, PLN_TIMER_COUNT> mPlnTimerFlag;
    //! Stage items
    kiwi::TBitFlag<u32, PLN_STAGE_COUNT> mPlnStageFlag;
    /**@}*/
};

} // namespace AP

#endif
