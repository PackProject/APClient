#include "core/CheckMgr.h"

#include <libkiwi.h>
#include "core/ItemMgr.h"

K_DYNAMIC_SINGLETON_IMPL(AP::CheckMgr);

namespace AP {

/**
 * @brief Binary file path
 */
const char* CheckMgr::PATH = "item.bin";

/**
 * @brief Constructor
 */
CheckMgr::CheckMgr() {
    Clear();
}

/**
 * @brief Deserializes binary contents (internal implementation)
 *
 * @param rHeader Binary file header
 */
void CheckMgr::DeserializeImpl(const Header& rHeader) {
    ;
}

/**
 * @brief Serializes binary contents (internal implementation)
 *
 * @param rHeader Binary file header
 */
void CheckMgr::SerializeImpl(Header& rHeader) const {
    ;
}

const char* CheckMgr::GetCheckName(CheckMgr::CheckID id) const {
    switch (id) {
        case SWORDPLAY_DUEL_STAMP_1: return "Swordplay Duel (Stamp) - Cliff-hanger";
        case SWORDPLAY_DUEL_STAMP_2: return "Swordplay Duel (Stamp) - Straight to the Point";
        case SWORDPLAY_DUEL_STAMP_3: return "Swordplay Duel (Stamp) - Met Your Match";
        case SWORDPLAY_DUEL_STAMP_4: return "Swordplay Duel (Stamp) - One-Hit Wonder";
        case SWORDPLAY_DUEL_STAMP_5: return "Swordplay Duel (Stamp) - Last Mii Standing";
        case SWORDPLAY_SPEED_SLICE_STAMP_1: return "Swordplay Speed Slice (Stamp) - Slice and Dice";
        case SWORDPLAY_SPEED_SLICE_STAMP_2: return "Swordplay Speed Slice (Stamp) - Slicing Machine";
        case SWORDPLAY_SPEED_SLICE_STAMP_3: return "Swordplay Speed Slice (Stamp) - Psychic Slice";
        case SWORDPLAY_SPEED_SLICE_STAMP_4: return "Swordplay Speed Slice (Stamp) - Double Time";
        case SWORDPLAY_SPEED_SLICE_STAMP_5: return "Swordplay Speed Slice (Stamp) - A Cut Above";
        case SWORDPLAY_SHOWDOWN_STAMP_1: return "Swordplay Showdown (Stamp) - Not a Scratch";
        case SWORDPLAY_SHOWDOWN_STAMP_2: return "Swordplay Showdown (Stamp) - Sword Fighter";
        case SWORDPLAY_SHOWDOWN_STAMP_3: return "Swordplay Showdown (Stamp) - Perfect 10";
        case SWORDPLAY_SHOWDOWN_STAMP_4: return "Swordplay Showdown (Stamp) - Swordmaster";
        case SWORDPLAY_SHOWDOWN_STAMP_5: return "Swordplay Showdown (Stamp) - Untouchable";
        case WAKEBOARDING_STAMP_1: return "Wakeboarding (Stamp) - Huge Air";
        case WAKEBOARDING_STAMP_2: return "Wakeboarding (Stamp) - Bag of Tricks";
        case WAKEBOARDING_STAMP_3: return "Wakeboarding (Stamp) - Smooth Landing";
        case WAKEBOARDING_STAMP_4: return "Wakeboarding (Stamp) - Master Carver";
        case WAKEBOARDING_STAMP_5: return "Wakeboarding (Stamp) - The Long Way Home";
        case FRISBEE_DOG_STAMP_1: return "Frisbee Dog (Stamp) - Good Dog";
        case FRISBEE_DOG_STAMP_2: return "Frisbee Dog (Stamp) - Balloon Animal";
        case FRISBEE_DOG_STAMP_3: return "Frisbee Dog (Stamp) - A for Effort";
        case FRISBEE_DOG_STAMP_4: return "Frisbee Dog (Stamp) - Perfect Target";
        case FRISBEE_DOG_STAMP_5: return "Frisbee Dog (Stamp) - Golden Arm";
        case FRISBEE_GOLF_STAMP_1: return "Frisbee Golf (Stamp) - Under Par";
        case FRISBEE_GOLF_STAMP_2: return "Frisbee Golf (Stamp) - Lucky Skip";
        case FRISBEE_GOLF_STAMP_3: return "Frisbee Golf (Stamp) - On a Roll";
        case FRISBEE_GOLF_STAMP_4: return "Frisbee Golf (Stamp) - Hole in One";
        case FRISBEE_GOLF_STAMP_5: return "Frisbee Golf (Stamp) - Straight and Narrow";
        case ARCHERY_STAMP_1: return "Archery (Stamp) - Bull Stampede";
        case ARCHERY_STAMP_2: return "Archery (Stamp) - Sure Shot";
        case ARCHERY_STAMP_3: return "Archery (Stamp) - Century Shot";
        case ARCHERY_STAMP_4: return "Archery (Stamp) - A Secret to Everybody";
        case ARCHERY_STAMP_5: return "Archery (Stamp) - Sharpshooter";
        case BASKETBALL_3PT_CONTEST_STAMP_1: return "3-Point Contest (Stamp) - Hot Streak";
        case BASKETBALL_3PT_CONTEST_STAMP_2: return "3-Point Contest (Stamp) - Bonus Plumber";
        case BASKETBALL_3PT_CONTEST_STAMP_3: return "3-Point Contest (Stamp) - Quick Draw";
        case BASKETBALL_3PT_CONTEST_STAMP_4: return "3-Point Contest (Stamp) - Hot Hand";
        case BASKETBALL_3PT_CONTEST_STAMP_5: return "3-Point Contest (Stamp) - Pure Shooter";
        case BASKETBALL_PICKUP_GAME_1: return "Pickup Game (Stamp) - Triple Dip";
        case BASKETBALL_PICKUP_GAME_2: return "Pickup Game (Stamp) - Rim Rattler";
        case BASKETBALL_PICKUP_GAME_3: return "Pickup Game (Stamp) - Lights Out";
        case BASKETBALL_PICKUP_GAME_4: return "Pickup Game (Stamp) - Buzzer Beater";
        case BASKETBALL_PICKUP_GAME_5: return "Pickup Game (Stamp) - Hoop Hero";
        case TABLE_TENNIS_MATCH_STAMP_1: return "Table Tennis Match (Stamp) - In Your Face";
        case TABLE_TENNIS_MATCH_STAMP_2: return "Table Tennis Match (Stamp) - Back from the Brink";
        case TABLE_TENNIS_MATCH_STAMP_3: return "Table Tennis Match (Stamp) - Epic Rally";
        case TABLE_TENNIS_MATCH_STAMP_4: return "Table Tennis Match (Stamp) - Perfectly Matched";
        case TABLE_TENNIS_MATCH_STAMP_5: return "Table Tennis Match (Stamp) - Table Titan";
        case TABLE_TENNIS_RETURN_CHALLENGE_STAMP_1: return "Return Challenge (Stamp) - 50-pointer";
        case TABLE_TENNIS_RETURN_CHALLENGE_STAMP_2: return "Return Challenge (Stamp) - 100-pointer";
        case TABLE_TENNIS_RETURN_CHALLENGE_STAMP_3: return "Return Challenge (Stamp) - 200-pointer";
        case TABLE_TENNIS_RETURN_CHALLENGE_STAMP_4: return "Return Challenge (Stamp) - Recycler";
        case TABLE_TENNIS_RETURN_CHALLENGE_STAMP_5: return "Return Challenge (Stamp) - Save Face";
        case GOLF_STAMP_1: return "Golf (Stamp) - Under Par";
        case GOLF_STAMP_2: return "Golf (Stamp) - Chip In";
        case GOLF_STAMP_3: return "Golf (Stamp) - King of Clubs";
        case GOLF_STAMP_4: return "Golf (Stamp) - Ace of Clubs";
        case GOLF_STAMP_5: return "Golf (Stamp) - Hole in One";
        case BOWLING_STANDARD_GAME_STAMP_1: return "Bowling Standard (Stamp) - Gobble Gobble";
        case BOWLING_STANDARD_GAME_STAMP_2: return "Bowling Standard (Stamp) - Split Spare";
        case BOWLING_STANDARD_GAME_STAMP_3: return "Bowling Standard (Stamp) - High Roller";
        case BOWLING_STANDARD_GAME_STAMP_4: return "Bowling Standard (Stamp) - Pin Dropper";
        case BOWLING_STANDARD_GAME_STAMP_5: return "Bowling Standard (Stamp) - Perfect Game";
        case BOWLING_100_PIN_STAMP_1: return "Bowling 100-Pin (Stamp) - Super Strike";
        case BOWLING_100_PIN_STAMP_2: return "Bowling 100-Pin (Stamp) - Split Spare";
        case BOWLING_100_PIN_STAMP_3: return "Bowling 100-Pin (Stamp) - Off the Wall";
        case BOWLING_100_PIN_STAMP_4: return "Bowling 100-Pin (Stamp) - Secret Strike";
        case BOWLING_100_PIN_STAMP_5: return "Bowling 100-Pin (Stamp) - Pin Dropper";
        case BOWLING_SPIN_CONTROL_STAMP_1: return "Spin Control (Stamp) - One for All";
        case BOWLING_SPIN_CONTROL_STAMP_2: return "Spin Control (Stamp) - Split Spare";
        case BOWLING_SPIN_CONTROL_STAMP_3: return "Spin Control (Stamp) - Head First";
        case BOWLING_SPIN_CONTROL_STAMP_4: return "Spin Control (Stamp) - English Major";
        case BOWLING_SPIN_CONTROL_STAMP_5: return "Spin Control (Stamp) - Pin Dropper";
        case POWER_CRUISING_STAMP_1: return "Power Cruising (Stamp) - Ringmaster";
        case POWER_CRUISING_STAMP_2: return "Power Cruising (Stamp) - 5,000-Pointer";
        case POWER_CRUISING_STAMP_3: return "Power Cruising (Stamp) - Power Cruiser";
        case POWER_CRUISING_STAMP_4: return "Power Cruising (Stamp) - Power Jumper";
        case POWER_CRUISING_STAMP_5: return "Power Cruising (Stamp) - Leisure Cruiser";
        case CANOEING_STAMP_1: return "Canoeing (Stamp) - Beginner License";
        case CANOEING_STAMP_2: return "Canoeing (Stamp) - Intermediate License";
        case CANOEING_STAMP_3: return "Canoeing (Stamp) - Expert License";
        case CANOEING_STAMP_4: return "Canoeing (Stamp) - Ducks in a Row";
        case CANOEING_STAMP_5: return "Canoeing (Stamp) - Cut the Red Tape";
        case CYCLING_STAMP_1: return "Cycling (Stamp) - Last Gasp";
        case CYCLING_STAMP_2: return "Cycling (Stamp) - First of Many";
        case CYCLING_STAMP_3: return "Cycling (Stamp) - 1-Stage Master";
        case CYCLING_STAMP_4: return "Cycling (Stamp) - 3-Stage Master";
        case CYCLING_STAMP_5: return "Cycling (Stamp) - 6-Stage Master";
        case SKYDIVING_STAMP_1: return "Skydiving (Stamp) - High Five";
        case SKYDIVING_STAMP_2: return "Skydiving (Stamp) - For the Birds";
        case SKYDIVING_STAMP_3: return "Skydiving (Stamp) - Friends in High Places";
        case SKYDIVING_STAMP_4: return "Skydiving (Stamp) - Camera Shy";
        case SKYDIVING_STAMP_5: return "Skydiving (Stamp) - 200-point Dive";
        case ISLAND_FLYOVER_STAMP_1: return "Island Flyover (Stamp) - Island Hopper";
        case ISLAND_FLYOVER_STAMP_2: return "Island Flyover (Stamp) - Pop Frenzy";
        case ISLAND_FLYOVER_STAMP_3: return "Island Flyover (Stamp) - Follow That Plane";
        case ISLAND_FLYOVER_STAMP_4: return "Island Flyover (Stamp) - Wuhu Tour Guide";
        case ISLAND_FLYOVER_STAMP_5: return "Island Flyover (Stamp) - Balloonatic";

        default: 
            kiwi::cout << "Bad ID: " << id << kiwi::endl;
            return "Unknown Check ID";
    }
}

/**
 * @brief Clears check state
 */
void CheckMgr::Clear() {
    for(u16 i = 0x0000; i < CheckMgr::COUNT; i++)
    {
        SetCheckState(CheckID(i), false);
    }
}

/**
 * @brief Sets debug state
 */
void CheckMgr::Debug() {
    for(u16 i = 0x0000; i < CheckMgr::COUNT; i++)
    {
        kiwi::cout << "Check " << GetCheckName(CheckID(i)) << " is " << CheckMgr::GetCheckState(CheckID(i)) << kiwi::endl;
    }
}

bool CheckMgr::GetCheckState(CheckID id) const {
    return mCheckState.Get(id, false);
}

void CheckMgr::SetCheckState(CheckID id, bool state) {
    mCheckState.Insert(id, state);
}

u16 CheckMgr::GetItemID(CheckID id) const {
    u16 itemIDResult = mCheckToItemID.Get(id, 0xFFFF);
    K_ASSERT(itemIDResult != 0xFFFF);
    return itemIDResult;
}

void CheckMgr::SetItemID(CheckID id, u16 itemID) {
    mCheckToItemID.Insert(id, itemID);
}

void CheckMgr::GiveItemFromCheck(CheckID id) {
    //u16 itemID = GetItemID(id);
    //ItemMgr::GetInstance().GiveItemToPlayer(ItemMgr::ItemID(itemID)); // this should be what's actually ran
    ItemMgr::GetInstance().GiveItemToPlayer(ItemMgr::BASKETBALL_3PT_TIMER);
    SetCheckState(id, true);
}



} // namespace AP