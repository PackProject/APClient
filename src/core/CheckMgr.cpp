#include "core/CheckMgr.h"

#include "core/ItemMgr.h"

#include <libkiwi.h>

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
 * @param rBin Binary file contents
 */
void CheckMgr::DeserializeImpl(const Bin& rBin) {
    ;
}

/**
 * @brief Serializes binary contents (internal implementation)
 *
 * @param rBin Binary file contents
 */
void CheckMgr::SerializeImpl(Bin& rBin) const {
    ;
}

const char* CheckMgr::GetCheckName(CheckMgr::CheckID id) const {
    switch (id) {
    case SWORDPLAY_DUEL_STAMP_1:
        return "Swordplay Duel (Stamp) - Cliff-hanger";
    case SWORDPLAY_DUEL_STAMP_2:
        return "Swordplay Duel (Stamp) - Straight to the Point";
    case SWORDPLAY_DUEL_STAMP_3:
        return "Swordplay Duel (Stamp) - Met Your Match";
    case SWORDPLAY_DUEL_STAMP_4:
        return "Swordplay Duel (Stamp) - One-Hit Wonder";
    case SWORDPLAY_DUEL_STAMP_5:
        return "Swordplay Duel (Stamp) - Last Mii Standing";
    case SWORDPLAY_SPEED_SLICE_STAMP_1:
        return "Swordplay Speed Slice (Stamp) - Slice and Dice";
    case SWORDPLAY_SPEED_SLICE_STAMP_2:
        return "Swordplay Speed Slice (Stamp) - Slicing Machine";
    case SWORDPLAY_SPEED_SLICE_STAMP_3:
        return "Swordplay Speed Slice (Stamp) - Psychic Slice";
    case SWORDPLAY_SPEED_SLICE_STAMP_4:
        return "Swordplay Speed Slice (Stamp) - Double Time";
    case SWORDPLAY_SPEED_SLICE_STAMP_5:
        return "Swordplay Speed Slice (Stamp) - A Cut Above";
    case SWORDPLAY_SHOWDOWN_STAMP_1:
        return "Swordplay Showdown (Stamp) - Not a Scratch";
    case SWORDPLAY_SHOWDOWN_STAMP_2:
        return "Swordplay Showdown (Stamp) - Sword Fighter";
    case SWORDPLAY_SHOWDOWN_STAMP_3:
        return "Swordplay Showdown (Stamp) - Perfect 10";
    case SWORDPLAY_SHOWDOWN_STAMP_4:
        return "Swordplay Showdown (Stamp) - Swordmaster";
    case SWORDPLAY_SHOWDOWN_STAMP_5:
        return "Swordplay Showdown (Stamp) - Untouchable";
    case WAKEBOARDING_STAMP_1:
        return "Wakeboarding (Stamp) - Huge Air";
    case WAKEBOARDING_STAMP_2:
        return "Wakeboarding (Stamp) - Bag of Tricks";
    case WAKEBOARDING_STAMP_3:
        return "Wakeboarding (Stamp) - Smooth Landing";
    case WAKEBOARDING_STAMP_4:
        return "Wakeboarding (Stamp) - Master Carver";
    case WAKEBOARDING_STAMP_5:
        return "Wakeboarding (Stamp) - The Long Way Home";
    case FRISBEE_DOG_STAMP_1:
        return "Frisbee Dog (Stamp) - Good Dog";
    case FRISBEE_DOG_STAMP_2:
        return "Frisbee Dog (Stamp) - Balloon Animal";
    case FRISBEE_DOG_STAMP_3:
        return "Frisbee Dog (Stamp) - A for Effort";
    case FRISBEE_DOG_STAMP_4:
        return "Frisbee Dog (Stamp) - Perfect Target";
    case FRISBEE_DOG_STAMP_5:
        return "Frisbee Dog (Stamp) - Golden Arm";
    case FRISBEE_GOLF_STAMP_1:
        return "Frisbee Golf (Stamp) - Under Par";
    case FRISBEE_GOLF_STAMP_2:
        return "Frisbee Golf (Stamp) - Lucky Skip";
    case FRISBEE_GOLF_STAMP_3:
        return "Frisbee Golf (Stamp) - On a Roll";
    case FRISBEE_GOLF_STAMP_4:
        return "Frisbee Golf (Stamp) - Hole in One";
    case FRISBEE_GOLF_STAMP_5:
        return "Frisbee Golf (Stamp) - Straight and Narrow";
    case ARCHERY_STAMP_1:
        return "Archery (Stamp) - Bull Stampede";
    case ARCHERY_STAMP_2:
        return "Archery (Stamp) - Sure Shot";
    case ARCHERY_STAMP_3:
        return "Archery (Stamp) - Century Shot";
    case ARCHERY_STAMP_4:
        return "Archery (Stamp) - A Secret to Everybody";
    case ARCHERY_STAMP_5:
        return "Archery (Stamp) - Sharpshooter";
    case BASKETBALL_3PT_CONTEST_STAMP_1:
        return "3-Point Contest (Stamp) - Hot Streak";
    case BASKETBALL_3PT_CONTEST_STAMP_2:
        return "3-Point Contest (Stamp) - Bonus Plumber";
    case BASKETBALL_3PT_CONTEST_STAMP_3:
        return "3-Point Contest (Stamp) - Quick Draw";
    case BASKETBALL_3PT_CONTEST_STAMP_4:
        return "3-Point Contest (Stamp) - Hot Hand";
    case BASKETBALL_3PT_CONTEST_STAMP_5:
        return "3-Point Contest (Stamp) - Pure Shooter";
    case BASKETBALL_PICKUP_GAME_1:
        return "Pickup Game (Stamp) - Triple Dip";
    case BASKETBALL_PICKUP_GAME_2:
        return "Pickup Game (Stamp) - Rim Rattler";
    case BASKETBALL_PICKUP_GAME_3:
        return "Pickup Game (Stamp) - Lights Out";
    case BASKETBALL_PICKUP_GAME_4:
        return "Pickup Game (Stamp) - Buzzer Beater";
    case BASKETBALL_PICKUP_GAME_5:
        return "Pickup Game (Stamp) - Hoop Hero";
    case TABLE_TENNIS_MATCH_STAMP_1:
        return "Table Tennis Match (Stamp) - In Your Face";
    case TABLE_TENNIS_MATCH_STAMP_2:
        return "Table Tennis Match (Stamp) - Back from the Brink";
    case TABLE_TENNIS_MATCH_STAMP_3:
        return "Table Tennis Match (Stamp) - Epic Rally";
    case TABLE_TENNIS_MATCH_STAMP_4:
        return "Table Tennis Match (Stamp) - Perfectly Matched";
    case TABLE_TENNIS_MATCH_STAMP_5:
        return "Table Tennis Match (Stamp) - Table Titan";
    case TABLE_TENNIS_RETURN_CHALLENGE_STAMP_1:
        return "Return Challenge (Stamp) - 50-pointer";
    case TABLE_TENNIS_RETURN_CHALLENGE_STAMP_2:
        return "Return Challenge (Stamp) - 100-pointer";
    case TABLE_TENNIS_RETURN_CHALLENGE_STAMP_3:
        return "Return Challenge (Stamp) - 200-pointer";
    case TABLE_TENNIS_RETURN_CHALLENGE_STAMP_4:
        return "Return Challenge (Stamp) - Recycler";
    case TABLE_TENNIS_RETURN_CHALLENGE_STAMP_5:
        return "Return Challenge (Stamp) - Save Face";
    case GOLF_STAMP_1:
        return "Golf (Stamp) - Under Par";
    case GOLF_STAMP_2:
        return "Golf (Stamp) - Chip In";
    case GOLF_STAMP_3:
        return "Golf (Stamp) - King of Clubs";
    case GOLF_STAMP_4:
        return "Golf (Stamp) - Ace of Clubs";
    case GOLF_STAMP_5:
        return "Golf (Stamp) - Hole in One";
    case BOWLING_STANDARD_GAME_STAMP_1:
        return "Bowling Standard (Stamp) - Gobble Gobble";
    case BOWLING_STANDARD_GAME_STAMP_2:
        return "Bowling Standard (Stamp) - Split Spare";
    case BOWLING_STANDARD_GAME_STAMP_3:
        return "Bowling Standard (Stamp) - High Roller";
    case BOWLING_STANDARD_GAME_STAMP_4:
        return "Bowling Standard (Stamp) - Pin Dropper";
    case BOWLING_STANDARD_GAME_STAMP_5:
        return "Bowling Standard (Stamp) - Perfect Game";
    case BOWLING_100_PIN_STAMP_1:
        return "Bowling 100-Pin (Stamp) - Super Strike";
    case BOWLING_100_PIN_STAMP_2:
        return "Bowling 100-Pin (Stamp) - Split Spare";
    case BOWLING_100_PIN_STAMP_3:
        return "Bowling 100-Pin (Stamp) - Off the Wall";
    case BOWLING_100_PIN_STAMP_4:
        return "Bowling 100-Pin (Stamp) - Secret Strike";
    case BOWLING_100_PIN_STAMP_5:
        return "Bowling 100-Pin (Stamp) - Pin Dropper";
    case BOWLING_SPIN_CONTROL_STAMP_1:
        return "Spin Control (Stamp) - One for All";
    case BOWLING_SPIN_CONTROL_STAMP_2:
        return "Spin Control (Stamp) - Split Spare";
    case BOWLING_SPIN_CONTROL_STAMP_3:
        return "Spin Control (Stamp) - Head First";
    case BOWLING_SPIN_CONTROL_STAMP_4:
        return "Spin Control (Stamp) - English Major";
    case BOWLING_SPIN_CONTROL_STAMP_5:
        return "Spin Control (Stamp) - Pin Dropper";
    case POWER_CRUISING_STAMP_1:
        return "Power Cruising (Stamp) - Ringmaster";
    case POWER_CRUISING_STAMP_2:
        return "Power Cruising (Stamp) - 5,000-Pointer";
    case POWER_CRUISING_STAMP_3:
        return "Power Cruising (Stamp) - Power Cruiser";
    case POWER_CRUISING_STAMP_4:
        return "Power Cruising (Stamp) - Power Jumper";
    case POWER_CRUISING_STAMP_5:
        return "Power Cruising (Stamp) - Leisure Cruiser";
    case CANOEING_STAMP_1:
        return "Canoeing (Stamp) - Beginner License";
    case CANOEING_STAMP_2:
        return "Canoeing (Stamp) - Intermediate License";
    case CANOEING_STAMP_3:
        return "Canoeing (Stamp) - Expert License";
    case CANOEING_STAMP_4:
        return "Canoeing (Stamp) - Ducks in a Row";
    case CANOEING_STAMP_5:
        return "Canoeing (Stamp) - Cut the Red Tape";
    case CYCLING_STAMP_1:
        return "Cycling (Stamp) - Last Gasp";
    case CYCLING_STAMP_2:
        return "Cycling (Stamp) - First of Many";
    case CYCLING_STAMP_3:
        return "Cycling (Stamp) - 1-Stage Master";
    case CYCLING_STAMP_4:
        return "Cycling (Stamp) - 3-Stage Master";
    case CYCLING_STAMP_5:
        return "Cycling (Stamp) - 6-Stage Master";
    case SKYDIVING_STAMP_1:
        return "Skydiving (Stamp) - High Five";
    case SKYDIVING_STAMP_2:
        return "Skydiving (Stamp) - For the Birds";
    case SKYDIVING_STAMP_3:
        return "Skydiving (Stamp) - Friends in High Places";
    case SKYDIVING_STAMP_4:
        return "Skydiving (Stamp) - Camera Shy";
    case SKYDIVING_STAMP_5:
        return "Skydiving (Stamp) - 200-point Dive";
    case ISLAND_FLYOVER_STAMP_1:
        return "Island Flyover (Stamp) - Island Hopper";
    case ISLAND_FLYOVER_STAMP_2:
        return "Island Flyover (Stamp) - Pop Frenzy";
    case ISLAND_FLYOVER_STAMP_3:
        return "Island Flyover (Stamp) - Follow That Plane";
    case ISLAND_FLYOVER_STAMP_4:
        return "Island Flyover (Stamp) - Wuhu Tour Guide";
    case ISLAND_FLYOVER_STAMP_5:
        return "Island Flyover (Stamp) - Balloonatic";

    case SWORDPLAY_DUEL_FIRST_WIN:
        return "Swordplay Duel - First Win!";

    case GOLF_COMPLTE_HOLE_1:
        return "Golf - Complete Hole 1!";
    case GOLF_COMPLTE_HOLE_2:
        return "Golf - Complete Hole 2!";
    case GOLF_COMPLTE_HOLE_3:
        return "Golf - Complete Hole 3!";
    case GOLF_COMPLTE_HOLE_4:
        return "Golf - Complete Hole 4!";
    case GOLF_COMPLTE_HOLE_5:
        return "Golf - Complete Hole 5!";
    case GOLF_COMPLTE_HOLE_6:
        return "Golf - Complete Hole 6!";
    case GOLF_COMPLTE_HOLE_7:
        return "Golf - Complete Hole 7!";
    case GOLF_COMPLTE_HOLE_8:
        return "Golf - Complete Hole 8!";
    case GOLF_COMPLTE_HOLE_9:
        return "Golf - Complete Hole 9!";
    case GOLF_COMPLTE_HOLE_10:
        return "Golf - Complete Hole 10!";
    case GOLF_COMPLTE_HOLE_11:
        return "Golf - Complete Hole 11!";
    case GOLF_COMPLTE_HOLE_12:
        return "Golf - Complete Hole 12!";
    case GOLF_COMPLTE_HOLE_13:
        return "Golf - Complete Hole 13!";
    case GOLF_COMPLTE_HOLE_14:
        return "Golf - Complete Hole 14!";
    case GOLF_COMPLTE_HOLE_15:
        return "Golf - Complete Hole 15!";
    case GOLF_COMPLTE_HOLE_16:
        return "Golf - Complete Hole 16!";
    case GOLF_COMPLTE_HOLE_17:
        return "Golf - Complete Hole 17!";
    case GOLF_COMPLTE_HOLE_18:
        return "Golf - Complete Hole 18!";
    case GOLF_COMPLTE_HOLE_19:
        return "Golf - Complete Hole 19!";
    case GOLF_COMPLTE_HOLE_20:
        return "Golf - Complete Hole 20!";
    case GOLF_COMPLTE_HOLE_21:
        return "Golf - Complete Hole 21!";

    case BOWLING_STANDARD_FIRST_STRIKE:
        return "Bowling Standard Game - First Strike!";

    case ISLAND_FLYOVER_IPOINT_GROUP_1:
        return "Progressive Island Flyover I Point Group 1";
    case ISLAND_FLYOVER_IPOINT_GROUP_2:
        return "Progressive Island Flyover I Point Group 2";
    case ISLAND_FLYOVER_IPOINT_GROUP_3:
        return "Progressive Island Flyover I Point Group 3";
    case ISLAND_FLYOVER_IPOINT_GROUP_4:
        return "Progressive Island Flyover I Point Group 4";
    case ISLAND_FLYOVER_IPOINT_GROUP_5:
        return "Progressive Island Flyover I Point Group 5";
    case ISLAND_FLYOVER_IPOINT_GROUP_6:
        return "Progressive Island Flyover I Point Group 6";
    case ISLAND_FLYOVER_IPOINT_GROUP_7:
        return "Progressive Island Flyover I Point Group 7";
    case ISLAND_FLYOVER_IPOINT_GROUP_8:
        return "Progressive Island Flyover I Point Group 8";
    case ISLAND_FLYOVER_IPOINT_GROUP_9:
        return "Progressive Island Flyover I Point Group 9";
    case ISLAND_FLYOVER_IPOINT_GROUP_10:
        return "Progressive Island Flyover I Point Group 10";
    case ISLAND_FLYOVER_IPOINT_GROUP_11:
        return "Progressive Island Flyover I Point Group 11";
    case ISLAND_FLYOVER_IPOINT_GROUP_12:
        return "Progressive Island Flyover I Point Group 12";

    default:
        kiwi::cout << "Bad ID: " << id << kiwi::endl;
        return "Unknown Check ID";
    }
}

