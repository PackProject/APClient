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
    //! Wakeboarding timer increment (in seconds)
    static const u32 WKB_TIMER_ITEM = 24;

public:
    /**
     * @brief Sets debug state
     */
    void Debug();

    /**
     * @name Main Menu
     */
    /**@{*/
    bool IsSportUnlock(Sp2::Cmn::ESport sport) {
        ASSERT(sport < Sp2::Cmn::ESport_Max);
        return mSportFlag & (1 << sport);
    }
    bool IsCategoryUnlock(Sp2::Cmn::ESaveSeq seq) const {
        ASSERT(seq < Sp2::Cmn::ESaveSeq_Max);
        return mCategoryFlag & (1 << seq);
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
    bool IsSwfSglBlock() const {
        return mSwfSglBlockFlag;
    }
    u32 GetSwfSglHeartNum() const {
        return kiwi::BitUtil::Count(mSwfSglHeartFlag);
    }
    bool IsSwfSglStageUnlock(u32 id) const {
        return mSwfSglStageFlag & (1 << id);
    }
    /**@}*/

    /**
     * @name Wakeboarding
     */
    /**@{*/
    u32 GetWkbTimerNum() const {
        return kiwi::BitUtil::Count(mWkbTimerFlag);
    }
    bool IsWkbStageUnlock(u32 id) const {
        return mWkbStageFlag & (1 << id);
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
    u32 mSportFlag;    //!< Unlocked sports
    u32 mCategoryFlag; //!< Unlocked categories
    /**@}*/

    /**
     * @name Swordplay (Duel)
     */
    /**@{*/
    bool mSwfVsBlockFlag; //!< Blocking ability
    /**@}*/

    /**
     * @name Swordplay (Speed Slice)
     */
    /**@{*/
    bool mSwfPrcPauseFlag; //!< Pausing ability
    /**@}*/

    /**
     * @name Swordplay (Showdown)
     */
    /**@{*/
    bool mSwfSglBlockFlag; //!< Blocking ability
    u32 mSwfSglHeartFlag;  //!< Extra hearts (bitfield)
    u32 mSwfSglStageFlag;  //!< Extra stages (bitfield)
    /**@}*/

    /**
     * @name Wakeboarding
     */
    /**@{*/
    u32 mWkbTimerFlag; //!< Extra timers (bitfield)
    u32 mWkbStageFlag; //!< Extra stages (bitfield)
    /**@}*/
};

} // namespace AP

#endif