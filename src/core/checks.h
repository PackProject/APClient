#ifndef APCLIENT_CORE_CHECKS_H
#define APCLIENT_CORE_CHECKS_H
#include <types.h>

// clang-format off

// X-macro for all Archipelago checks
// X(ID, Code name identifier, Readable name string)
#define AP_CHECKS_X_MACRO \
    X(0x0000, SWORDPLAY_SHOWDOWN_STAMP_1, "Swordplay Showdown (Stamp) - Not a Scratch") \
    X(0x0001, SWORDPLAY_SHOWDOWN_STAMP_2, "Swordplay Showdown (Stamp) - Sword Fighter") \
    X(0x0002, SWORDPLAY_SHOWDOWN_STAMP_3, "Swordplay Showdown (Stamp) - Perfect 10") \
    X(0x0003, SWORDPLAY_SHOWDOWN_STAMP_4, "Swordplay Showdown (Stamp) - Swordmaster") \
    X(0x0004, SWORDPLAY_SHOWDOWN_STAMP_5, "Swordplay Showdown (Stamp) - Untouchable") \
    X(0x0005, SWORDPLAY_DUEL_STAMP_1, "Swordplay Duel (Stamp) - Cliff-hanger") \
    X(0x0006, SWORDPLAY_DUEL_STAMP_2, "Swordplay Duel (Stamp) - Straight to the Point") \
    X(0x0007, SWORDPLAY_DUEL_STAMP_3, "Swordplay Duel (Stamp) - Met Your Match") \
    X(0x0008, SWORDPLAY_DUEL_STAMP_4, "Swordplay Duel (Stamp) - One-Hit Wonder") \
    X(0x0009, SWORDPLAY_DUEL_STAMP_5, "Swordplay Duel (Stamp) - Last Mii Standing") \
    X(0x000A, SWORDPLAY_SPEED_SLICE_STAMP_1, "Swordplay Speed Slice (Stamp) - Slice and Dice") \
    X(0x000B, SWORDPLAY_SPEED_SLICE_STAMP_2, "Swordplay Speed Slice (Stamp) - Slicing Machine") \
    X(0x000C, SWORDPLAY_SPEED_SLICE_STAMP_3, "Swordplay Speed Slice (Stamp) - Psychic Slice") \
    X(0x000D, SWORDPLAY_SPEED_SLICE_STAMP_4, "Swordplay Speed Slice (Stamp) - Double Time") \
    X(0x000E, SWORDPLAY_SPEED_SLICE_STAMP_5, "Swordplay Speed Slice (Stamp) - A Cut Above") \
    X(0x000F, POWER_CRUISING_STAMP_1, "Power Cruising (Stamp) - Ringmaster") \
    X(0x0010, POWER_CRUISING_STAMP_2, "Power Cruising (Stamp) - 5") \
    X(0x0011, POWER_CRUISING_STAMP_3, "Power Cruising (Stamp) - Power Cruiser") \
    X(0x0012, POWER_CRUISING_STAMP_4, "Power Cruising (Stamp) - Power Jumper") \
    X(0x0013, POWER_CRUISING_STAMP_5, "Power Cruising (Stamp) - Leisure Cruiser") \
    X(0x0019, ARCHERY_STAMP_1, "Archery (Stamp) - Bull Stampede") \
    X(0x001A, ARCHERY_STAMP_2, "Archery (Stamp) - Sure Shot") \
    X(0x001B, ARCHERY_STAMP_3, "Archery (Stamp) - Century Shot") \
    X(0x001C, ARCHERY_STAMP_4, "Archery (Stamp) - A Secret to Everybody") \
    X(0x001D, ARCHERY_STAMP_5, "Archery (Stamp) - Sharpshooter") \
    X(0x001E, FRISBEE_DOG_STAMP_1, "Frisbee Dog (Stamp) - Good Dog") \
    X(0x001F, FRISBEE_DOG_STAMP_2, "Frisbee Dog (Stamp) - Balloon Animal") \
    X(0x0020, FRISBEE_DOG_STAMP_3, "Frisbee Dog (Stamp) - A for Effort") \
    X(0x0021, FRISBEE_DOG_STAMP_4, "Frisbee Dog (Stamp) - Perfect Target") \
    X(0x0022, FRISBEE_DOG_STAMP_5, "Frisbee Dog (Stamp) - Golden Arm") \
    X(0x0023, BASKETBALL_3PT_CONTEST_STAMP_1, "3-Point Contest (Stamp) - Hot Streak") \
    X(0x0024, BASKETBALL_3PT_CONTEST_STAMP_2, "3-Point Contest (Stamp) - Bonus Plumber") \
    X(0x0025, BASKETBALL_3PT_CONTEST_STAMP_3, "3-Point Contest (Stamp) - Quick Draw") \
    X(0x0026, BASKETBALL_3PT_CONTEST_STAMP_4, "3-Point Contest (Stamp) - Hot Hand") \
    X(0x0027, BASKETBALL_3PT_CONTEST_STAMP_5, "3-Point Contest (Stamp) - Pure Shooter") \
    X(0x0028, BASKETBALL_PICKUP_GAME_1, "Pickup Game (Stamp) - Triple Dip") \
    X(0x0029, BASKETBALL_PICKUP_GAME_2, "Pickup Game (Stamp) - Rim Rattler") \
    X(0x002A, BASKETBALL_PICKUP_GAME_3, "Pickup Game (Stamp) - Lights Out") \
    X(0x002B, BASKETBALL_PICKUP_GAME_4, "Pickup Game (Stamp) - Buzzer Beater") \
    X(0x002C, BASKETBALL_PICKUP_GAME_5, "Pickup Game (Stamp) - Hoop Hero") \
    X(0x002D, BOWLING_STANDARD_GAME_STAMP_1, "Bowling Standard (Stamp) - Gobble Gobble") \
    X(0x002E, BOWLING_STANDARD_GAME_STAMP_2, "Bowling Standard (Stamp) - Split Spare") \
    X(0x002F, BOWLING_STANDARD_GAME_STAMP_3, "Bowling Standard (Stamp) - High Roller") \
    X(0x0030, BOWLING_STANDARD_GAME_STAMP_4, "Bowling Standard (Stamp) - Pin Dropper") \
    X(0x0031, BOWLING_STANDARD_GAME_STAMP_5, "Bowling Standard (Stamp) - Perfect Game") \
    X(0x0032, BOWLING_100_PIN_STAMP_1, "Bowling 100-Pin (Stamp) - Super Strike") \
    X(0x0033, BOWLING_100_PIN_STAMP_2, "Bowling 100-Pin (Stamp) - Split Spare") \
    X(0x0034, BOWLING_100_PIN_STAMP_3, "Bowling 100-Pin (Stamp) - Off the Wall") \
    X(0x0035, BOWLING_100_PIN_STAMP_4, "Bowling 100-Pin (Stamp) - Secret Strike") \
    X(0x0036, BOWLING_100_PIN_STAMP_5, "Bowling 100-Pin (Stamp) - Pin Dropper") \
    X(0x0037, BOWLING_SPIN_CONTROL_STAMP_1, "Spin Control (Stamp) - One for All") \
    X(0x0038, BOWLING_SPIN_CONTROL_STAMP_2, "Spin Control (Stamp) - Split Spare") \
    X(0x0039, BOWLING_SPIN_CONTROL_STAMP_3, "Spin Control (Stamp) - Head First") \
    X(0x003A, BOWLING_SPIN_CONTROL_STAMP_4, "Spin Control (Stamp) - English Major") \
    X(0x003B, BOWLING_SPIN_CONTROL_STAMP_5, "Spin Control (Stamp) - Pin Dropper") \
    X(0x0041, CANOEING_STAMP_1, "Canoeing (Stamp) - Beginner License") \
    X(0x0042, CANOEING_STAMP_2, "Canoeing (Stamp) - Intermediate License") \
    X(0x0043, CANOEING_STAMP_3, "Canoeing (Stamp) - Expert License") \
    X(0x0044, CANOEING_STAMP_4, "Canoeing (Stamp) - Ducks in a Row") \
    X(0x0045, CANOEING_STAMP_5, "Canoeing (Stamp) - Cut the Red Tape") \
    X(0x0046, TABLE_TENNIS_RETURN_CHALLENGE_STAMP_1, "Return Challenge (Stamp) - 50-pointer") \
    X(0x0047, TABLE_TENNIS_RETURN_CHALLENGE_STAMP_2, "Return Challenge (Stamp) - 100-pointer") \
    X(0x0048, TABLE_TENNIS_RETURN_CHALLENGE_STAMP_3, "Return Challenge (Stamp) - 200-pointer") \
    X(0x0049, TABLE_TENNIS_RETURN_CHALLENGE_STAMP_4, "Return Challenge (Stamp) - Recycler") \
    X(0x004A, TABLE_TENNIS_RETURN_CHALLENGE_STAMP_5, "Return Challenge (Stamp) - Save Face") \
    X(0x004B, TABLE_TENNIS_MATCH_STAMP_1, "Table Tennis Match (Stamp) - In Your Face") \
    X(0x004C, TABLE_TENNIS_MATCH_STAMP_2, "Table Tennis Match (Stamp) - Back from the Brink") \
    X(0x004D, TABLE_TENNIS_MATCH_STAMP_3, "Table Tennis Match (Stamp) - Epic Rally") \
    X(0x004E, TABLE_TENNIS_MATCH_STAMP_4, "Table Tennis Match (Stamp) - Perfectly Matched") \
    X(0x004F, TABLE_TENNIS_MATCH_STAMP_5, "Table Tennis Match (Stamp) - Table Titan") \
    X(0x0050, WAKEBOARDING_STAMP_1, "Wakeboarding (Stamp) - Huge Air") \
    X(0x0051, WAKEBOARDING_STAMP_2, "Wakeboarding (Stamp) - Bag of Tricks") \
    X(0x0052, WAKEBOARDING_STAMP_3, "Wakeboarding (Stamp) - Smooth Landing") \
    X(0x0053, WAKEBOARDING_STAMP_4, "Wakeboarding (Stamp) - Master Carver") \
    X(0x0054, WAKEBOARDING_STAMP_5, "Wakeboarding (Stamp) - The Long Way Home") \
    X(0x0055, ISLAND_FLYOVER_STAMP_1, "Island Flyover (Stamp) - Island Hopper") \
    X(0x0056, ISLAND_FLYOVER_STAMP_2, "Island Flyover (Stamp) - Pop Frenzy") \
    X(0x0057, ISLAND_FLYOVER_STAMP_3, "Island Flyover (Stamp) - Follow That Plane") \
    X(0x0058, ISLAND_FLYOVER_STAMP_4, "Island Flyover (Stamp) - Wuhu Tour Guide") \
    X(0x0059, ISLAND_FLYOVER_STAMP_5, "Island Flyover (Stamp) - Balloonatic") \
    X(0x005F, GOLF_STAMP_1, "Golf (Stamp) - Under Par") \
    X(0x0060, GOLF_STAMP_2, "Golf (Stamp) - Chip In") \
    X(0x0061, GOLF_STAMP_3, "Golf (Stamp) - King of Clubs") \
    X(0x0062, GOLF_STAMP_4, "Golf (Stamp) - Ace of Clubs") \
    X(0x0063, GOLF_STAMP_5, "Golf (Stamp) - Hole in One") \
    X(0x0064, FRISBEE_GOLF_STAMP_1, "Frisbee Golf (Stamp) - Under Par") \
    X(0x0065, FRISBEE_GOLF_STAMP_2, "Frisbee Golf (Stamp) - Lucky Skip") \
    X(0x0066, FRISBEE_GOLF_STAMP_3, "Frisbee Golf (Stamp) - On a Roll") \
    X(0x0067, FRISBEE_GOLF_STAMP_4, "Frisbee Golf (Stamp) - Hole in One") \
    X(0x0068, FRISBEE_GOLF_STAMP_5, "Frisbee Golf (Stamp) - Straight and Narrow") \
    X(0x006E, CYCLING_STAMP_1, "Cycling (Stamp) - Last Gasp") \
    X(0x006F, CYCLING_STAMP_2, "Cycling (Stamp) - First of Many") \
    X(0x0070, CYCLING_STAMP_3, "Cycling (Stamp) - 1-Stage Master") \
    X(0x0071, CYCLING_STAMP_4, "Cycling (Stamp) - 3-Stage Master") \
    X(0x0072, CYCLING_STAMP_5, "Cycling (Stamp) - 6-Stage Master") \
    X(0x0073, SKYDIVING_STAMP_1, "Skydiving (Stamp) - High Five") \
    X(0x0074, SKYDIVING_STAMP_2, "Skydiving (Stamp) - For the Birds") \
    X(0x0075, SKYDIVING_STAMP_3, "Skydiving (Stamp) - Friends in High Places") \
    X(0x0076, SKYDIVING_STAMP_4, "Skydiving (Stamp) - Camera Shy") \
    X(0x0077, SKYDIVING_STAMP_5, "Skydiving (Stamp) - 200-point Dive") \
    X(0x0200, SWORDPLAY_DUEL_FIRST_WIN, "Swordplay Duel - First Win!") \
    X(0x0E00, BOWLING_STANDARD_FIRST_STRIKE, "Bowling Standard Game - First Strike!") \
    X(0x1B00, ISLAND_FLYOVER_IPOINT_GROUP_1, "Progressive Island Flyover I Point Group 1") \
    X(0x1B01, ISLAND_FLYOVER_IPOINT_GROUP_2, "Progressive Island Flyover I Point Group 2") \
    X(0x1B02, ISLAND_FLYOVER_IPOINT_GROUP_3, "Progressive Island Flyover I Point Group 3") \
    X(0x1B03, ISLAND_FLYOVER_IPOINT_GROUP_4, "Progressive Island Flyover I Point Group 4") \
    X(0x1B04, ISLAND_FLYOVER_IPOINT_GROUP_5, "Progressive Island Flyover I Point Group 5") \
    X(0x1B05, ISLAND_FLYOVER_IPOINT_GROUP_6, "Progressive Island Flyover I Point Group 6") \
    X(0x1B06, ISLAND_FLYOVER_IPOINT_GROUP_7, "Progressive Island Flyover I Point Group 7") \
    X(0x1B07, ISLAND_FLYOVER_IPOINT_GROUP_8, "Progressive Island Flyover I Point Group 8") \
    X(0x1B08, ISLAND_FLYOVER_IPOINT_GROUP_9, "Progressive Island Flyover I Point Group 9") \
    X(0x1B09, ISLAND_FLYOVER_IPOINT_GROUP_10, "Progressive Island Flyover I Point Group 10") \
    X(0x1B0A, ISLAND_FLYOVER_IPOINT_GROUP_11, "Progressive Island Flyover I Point Group 11") \
    X(0x1B0B, ISLAND_FLYOVER_IPOINT_GROUP_12, "Progressive Island Flyover I Point Group 12") \
    X(0x0D00, GOLF_COMPLETE_HOLE_1, "Golf - Complete Hole 1!") \
    X(0x0D01, GOLF_COMPLETE_HOLE_2, "Golf - Complete Hole 2!") \
    X(0x0D02, GOLF_COMPLETE_HOLE_3, "Golf - Complete Hole 3!") \
    X(0x0D03, GOLF_COMPLETE_HOLE_4, "Golf - Complete Hole 4!") \
    X(0x0D04, GOLF_COMPLETE_HOLE_5, "Golf - Complete Hole 5!") \
    X(0x0D05, GOLF_COMPLETE_HOLE_6, "Golf - Complete Hole 6!") \
    X(0x0D06, GOLF_COMPLETE_HOLE_7, "Golf - Complete Hole 7!") \
    X(0x0D07, GOLF_COMPLETE_HOLE_8, "Golf - Complete Hole 8!") \
    X(0x0D08, GOLF_COMPLETE_HOLE_9, "Golf - Complete Hole 9!") \
    X(0x0D09, GOLF_COMPLETE_HOLE_10, "Golf - Complete Hole 10!") \
    X(0x0D0A, GOLF_COMPLETE_HOLE_11, "Golf - Complete Hole 11!") \
    X(0x0D0B, GOLF_COMPLETE_HOLE_12, "Golf - Complete Hole 12!") \
    X(0x0D0C, GOLF_COMPLETE_HOLE_13, "Golf - Complete Hole 13!") \
    X(0x0D0D, GOLF_COMPLETE_HOLE_14, "Golf - Complete Hole 14!") \
    X(0x0D0E, GOLF_COMPLETE_HOLE_15, "Golf - Complete Hole 15!") \
    X(0x0D0F, GOLF_COMPLETE_HOLE_16, "Golf - Complete Hole 16!") \
    X(0x0D10, GOLF_COMPLETE_HOLE_17, "Golf - Complete Hole 17!") \
    X(0x0D11, GOLF_COMPLETE_HOLE_18, "Golf - Complete Hole 18!") \
    X(0x0D12, GOLF_COMPLETE_HOLE_19, "Golf - Complete Hole 19!") \
    X(0x0D13, GOLF_COMPLETE_HOLE_20, "Golf - Complete Hole 20!") \
    X(0x0D14, GOLF_COMPLETE_HOLE_21, "Golf - Complete Hole 21!")

// clang-format on

#endif
