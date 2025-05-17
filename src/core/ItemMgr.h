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
     * @name Frisbee Golf
     */
    /**@{*/
    //! HUD
    bool IsDglHUDUnlocked() const {
        return mDglHUDFlag;
    }
    /**@}*/

    /**
     * @name Archery
     */
    /**@{*/
    //! Number of arrow items
    static const u32 ARC_ARROW_COUNT = 3;
    //! Number of stage unlock items
    static const u32 ARC_STAGE_COUNT = 3;
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
    bool IsBskGoldenBallAbilityUnlocked() const {
        return mBsk3ptGoldenBallFlag;
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
    bool IsBskVsPassUnlocked() const {
        return mBskVsPassFlag;
    }
    /**@}*/

    /**
     * @name Golf
     */
    /**@{*/
    //! HUD
    bool IsGlfHUDUnlocked() const {
        return mGlfHUDFlag;
    }
    /**@}*/

    /**
     * @name Bowling (Standard Game)
     */
    /**@{*/
    //! Moving ability
    bool IsBwlStdMoveUnlocked() const {
        return mBwlStdMoveFlag;
    }
    //! Turning ability
    bool IsBwlStdTurnUnlocked() const {
        return mBwlStdTurnFlag;
    }
    /**@}*/

    /**
     * @name Bowling (Standard Game)
     */
    /**@{*/
    //! Moving ability
    bool IsBwl100MoveUnlocked() const {
        return mBwl100MoveFlag;
    }
    //! Turning ability
    bool IsBwl100TurnUnlocked() const {
        return mBwl100TurnFlag;
    }
    /**@}*/

    /**
     * @name Bowling (Standard Game)
     */
    /**@{*/
    //! Moving ability
    bool IsBwlWalMoveUnlocked() const {
        return mBwlWalMoveFlag;
    }
    //! Turning ability
    bool IsBwlWalTurnUnlocked() const {
        return mBwlWalTurnFlag;
    }
    /**@}*/

    /**
     * @name Power Cruising
     */
    /**@{*/
    //! Boosting ability
    bool IsJskBoostUnlocked() const {
        return mJskBoostFlag;
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
    //! Blocking ability
    bool mSwfVsBlockFlag;
    /**@}*/

    /**
     * @name Swordplay (Speed Slice)
     */
    /**@{*/
    //! Pausing ability
    bool mSwfPrcPauseFlag;
    /**@}*/

    /**
     * @name Swordplay (Showdown)
     */
    /**@{*/
    //! Blocking ability
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
    //! Extra timers (bitfield)
    kiwi::TBitFlag<u32, WKB_TIMER_COUNT> mWkbTimerFlag;
    //! Extra stages (bitfield)
    kiwi::TBitFlag<u32, WKB_STAGE_COUNT> mWkbStageFlag;
    /**@}*/

    /**
     * @name Frisbee Golf
     */
    /**@{*/
    //! HUD
    bool mDglHUDFlag;
    /**@}*/

    /**
     * @name Archery
     */
    /**@{*/
    //! Total arrows (bitfield)
    kiwi::TBitFlag<u32, ARC_ARROW_COUNT> mArcTotalArrowsFlag;
    //! Extra stages (bitfield)
    kiwi::TBitFlag<u32, ARC_STAGE_COUNT> mArcStageFlag;
    /**@}*/

    /**
     * @name Basketball (3-Point Contest)
     */
    /**@{*/
    //! Extra timers (bitfield)
    kiwi::TBitFlag<u32, BSK_3PT_TIMER_COUNT> mBsk3ptTimerFlag;
    //! Golden ball ability
    bool mBsk3ptGoldenBallFlag;
    /**@}*/

    /**
     * @name Basketball (Pickup Game)
     */
    /**@{*/
    //! Extra timers (bitfield)
    kiwi::TBitFlag<u32, BSK_VS_TIMER_COUNT> mBskVsTimerFlag;
    //! Passing ability (bitfield)
    bool mBskVsPassFlag;
    /**@}*/

    /**
     * @name Golf
     */
    /**@{*/
    //! HUD
    bool mGlfHUDFlag;
    /**@}*/

    /**
     * @name Bowling (Standard Game)
     */
    /**@{*/
    //! Moving ability
    bool mBwlStdMoveFlag;
    //! Turning ability
    bool mBwlStdTurnFlag;
    /**@}*/

    /**
     * @name Bowling (100-Pin Game)
     */
    /**@{*/
    //! Moving ability
    bool mBwl100MoveFlag;
    //! Turning ability
    bool mBwl100TurnFlag;
    /**@}*/

    /**
     * @name Bowling (Spin Control)
     */
    /**@{*/
    //! Moving ability
    bool mBwlWalMoveFlag;
    //! Turning ability
    bool mBwlWalTurnFlag;
    /**@}*/

    /**
     * @name Power Cruising
     */
    /**@{*/
    //! Boosting Ability
    bool mJskBoostFlag;
    /**@}*/

    /**
     * @name Canoeing
     */
    /**@{*/
    //! Extra timers (bitfield)
    kiwi::TBitFlag<u32, CAN_TIMER_COUNT> mCanTimerFlag;
    //! Extra stages (bitfield)
    kiwi::TBitFlag<u32, CAN_STAGE_COUNT> mCanStageFlag;
    /**@}*/

    /**
     * @name Cycling
     */
    /**@{*/
    //! Extra hearts (bitfield)
    kiwi::TBitFlag<u32, BIC_HEART_COUNT> mBicHeartFlag;
    //! Extra stages (bitfield)
    kiwi::TBitFlag<u32, BIC_STAGE_COUNT> mBicStageFlag;
    /**@}*/

    /**
     * @name Island Flyover
     */
    /**@{*/
    //! Extra timers (bitfield)
    kiwi::TBitFlag<u32, PLN_TIMER_COUNT> mPlnTimerFlag;
    //! Extra stages (bitfield)
    kiwi::TBitFlag<u32, PLN_STAGE_COUNT> mPlnStageFlag;
    /**@}*/
};

} // namespace AP

#endif
