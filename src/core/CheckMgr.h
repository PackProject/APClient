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
    Swordplay_Duel_Stamp_1 = 0x0001,
    Swordplay_Duel_Stamp_2 = 0x0002,
    Swordplay_Duel_Stamp_3 = 0x0003,
    Swordplay_Duel_Stamp_4 = 0x0004,
    Swordplay_Duel_Stamp_5 = 0x0005,
    Swordplay_SpeedSlice_Stamp_1 = 0x0006,
    Swordplay_SpeedSlice_Stamp_2 = 0x0007,
    Swordplay_SpeedSlice_Stamp_3 = 0x0008,
    Swordplay_SpeedSlice_Stamp_4 = 0x0009,
    Swordplay_SpeedSlice_Stamp_5 = 0x000A,
    Swordplay_Showdown_Stamp_1 = 0x000B,
    Swordplay_Showdown_Stamp_2 = 0x000C,
    Swordplay_Showdown_Stamp_3 = 0x000D,
    Swordplay_Showdown_Stamp_4 = 0x000E,
    Swordplay_Showdown_Stamp_5 = 0x000F,
    Wakeboarding_Stamp_1 = 0x0010,
    Wakeboarding_Stamp_2 = 0x0011,
    Wakeboarding_Stamp_3 = 0x0012,
    Wakeboarding_Stamp_4 = 0x0013,
    Wakeboarding_Stamp_5 = 0x0014,
    FrisbeeDog_Stamp_1 = 0x0015,
    FrisbeeDog_Stamp_2 = 0x0016,
    FrisbeeDog_Stamp_3 = 0x0017,
    FrisbeeDog_Stamp_4 = 0x0018,
    FrisbeeDog_Stamp_5 = 0x0019,
    FrisbeeGolf_Stamp_1 = 0x001A,
    FrisbeeGolf_Stamp_2 = 0x001B,
    FrisbeeGolf_Stamp_3 = 0x001C,
    FrisbeeGolf_Stamp_4 = 0x001D,
    FrisbeeGolf_Stamp_5 = 0x001E,
    Archery_Stamp_1 = 0x001F,
    Archery_Stamp_2 = 0x0020,
    Archery_Stamp_3 = 0x0021,
    Archery_Stamp_4 = 0x0022,
    Archery_Stamp_5 = 0x0023,
    Basketball_3PointContest_Stamp_1 = 0x0024,
    Basketball_3PointContest_Stamp_2 = 0x0025,
    Basketball_3PointContest_Stamp_3 = 0x0026,
    Basketball_3PointContest_Stamp_4 = 0x0027,
    Basketball_3PointContest_Stamp_5 = 0x0028,
    Basketball_PickupGame_Stamp_1 = 0x0029,
    Basketball_PickupGame_Stamp_2 = 0x002A,
    Basketball_PickupGame_Stamp_3 = 0x002B,
    Basketball_PickupGame_Stamp_4 = 0x002C,
    Basketball_PickupGame_Stamp_5 = 0x002D,
    TableTennis_Match_Stamp_1 = 0x002E,
    TableTennis_Match_Stamp_2 = 0x002F,
    TableTennis_Match_Stamp_3 = 0x0030,
    TableTennis_Match_Stamp_4 = 0x0031,
    TableTennis_Match_Stamp_5 = 0x0032,
    TableTennis_ReturnChallenge_Stamp_1 = 0x0033,
    TableTennis_ReturnChallenge_Stamp_2 = 0x0034,
    TableTennis_ReturnChallenge_Stamp_3 = 0x0035,
    TableTennis_ReturnChallenge_Stamp_4 = 0x0036,
    TableTennis_ReturnChallenge_Stamp_5 = 0x0037,
    Golf_Stamp_1 = 0x0038,
    Golf_Stamp_2 = 0x0039,
    Golf_Stamp_3 = 0x003A,
    Golf_Stamp_4 = 0x003B,
    Golf_Stamp_5 = 0x003C,
    Bowling_StandardGame_Stamp_1 = 0x003D,
    Bowling_StandardGame_Stamp_2 = 0x003E,
    Bowling_StandardGame_Stamp_3 = 0x003F,
    Bowling_StandardGame_Stamp_4 = 0x0040,
    Bowling_StandardGame_Stamp_5 = 0x0041,
    Bowling_100PinGame_Stamp_1 = 0x0042,
    Bowling_100PinGame_Stamp_2 = 0x0043,
    Bowling_100PinGame_Stamp_3 = 0x0044,
    Bowling_100PinGame_Stamp_4 = 0x0045,
    Bowling_100PinGame_Stamp_5 = 0x0046,
    Bowling_SpinControl_Stamp_1 = 0x0047,
    Bowling_SpinControl_Stamp_2 = 0x0048,
    Bowling_SpinControl_Stamp_3 = 0x0049,
    Bowling_SpinControl_Stamp_4 = 0x004A,
    Bowling_SpinControl_Stamp_5 = 0x004B,
    PowerCruising_Stamp_1 = 0x004C,
    PowerCruising_Stamp_2 = 0x004D,
    PowerCruising_Stamp_3 = 0x004E,
    PowerCruising_Stamp_4 = 0x004F,
    PowerCruising_Stamp_5 = 0x0050,
    Canoeing_Stamp_1 = 0x0051,
    Canoeing_Stamp_2 = 0x0052,
    Canoeing_Stamp_3 = 0x0053,
    Canoeing_Stamp_4 = 0x0054,
    Canoeing_Stamp_5 = 0x0055,
    Cycling_Stamp_1 = 0x0056,
    Cycling_Stamp_2 = 0x0057,
    Cycling_Stamp_3 = 0x0058,
    Cycling_Stamp_4 = 0x0059,
    Cycling_Stamp_5 = 0x005A,
    Skydiving_Stamp_1 = 0x005B,
    Skydiving_Stamp_2 = 0x005C,
    Skydiving_Stamp_3 = 0x005D,
    Skydiving_Stamp_4 = 0x005E,
    Skydiving_Stamp_5 = 0x005F,
    IslandFlyover_Stamp_1 = 0x0060,
    IslandFlyover_Stamp_2 = 0x0061,
    IslandFlyover_Stamp_3 = 0x0062,
    IslandFlyover_Stamp_4 = 0x0063,
    IslandFlyover_Stamp_5 = 0x0064,
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