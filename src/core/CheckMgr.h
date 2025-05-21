#ifndef APCLIENT_CORE_CHECK_MGR_H
#define APCLIENT_CORE_CHECK_MGR_H
#include <types.h>

#include "core/const.h"

#include <Sports2/Sp2Cmn.h>

#include <libkiwi.h>

namespace AP {

class CheckMgr : public kiwi::DynamicSingleton<CheckMgr>, public kiwi::IBinary {
    friend class kiwi::DynamicSingleton<CheckMgr>;

public:
    enum CheckID {
    // Stamps
    SWORDPLAY_SHOWDOWN_STAMP_1 = 0x0000, // Sport ID 0
    SWORDPLAY_SHOWDOWN_STAMP_2 = 0x0001,
    SWORDPLAY_SHOWDOWN_STAMP_3 = 0x0002,
    SWORDPLAY_SHOWDOWN_STAMP_4 = 0x0003,
    SWORDPLAY_SHOWDOWN_STAMP_5 = 0x0004,
    SWORDPLAY_DUEL_STAMP_1 = 0x0005, // Sport ID 1
    SWORDPLAY_DUEL_STAMP_2 = 0x0006,
    SWORDPLAY_DUEL_STAMP_3 = 0x0007,
    SWORDPLAY_DUEL_STAMP_4 = 0x0008,
    SWORDPLAY_DUEL_STAMP_5 = 0x0009,
    SWORDPLAY_SPEED_SLICE_STAMP_1 = 0x000A, // Sport ID 2
    SWORDPLAY_SPEED_SLICE_STAMP_2 = 0x000B,
    SWORDPLAY_SPEED_SLICE_STAMP_3 = 0x000C,
    SWORDPLAY_SPEED_SLICE_STAMP_4 = 0x000D,
    SWORDPLAY_SPEED_SLICE_STAMP_5 = 0x000E,
    POWER_CRUISING_STAMP_1 = 0x000F, // Sport ID 3
    POWER_CRUISING_STAMP_2 = 0x0010,
    POWER_CRUISING_STAMP_3 = 0x0011,
    POWER_CRUISING_STAMP_4 = 0x0012,
    POWER_CRUISING_STAMP_5 = 0x0013,
    ARCHERY_STAMP_1 = 0x0019, // Sport ID 5
    ARCHERY_STAMP_2 = 0x001A,
    ARCHERY_STAMP_3 = 0x001B,
    ARCHERY_STAMP_4 = 0x001C,
    ARCHERY_STAMP_5 = 0x001D,
    FRISBEE_DOG_STAMP_1 = 0x001E, // Sport ID 6
    FRISBEE_DOG_STAMP_2 = 0x001F,
    FRISBEE_DOG_STAMP_3 = 0x0020,
    FRISBEE_DOG_STAMP_4 = 0x0021,
    FRISBEE_DOG_STAMP_5 = 0x0022,
    BASKETBALL_3PT_CONTEST_STAMP_1 = 0x0023, // Sport ID 7
    BASKETBALL_3PT_CONTEST_STAMP_2 = 0x0024,
    BASKETBALL_3PT_CONTEST_STAMP_3 = 0x0025,
    BASKETBALL_3PT_CONTEST_STAMP_4 = 0x0026,
    BASKETBALL_3PT_CONTEST_STAMP_5 = 0x0027,
    BASKETBALL_PICKUP_GAME_1 = 0x0028, // Sport ID 8
    BASKETBALL_PICKUP_GAME_2 = 0x0029,
    BASKETBALL_PICKUP_GAME_3 = 0x002A,
    BASKETBALL_PICKUP_GAME_4 = 0x002B,
    BASKETBALL_PICKUP_GAME_5 = 0x002C,
    BOWLING_STANDARD_GAME_STAMP_1 = 0x002D, // Sport ID 9
    BOWLING_STANDARD_GAME_STAMP_2 = 0x002E,
    BOWLING_STANDARD_GAME_STAMP_3 = 0x002F,
    BOWLING_STANDARD_GAME_STAMP_4 = 0x0030,
    BOWLING_STANDARD_GAME_STAMP_5 = 0x0031,
    BOWLING_100_PIN_STAMP_1 = 0x0032, // Sport ID 10
    BOWLING_100_PIN_STAMP_2 = 0x0033,
    BOWLING_100_PIN_STAMP_3 = 0x0034,
    BOWLING_100_PIN_STAMP_4 = 0x0035,
    BOWLING_100_PIN_STAMP_5 = 0x0036,
    BOWLING_SPIN_CONTROL_STAMP_1 = 0x0037, // Sport ID 11
    BOWLING_SPIN_CONTROL_STAMP_2 = 0x0038,
    BOWLING_SPIN_CONTROL_STAMP_3 = 0x0039,
    BOWLING_SPIN_CONTROL_STAMP_4 = 0x003A,
    BOWLING_SPIN_CONTROL_STAMP_5 = 0x003B,
    CANOEING_STAMP_1 = 0x0041, // Sport ID 13
    CANOEING_STAMP_2 = 0x0042,
    CANOEING_STAMP_3 = 0x0043,
    CANOEING_STAMP_4 = 0x0044,
    CANOEING_STAMP_5 = 0x0045,
    TABLE_TENNIS_RETURN_CHALLENGE_STAMP_1 = 0x0046, // Sport ID 14
    TABLE_TENNIS_RETURN_CHALLENGE_STAMP_2 = 0x0047,
    TABLE_TENNIS_RETURN_CHALLENGE_STAMP_3 = 0x0048,
    TABLE_TENNIS_RETURN_CHALLENGE_STAMP_4 = 0x0049,
    TABLE_TENNIS_RETURN_CHALLENGE_STAMP_5 = 0x004A,
    TABLE_TENNIS_MATCH_STAMP_1 = 0x004B, // Sport ID 15
    TABLE_TENNIS_MATCH_STAMP_2 = 0x004C,
    TABLE_TENNIS_MATCH_STAMP_3 = 0x004D,
    TABLE_TENNIS_MATCH_STAMP_4 = 0x004E,
    TABLE_TENNIS_MATCH_STAMP_5 = 0x004F,
    WAKEBOARDING_STAMP_1 = 0x0050, // Sport ID 16
    WAKEBOARDING_STAMP_2 = 0x0051,
    WAKEBOARDING_STAMP_3 = 0x0052,
    WAKEBOARDING_STAMP_4 = 0x0053,
    WAKEBOARDING_STAMP_5 = 0x0054,
    ISLAND_FLYOVER_STAMP_1 = 0x0055, // Sport ID 17
    ISLAND_FLYOVER_STAMP_2 = 0x0056,
    ISLAND_FLYOVER_STAMP_3 = 0x0057,
    ISLAND_FLYOVER_STAMP_4 = 0x0058,
    ISLAND_FLYOVER_STAMP_5 = 0x0059,
    GOLF_STAMP_1 = 0x005F, // Sport ID 19
    GOLF_STAMP_2 = 0x0060,
    GOLF_STAMP_3 = 0x0061,
    GOLF_STAMP_4 = 0x0062,
    GOLF_STAMP_5 = 0x0063,
    FRISBEE_GOLF_STAMP_1 = 0x0064, // Sport ID 20
    FRISBEE_GOLF_STAMP_2 = 0x0065,
    FRISBEE_GOLF_STAMP_3 = 0x0066,
    FRISBEE_GOLF_STAMP_4 = 0x0067,
    FRISBEE_GOLF_STAMP_5 = 0x0068,
    CYCLING_STAMP_1 = 0x006E, // Sport ID 22
    CYCLING_STAMP_2 = 0x006F,
    CYCLING_STAMP_3 = 0x0070,
    CYCLING_STAMP_4 = 0x0071,
    CYCLING_STAMP_5 = 0x0072,
    SKYDIVING_STAMP_1 = 0x0073, // Sport ID 23
    SKYDIVING_STAMP_2 = 0x0074,
    SKYDIVING_STAMP_3 = 0x0075,
    SKYDIVING_STAMP_4 = 0x0076,
    SKYDIVING_STAMP_5 = 0x0077,