/**
 * @brief Clears check state
 */
void CheckMgr::Clear() {
    GenerateCheckIDArray();

    for (int i = 0; i < checkIDArr.Size(); i++) {
        CheckID currCheckID = checkIDArr[i];
        SetCheckState(currCheckID, false);
    }
}

/**
 * @brief Sets debug state
 */
void CheckMgr::Debug() {}

bool CheckMgr::GetCheckState(CheckID id) const {
    return mCheckState.Get(id, false);
}

void CheckMgr::SetCheckState(CheckID id, bool state) {
    kiwi::cout << "Check: " << GetCheckName(id) << " has been set to " << state
               << kiwi::endl;
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
    // u16 itemID = GetItemID(id);
    // ItemMgr::GetInstance().GiveItemToPlayer(ItemMgr::ItemID(itemID)); // this
    // should be what's actually ran
    ItemMgr::GetInstance().GiveItemToPlayer(ItemMgr::BASKETBALL_3PT_TIMER);
    SetCheckState(id, true);
}

void CheckMgr::GenerateCheckIDArray() {
    checkIDArr[0] = SWORDPLAY_SHOWDOWN_STAMP_1;
    checkIDArr[1] = SWORDPLAY_SHOWDOWN_STAMP_2;
    checkIDArr[2] = SWORDPLAY_SHOWDOWN_STAMP_3;
    checkIDArr[3] = SWORDPLAY_SHOWDOWN_STAMP_4;
    checkIDArr[4] = SWORDPLAY_SHOWDOWN_STAMP_5;
    checkIDArr[5] = SWORDPLAY_DUEL_STAMP_1;
    checkIDArr[6] = SWORDPLAY_DUEL_STAMP_2;
    checkIDArr[7] = SWORDPLAY_DUEL_STAMP_3;
    checkIDArr[8] = SWORDPLAY_DUEL_STAMP_4;
    checkIDArr[9] = SWORDPLAY_DUEL_STAMP_5;
    checkIDArr[10] = SWORDPLAY_SPEED_SLICE_STAMP_1;
    checkIDArr[11] = SWORDPLAY_SPEED_SLICE_STAMP_2;
    checkIDArr[12] = SWORDPLAY_SPEED_SLICE_STAMP_3;
    checkIDArr[13] = SWORDPLAY_SPEED_SLICE_STAMP_4;
    checkIDArr[14] = SWORDPLAY_SPEED_SLICE_STAMP_5;
    checkIDArr[15] = POWER_CRUISING_STAMP_1;
    checkIDArr[16] = POWER_CRUISING_STAMP_2;
    checkIDArr[17] = POWER_CRUISING_STAMP_3;
    checkIDArr[18] = POWER_CRUISING_STAMP_4;
    checkIDArr[19] = POWER_CRUISING_STAMP_5;
    checkIDArr[20] = ARCHERY_STAMP_1;
    checkIDArr[21] = ARCHERY_STAMP_2;
    checkIDArr[22] = ARCHERY_STAMP_3;
    checkIDArr[23] = ARCHERY_STAMP_4;
    checkIDArr[24] = ARCHERY_STAMP_5;
    checkIDArr[25] = FRISBEE_DOG_STAMP_1;
    checkIDArr[26] = FRISBEE_DOG_STAMP_2;
    checkIDArr[27] = FRISBEE_DOG_STAMP_3;
    checkIDArr[28] = FRISBEE_DOG_STAMP_4;
    checkIDArr[29] = FRISBEE_DOG_STAMP_5;
    checkIDArr[30] = BASKETBALL_3PT_CONTEST_STAMP_1;
    checkIDArr[31] = BASKETBALL_3PT_CONTEST_STAMP_2;
    checkIDArr[32] = BASKETBALL_3PT_CONTEST_STAMP_3;
    checkIDArr[33] = BASKETBALL_3PT_CONTEST_STAMP_4;
    checkIDArr[34] = BASKETBALL_3PT_CONTEST_STAMP_5;
    checkIDArr[35] = BASKETBALL_PICKUP_GAME_1;
    checkIDArr[36] = BASKETBALL_PICKUP_GAME_2;
    checkIDArr[37] = BASKETBALL_PICKUP_GAME_3;
    checkIDArr[38] = BASKETBALL_PICKUP_GAME_4;
    checkIDArr[39] = BASKETBALL_PICKUP_GAME_5;
    checkIDArr[40] = BOWLING_STANDARD_GAME_STAMP_1;
    checkIDArr[41] = BOWLING_STANDARD_GAME_STAMP_2;
    checkIDArr[42] = BOWLING_STANDARD_GAME_STAMP_3;
    checkIDArr[43] = BOWLING_STANDARD_GAME_STAMP_4;
    checkIDArr[44] = BOWLING_STANDARD_GAME_STAMP_5;
    checkIDArr[45] = BOWLING_100_PIN_STAMP_1;
    checkIDArr[46] = BOWLING_100_PIN_STAMP_2;
    checkIDArr[47] = BOWLING_100_PIN_STAMP_3;
    checkIDArr[48] = BOWLING_100_PIN_STAMP_4;
    checkIDArr[49] = BOWLING_100_PIN_STAMP_5;
    checkIDArr[50] = BOWLING_SPIN_CONTROL_STAMP_1;
    checkIDArr[51] = BOWLING_SPIN_CONTROL_STAMP_2;
    checkIDArr[52] = BOWLING_SPIN_CONTROL_STAMP_3;
    checkIDArr[53] = BOWLING_SPIN_CONTROL_STAMP_4;
    checkIDArr[54] = BOWLING_SPIN_CONTROL_STAMP_5;
    checkIDArr[55] = CANOEING_STAMP_1;
    checkIDArr[56] = CANOEING_STAMP_2;
    checkIDArr[57] = CANOEING_STAMP_3;
    checkIDArr[58] = CANOEING_STAMP_4;
    checkIDArr[59] = CANOEING_STAMP_5;
    checkIDArr[60] = TABLE_TENNIS_RETURN_CHALLENGE_STAMP_1;
    checkIDArr[61] = TABLE_TENNIS_RETURN_CHALLENGE_STAMP_2;
    checkIDArr[62] = TABLE_TENNIS_RETURN_CHALLENGE_STAMP_3;
    checkIDArr[63] = TABLE_TENNIS_RETURN_CHALLENGE_STAMP_4;
    checkIDArr[64] = TABLE_TENNIS_RETURN_CHALLENGE_STAMP_5;
    checkIDArr[65] = TABLE_TENNIS_MATCH_STAMP_1;
    checkIDArr[66] = TABLE_TENNIS_MATCH_STAMP_2;
    checkIDArr[67] = TABLE_TENNIS_MATCH_STAMP_3;
    checkIDArr[68] = TABLE_TENNIS_MATCH_STAMP_4;
    checkIDArr[69] = TABLE_TENNIS_MATCH_STAMP_5;
    checkIDArr[70] = WAKEBOARDING_STAMP_1;
    checkIDArr[71] = WAKEBOARDING_STAMP_2;
    checkIDArr[72] = WAKEBOARDING_STAMP_3;
    checkIDArr[73] = WAKEBOARDING_STAMP_4;
    checkIDArr[74] = WAKEBOARDING_STAMP_5;
    checkIDArr[75] = ISLAND_FLYOVER_STAMP_1;
    checkIDArr[76] = ISLAND_FLYOVER_STAMP_2;
    checkIDArr[77] = ISLAND_FLYOVER_STAMP_3;
    checkIDArr[78] = ISLAND_FLYOVER_STAMP_4;
    checkIDArr[79] = ISLAND_FLYOVER_STAMP_5;
    checkIDArr[80] = GOLF_STAMP_1;
    checkIDArr[81] = GOLF_STAMP_2;
    checkIDArr[82] = GOLF_STAMP_3;
    checkIDArr[83] = GOLF_STAMP_4;
    checkIDArr[84] = GOLF_STAMP_5;
    checkIDArr[85] = FRISBEE_GOLF_STAMP_1;
    checkIDArr[86] = FRISBEE_GOLF_STAMP_2;
    checkIDArr[87] = FRISBEE_GOLF_STAMP_3;
    checkIDArr[88] = FRISBEE_GOLF_STAMP_4;
    checkIDArr[89] = FRISBEE_GOLF_STAMP_5;
    checkIDArr[90] = CYCLING_STAMP_1;
    checkIDArr[91] = CYCLING_STAMP_2;
    checkIDArr[92] = CYCLING_STAMP_3;
    checkIDArr[93] = CYCLING_STAMP_4;
    checkIDArr[94] = CYCLING_STAMP_5;
    checkIDArr[95] = SKYDIVING_STAMP_1;
    checkIDArr[96] = SKYDIVING_STAMP_2;
    checkIDArr[97] = SKYDIVING_STAMP_3;
    checkIDArr[98] = SKYDIVING_STAMP_4;
    checkIDArr[99] = SKYDIVING_STAMP_5;
    checkIDArr[100] = SWORDPLAY_DUEL_FIRST_WIN;
    checkIDArr[101] = GOLF_COMPLTE_HOLE_1;
    checkIDArr[102] = GOLF_COMPLTE_HOLE_2;
    checkIDArr[103] = GOLF_COMPLTE_HOLE_3;
    checkIDArr[104] = GOLF_COMPLTE_HOLE_4;
    checkIDArr[105] = GOLF_COMPLTE_HOLE_5;
    checkIDArr[106] = GOLF_COMPLTE_HOLE_6;
    checkIDArr[107] = GOLF_COMPLTE_HOLE_7;
    checkIDArr[108] = GOLF_COMPLTE_HOLE_8;
    checkIDArr[109] = GOLF_COMPLTE_HOLE_9;
    checkIDArr[110] = GOLF_COMPLTE_HOLE_10;
    checkIDArr[111] = GOLF_COMPLTE_HOLE_11;
    checkIDArr[112] = GOLF_COMPLTE_HOLE_12;
    checkIDArr[113] = GOLF_COMPLTE_HOLE_13;
    checkIDArr[114] = GOLF_COMPLTE_HOLE_14;
    checkIDArr[115] = GOLF_COMPLTE_HOLE_15;
    checkIDArr[116] = GOLF_COMPLTE_HOLE_16;
    checkIDArr[117] = GOLF_COMPLTE_HOLE_17;
    checkIDArr[118] = GOLF_COMPLTE_HOLE_18;
    checkIDArr[119] = GOLF_COMPLTE_HOLE_19;
    checkIDArr[120] = GOLF_COMPLTE_HOLE_20;
    checkIDArr[121] = GOLF_COMPLTE_HOLE_21;
    checkIDArr[122] = BOWLING_STANDARD_FIRST_STRIKE;
    checkIDArr[123] = ISLAND_FLYOVER_IPOINT_GROUP_1;
    checkIDArr[124] = ISLAND_FLYOVER_IPOINT_GROUP_2;
    checkIDArr[125] = ISLAND_FLYOVER_IPOINT_GROUP_3;
    checkIDArr[126] = ISLAND_FLYOVER_IPOINT_GROUP_4;
    checkIDArr[127] = ISLAND_FLYOVER_IPOINT_GROUP_5;
    checkIDArr[128] = ISLAND_FLYOVER_IPOINT_GROUP_6;
    checkIDArr[129] = ISLAND_FLYOVER_IPOINT_GROUP_7;
    checkIDArr[130] = ISLAND_FLYOVER_IPOINT_GROUP_8;
    checkIDArr[131] = ISLAND_FLYOVER_IPOINT_GROUP_9;
    checkIDArr[132] = ISLAND_FLYOVER_IPOINT_GROUP_10;
    checkIDArr[133] = ISLAND_FLYOVER_IPOINT_GROUP_11;
    checkIDArr[134] = ISLAND_FLYOVER_IPOINT_GROUP_12;
}

} // namespace AP
