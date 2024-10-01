#ifndef APCLIENT_CORE_ITEM_MGR_H
#define APCLIENT_CORE_ITEM_MGR_H
#include <core/const.h>
#include <libkiwi.h>
#include <types.h>

namespace AP {

/**
 * @brief Archipelago item manager
 */
class ItemMgr : public kiwi::DynamicSingleton<ItemMgr>, public kiwi::IBinary {
    friend class kiwi::DynamicSingleton<ItemMgr>;

public:
    /**
     * @name Swordplay (Duel)
     */
    /**@{*/
    bool SwfVsCanBlock() const {
        return mSwfVsCanBlock;
    }
    /**@}*/

    /**
     * @name Swordplay (Speed Slice)
     */
    /**@{*/
    bool SwfPrcCanPause() const {
        return mSwfPrcCanPause;
    }
    /**@}*/

    /**
     * @name Swordplay (Showdown)
     */
    /**@{*/
    bool SwfSglCanBlock() const {
        return mSwfSglCanBlock;
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

private:
    /**
     * @name Swordplay (Duel)
     */
    /**@{*/
    bool mSwfVsCanBlock; //!< Blocking ability
    /**@}*/

    /**
     * @name Swordplay (Speed Slice)
     */
    /**@{*/
    bool mSwfPrcCanPause; //!< Pausing ability
    /**@}*/

    /**
     * @name Swordplay (Showdown)
     */
    /**@{*/
    bool mSwfSglCanBlock; //!< Blocking ability
    int mSwfSglHearts;    //!< Number of hearts
    /**@}*/

private:
    /**
     * @brief Item manager binary structure
     */
#pragma pack(push, 1)
    struct Bin : kiwi::IBinary::Block {
        /* 0x00:0  */ u32 swfVsCanBlock : 1;  //!< Blocking ability
        /* 0x00:1  */ u32 swfPrcCanPause : 1; //!< Pausing ability
        /* 0x00:2  */ u32 swfSglCanBlock : 1; //!< Blocking ability
        /* 0x00:3  */ u32 swfSglHearts : 2;   //!< Extra hearts
        /* 0x00:5  */ u32 swfSglStages : 19;  //!< Unlocked stages

        /* 0x04:0  */ u8 wkbTimer : 4;  //!< Extra time
        /* 0x04:4  */ u8 wkbStages : 3; //!< Unlocked difficulties

        /* 0x05:0  */ u16 fldThrows : 9;        //!< Extra throws
        /* 0x05:4  */ u16 fldCanPopBalloon : 1; //!< A+2 balloon pop ability

        /* 0x07:0  */ u16 dglDisc : 3;    //!< Progressive disc
        /* 0x07:3  */ u16 dglStages : 10; //!< Unlocked courses

        /* 0x09:0  */ u16 arcArrows : 2; //!< Extra arrows
        /* 0x09:2  */ u16 arcFruits : 3; //!< Hidden fruits
        /* 0x09:5  */ u16 arcStages : 3; //!< Unlocked stages

        // . . .
    };
#pragma pack(pop)
};

} // namespace AP

#endif