    COUNT
}; // CheckID;

public:
    /**
     * @brief Sets debug state
     */
    void Debug();

    /**
     * @brief Clears check state
     */
    void Clear();

    /**
     * @brief Gets the check state
     *
     * @param id Check ID
     * @return Check state
     */
    bool GetCheckState(CheckID id) const;

    /**
     * @brief Sets the check state
     *
     * @param id Check ID
     * @param state Check state
     */
    void SetCheckState(CheckID id, bool state);

    /**
     * @brief Gets the item ID for a check
     *
     * @param id Check ID
     * @return Item ID
     */
    u16 GetItemID(CheckID id) const;

    /**
     * @brief Sets the item ID for a check
     *
     * @param id Check ID
     * @param itemID Item ID
     */
    void SetItemID(CheckID id, u16 itemID);

    /**
     * 
     * @brief gives proper item from check ID
     * 
     * @param id Check ID
     */
    void GiveItemFromCheck(CheckID id);

    /**
     * @brief Gets name of check
     * 
     */
    const char* GetCheckName(CheckID id) const;


private:
    //! Binary file magic
    static const u32 SIGNATURE = 'CHCK';
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

    };
#pragma pack(pop)

private:
    /**
     * @brief Constructor
     */
    CheckMgr();

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
    kiwi::TMap<CheckID, bool> mCheckState; //!< Check state
    kiwi::TMap<CheckID, u16> mCheckToItemID; //!< Check to item mapping




};

} // namespace AP

#endif // APCLIENT_CORE_CHECK_MGR_H