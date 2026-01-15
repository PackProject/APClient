#ifndef APCLIENT_CHECKS_H
#define APCLIENT_CHECKS_H
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
    X(0x0100, SWORDPLAY_SHOWDOWN_PRO_STATUS, "Swordplay Showdown - Pro Status") \
    X(0x0101, SWORDPLAY_SHOWDOWN_COMPLETE_STAGE_1, "Swordplay Showdown - Complete Stage 1") \
    X(0x0102, SWORDPLAY_SHOWDOWN_COMPLETE_STAGE_2, "Swordplay Showdown - Complete Stage 2") \
    X(0x0103, SWORDPLAY_SHOWDOWN_COMPLETE_STAGE_3, "Swordplay Showdown - Complete Stage 3") \
    X(0x0104, SWORDPLAY_SHOWDOWN_COMPLETE_STAGE_4, "Swordplay Showdown - Complete Stage 4") \
    X(0x0105, SWORDPLAY_SHOWDOWN_COMPLETE_STAGE_5, "Swordplay Showdown - Complete Stage 5") \
    X(0x0106, SWORDPLAY_SHOWDOWN_COMPLETE_STAGE_6, "Swordplay Showdown - Complete Stage 6") \
    X(0x0107, SWORDPLAY_SHOWDOWN_COMPLETE_STAGE_7, "Swordplay Showdown - Complete Stage 7") \
    X(0x0108, SWORDPLAY_SHOWDOWN_COMPLETE_STAGE_8, "Swordplay Showdown - Complete Stage 8") \
    X(0x0109, SWORDPLAY_SHOWDOWN_COMPLETE_STAGE_9, "Swordplay Showdown - Complete Stage 9") \
    X(0x010A, SWORDPLAY_SHOWDOWN_COMPLETE_STAGE_10, "Swordplay Showdown - Complete Stage 10") \
    X(0x010B, SWORDPLAY_SHOWDOWN_COMPLETE_STAGE_11, "Swordplay Showdown - Complete Stage 11") \
    X(0x010C, SWORDPLAY_SHOWDOWN_COMPLETE_STAGE_12, "Swordplay Showdown - Complete Stage 12") \
    X(0x010D, SWORDPLAY_SHOWDOWN_COMPLETE_STAGE_13, "Swordplay Showdown - Complete Stage 13") \
    X(0x010E, SWORDPLAY_SHOWDOWN_COMPLETE_STAGE_14, "Swordplay Showdown - Complete Stage 14") \
    X(0x010F, SWORDPLAY_SHOWDOWN_COMPLETE_STAGE_15, "Swordplay Showdown - Complete Stage 15") \
    X(0x0110, SWORDPLAY_SHOWDOWN_COMPLETE_STAGE_16, "Swordplay Showdown - Complete Stage 16") \
    X(0x0111, SWORDPLAY_SHOWDOWN_COMPLETE_STAGE_17, "Swordplay Showdown - Complete Stage 17") \
    X(0x0112, SWORDPLAY_SHOWDOWN_COMPLETE_STAGE_18, "Swordplay Showdown - Complete Stage 18") \
    X(0x0113, SWORDPLAY_SHOWDOWN_COMPLETE_STAGE_19, "Swordplay Showdown - Complete Stage 19") \
    X(0x0114, SWORDPLAY_SHOWDOWN_COMPLETE_STAGE_20, "Swordplay Showdown - Complete Stage 20") \
    X(0x0200, SWORDPLAY_DUEL_FIRST_WIN, "Swordplay Duel - First Win!") \
    X(0x0201, SWORDPLAY_DUEL_PRO_STATUS, "Swordplay Duel - Pro Status") \
    X(0x0202, SWORDPLAY_DUEL_BEAT_THE_CHAMPTION, "Swordplay Duel - Beat The Champion") \
    X(0x0300, SWORDPLAY_SPEED_SLICE_FIRST_WIN, "Swordplay Speed Slice - First Win!") \
    X(0x0301, SWORDPLAY_SPEED_SLICE_PRO_STATUS, "Swordplay Speed Slice - Pro Status") \
    X(0x0302, SWORDPLAY_SPEED_SLICE_BEAT_THE_CHAMPION, "Swordplay Speed Slice - Beat The Champion") \
    X(0x0400, POWER_CRUISING_PRO_STATUS, "Power Cruising - Pro Status") \
    X(0x0401, POWER_CRUISING_1500_POINTS, "Power Cruising - 1,500 Total Points") \
    X(0x0600, ARCHERY_PRO_STATUS, "Archery - Pro Status") \
    X(0x0700, FRISBEE_DOG_PRO_STATUS, "Frisbee Dog - Pro Status") \
    X(0x0800, BSK_3PT_PRO_STATUS, "Basketball 3-Point Contest - Pro Status") \
    X(0x0900, BSK_PICKUP_PRO_STATUS, "Basketball Pickup Game - Pro Status") \
    X(0x0901, BSK_PICKUP_BEAT_THE_CHAMPION, "Basketball Pickup Game - Beat The Champion") \
    X(0x0A00, BOWLING_STANDARD_PRO_STATUS, "Bowling Standard Game - Pro Status") \
    X(0x0A01, BOWLING_STANDARD_FIRST_STRIKE, "Bowling Standard Game - First Strike!") \
    X(0x0B00, BOWLING_100_PRO_STATUS, "Bowling 100-Pin - Pro Status") \
    X(0x0B01, BOWLING_100_FIRST_STRIKE, "Bowling 100-Pin - First Strike!") \
    X(0x0C00, BOWLING_SPIN_PRO_STATUS, "Bowling Spin Control - Pro Status") \
    X(0x0C01, BOWLING_SPIN_FIRST_STRIKE, "Bowling Spin Control - First Strike!") \
    X(0x0D01, CANOEING_PRO_CLASS, "Canoeing - Pro Status") \
    X(0x0E00, TABLE_TENNIS_RETURN_PRO_STATUS, "Table Tennis Return Challenge - Pro Status") \
    X(0x0F00, TABLE_TENNIS_MATCH_PRO_STATUS, "Table Tennis Match - Pro Status") \
    X(0x0F01, TABLE_TENNIS_MATCH_BEAT_THE_CHAMPION, "Table Tennis Match - Beat The Champion") \
    X(0x1000, WAKEBOARD_PRO_STATUS, "Wakeboarding - Pro Status") \
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
    X(0x1B0C, ISLAND_FLYOVER_IPOINT_GROUP_13, "Progressive Island Flyover I Point Group 13") \
    X(0x1B0D, ISLAND_FLYOVER_IPOINT_GROUP_14, "Progressive Island Flyover I Point Group 14") \
    X(0x1B0E, ISLAND_FLYOVER_IPOINT_GROUP_15, "Progressive Island Flyover I Point Group 15") \
    X(0x1B0F, ISLAND_FLYOVER_IPOINT_GROUP_16, "Progressive Island Flyover I Point Group 16") \
    X(0x1B10, ISLAND_FLYOVER_WHITE_BALLOON_GROUP_1, "Progressive Island Flyover White Balloon Group 1") \
    X(0x1B11, ISLAND_FLYOVER_WHITE_BALLOON_GROUP_2, "Progressive Island Flyover White Balloon Group 2") \
    X(0x1B12, ISLAND_FLYOVER_WHITE_BALLOON_GROUP_3, "Progressive Island Flyover White Balloon Group 3") \
    X(0x1B13, ISLAND_FLYOVER_WHITE_BALLOON_GROUP_4, "Progressive Island Flyover White Balloon Group 4") \
    X(0x1B14, ISLAND_FLYOVER_WHITE_BALLOON_GROUP_5, "Progressive Island Flyover White Balloon Group 5") \
    X(0x1B15, ISLAND_FLYOVER_WHITE_BALLOON_GROUP_6, "Progressive Island Flyover White Balloon Group 6") \
    X(0x1B16, ISLAND_FLYOVER_WHITE_BALLOON_GROUP_7, "Progressive Island Flyover White Balloon Group 7") \
    X(0x1B17, ISLAND_FLYOVER_WHITE_BALLOON_GROUP_8, "Progressive Island Flyover White Balloon Group 8") \
    X(0x1B18, ISLAND_FLYOVER_WHITE_BALLOON_GROUP_9, "Progressive Island Flyover White Balloon Group 9") \
    X(0x1B19, ISLAND_FLYOVER_WHITE_BALLOON_GROUP_10, "Progressive Island Flyover White Balloon Group 10") \
    X(0x1B1A, ISLAND_FLYOVER_WHITE_BALLOON_GROUP_11, "Progressive Island Flyover White Balloon Group 11") \
    X(0x1400, GOLF_COMPLETE_HOLE_1, "Golf - Complete Hole 1!") \
    X(0x1401, GOLF_COMPLETE_HOLE_2, "Golf - Complete Hole 2!") \
    X(0x1402, GOLF_COMPLETE_HOLE_3, "Golf - Complete Hole 3!") \
    X(0x1403, GOLF_COMPLETE_HOLE_4, "Golf - Complete Hole 4!") \
    X(0x1404, GOLF_COMPLETE_HOLE_5, "Golf - Complete Hole 5!") \
    X(0x1405, GOLF_COMPLETE_HOLE_6, "Golf - Complete Hole 6!") \
    X(0x1406, GOLF_COMPLETE_HOLE_7, "Golf - Complete Hole 7!") \
    X(0x1407, GOLF_COMPLETE_HOLE_8, "Golf - Complete Hole 8!") \
    X(0x1408, GOLF_COMPLETE_HOLE_9, "Golf - Complete Hole 9!") \
    X(0x1409, GOLF_COMPLETE_HOLE_10, "Golf - Complete Hole 10!") \
    X(0x140A, GOLF_COMPLETE_HOLE_11, "Golf - Complete Hole 11!") \
    X(0x140B, GOLF_COMPLETE_HOLE_12, "Golf - Complete Hole 12!") \
    X(0x140C, GOLF_COMPLETE_HOLE_13, "Golf - Complete Hole 13!") \
    X(0x140D, GOLF_COMPLETE_HOLE_14, "Golf - Complete Hole 14!") \
    X(0x140E, GOLF_COMPLETE_HOLE_15, "Golf - Complete Hole 15!") \
    X(0x140F, GOLF_COMPLETE_HOLE_16, "Golf - Complete Hole 16!") \
    X(0x1410, GOLF_COMPLETE_HOLE_17, "Golf - Complete Hole 17!") \
    X(0x1411, GOLF_COMPLETE_HOLE_18, "Golf - Complete Hole 18!") \
    X(0x1412, GOLF_COMPLETE_HOLE_19, "Golf - Complete Hole 19!") \
    X(0x1413, GOLF_COMPLETE_HOLE_20, "Golf - Complete Hole 20!") \
    X(0x1414, GOLF_COMPLETE_HOLE_21, "Golf - Complete Hole 21!") \
    X(0x1415, GOLF_PAR, "Golf - Get a par") \
    X(0x1416, GOLF_BIRDIE, "Golf - Get a birdie") \
    X(0x1417, GOLF_EAGLE, "Golf - Get an eagle!") \
    X(0x1418, GOLF_PRO_STATUS, "Golf - Pro Status") \
    X(0x1500, FRISBEE_GOLF_PRO_STATUS, "Frisbee Golf - Pro Status") \
    X(0x1501, FRISBEE_GOLF_COMPLETE_HOLE_1, "Frisbee Golf - Complete Hole 1") \
    X(0x1502, FRISBEE_GOLF_COMPLETE_HOLE_2, "Frisbee Golf - Complete Hole 2") \
    X(0x1503, FRISBEE_GOLF_COMPLETE_HOLE_3, "Frisbee Golf - Complete Hole 3") \
    X(0x1504, FRISBEE_GOLF_COMPLETE_HOLE_4, "Frisbee Golf - Complete Hole 4") \
    X(0x1505, FRISBEE_GOLF_COMPLETE_HOLE_5, "Frisbee Golf - Complete Hole 5") \
    X(0x1506, FRISBEE_GOLF_COMPLETE_HOLE_6, "Frisbee Golf - Complete Hole 6") \
    X(0x1507, FRISBEE_GOLF_COMPLETE_HOLE_7, "Frisbee Golf - Complete Hole 7") \
    X(0x1508, FRISBEE_GOLF_COMPLETE_HOLE_8, "Frisbee Golf - Complete Hole 8") \
    X(0x1509, FRISBEE_GOLF_COMPLETE_HOLE_9, "Frisbee Golf - Complete Hole 9") \
    X(0x150A, FRISBEE_GOLF_COMPLETE_HOLE_10, "Frisbee Golf - Complete Hole 10") \
    X(0x150B, FRISBEE_GOLF_COMPLETE_HOLE_11, "Frisbee Golf - Complete Hole 11") \
    X(0x150C, FRISBEE_GOLF_COMPLETE_HOLE_12, "Frisbee Golf - Complete Hole 12") \
    X(0x150D, FRISBEE_GOLF_COMPLETE_HOLE_13, "Frisbee Golf - Complete Hole 13") \
    X(0x150E, FRISBEE_GOLF_COMPLETE_HOLE_14, "Frisbee Golf - Complete Hole 14") \
    X(0x150F, FRISBEE_GOLF_COMPLETE_HOLE_15, "Frisbee Golf - Complete Hole 15") \
    X(0x1510, FRISBEE_GOLF_COMPLETE_HOLE_16, "Frisbee Golf - Complete Hole 16") \
    X(0x1511, FRISBEE_GOLF_COMPLETE_HOLE_17, "Frisbee Golf - Complete Hole 17") \
    X(0x1512, FRISBEE_GOLF_COMPLETE_HOLE_18, "Frisbee Golf - Complete Hole 18") \
    X(0x1513, FRISBEE_GOLF_COMPLETE_HOLE_19, "Frisbee Golf - Complete Hole 19") \
    X(0x1514, FRISBEE_GOLF_COMPLETE_HOLE_20, "Frisbee Golf - Complete Hole 20") \
    X(0x1515, FRISBEE_GOLF_COMPLETE_HOLE_21, "Frisbee Golf - Complete Hole 21") \
    X(0x1516, FRISBEE_GOLF_PAR, "Frisbee Golf - Get a par") \
    X(0x1517, FRISBEE_GOLF_BIRDIE, "Frisbee Golf - Get a birdie") \
    X(0x1518, FRISBEE_GOLF_EAGLE, "Frisbee Golf - Get an eagle!") \
    X(0x1700, CYCLING_PRO_STATUS, "Cycling - Pro Status") \
    X(0x1701, CYCLING_COMPLETE_STAGE_1, "Cycling - Complete Stage 1") \
    X(0x1702, CYCLING_COMPLETE_STAGE_2, "Cycling - Complete Stage 2") \
    X(0x1703, CYCLING_COMPLETE_STAGE_3, "Cycling - Complete Stage 3") \
    X(0x1704, CYCLING_COMPLETE_STAGE_4, "Cycling - Complete Stage 4") \
    X(0x1705, CYCLING_COMPLETE_STAGE_5, "Cycling - Complete Stage 5") \
    X(0x1706, CYCLING_COMPLETE_STAGE_6, "Cycling - Complete Stage 6") \
    X(0x1800, SKYDIVING_PRO_STATUS, "Skydiving - Pro Status")
    
// clang-format on

#endif
