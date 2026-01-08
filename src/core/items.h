#ifndef APCLIENT_CORE_ITEMS_H
#define APCLIENT_CORE_ITEMS_H
#include <types.h>

// clang-format off

// X-macro for all Archipelago items
// X(ID, Code name identifier, Readable name string)
#define AP_ITEMS_X_MACRO \
    X(0x0000, SWORDPLAY_DUEL_SPORT_UNLOCK, "Swordplay Duel Sport Unlock") \
    X(0x0001, SWORDPLAY_SPEED_SLICE_SPORT_UNLOCK, "Swordplay Speed Slice Sport Unlock") \
    X(0x0002, SWORDPLAY_SHOWDOWN_SPORT_UNLOCK, "Swordplay Showdown Sport Unlock") \
    X(0x0003, WAKEBOARDING_SPORT_UNLOCK, "Wakeboarding Sport Unlock") \
    X(0x0004, FRISBEE_DOG_SPORT_UNLOCK, "Frisbee Dog Sport Unlock") \
    X(0x0005, FRISBEE_GOLF_SPORT_UNLOCK, "Frisbee Golf Sport Unlock") \
    X(0x0006, ARCHERY_SPORT_UNLOCK, "Archery Sport Unlock") \
    X(0x0007, BASKETBALL_3POINT_CONTEST_SPORT_UNLOCK, "Basketball 3 Point Contest Sport Unlock") \
    X(0x0008, BASKETBALL_PICKUP_GAME_SPORT_UNLOCK, "Basketball Pickup Game Sport Unlock") \
    X(0x0009, TABLE_TENNIS_MATCH_SPORT_UNLOCK, "Table Tennis Match Sport Unlock") \
    X(0x000A, TABLE_TENNIS_RETURN_CHALLENGE_SPORT_UNLOCK, "Table Tennis Return Challenge Sport Unlock") \
    X(0x000B, GOLF_SPORT_UNLOCK, "Golf Sport Unlock") \
    X(0x000C, BOWLING_STANDARD_GAME_SPORT_UNLOCK, "Bowling Standard Game Sport Unlock") \
    X(0x000D, BOWLING_100_PIN_GAME_SPORT_UNLOCK, "Bowling 100 Pin Game Sport Unlock") \
    X(0x000E, BOWLING_SPIN_CONTROL_SPORT_UNLOCK, "Bowling Spin Control Sport Unlock") \
    X(0x000F, POWER_CRUISING_SPORT_UNLOCK, "Power Cruising Sport Unlock") \
    X(0x0010, CANOEING_SPEED_CHALLENGE_SPORT_UNLOCK, "Canoeing Speed Challenge Sport Unlock") \
    X(0x0011, CYCLING_SINGLE_RACE_UNLOCK, "Cycling Single Race Unlock") \
    X(0x0012, AIRSPORTS_SKYDIVING_UNLOCK, "Air Sports Skydiving Unlock") \
    X(0x0013, AIRSPORTS_ISLAND_FLYOVER_UNLOCK, "Air Sports Island Flyover Unlock") \
    X(0x0014, SWORDPLAY_CATEGORY_UNLOCK, "Swordplay Category Unlock") \
    X(0x0015, WAKEBOARD_CATEGORY_UNLOCK, "Wakeboard Category Unlock") \
    X(0x0016, FRISBEE_CATEGORY_UNLOCK, "Frisbee Category Unlock") \
    X(0x0017, ARCHERY_CATEGORY_UNLOCK, "Archery Category Unlock") \
    X(0x0018, BASKETBALL_CATEGORY_UNLOCK, "Basketball Category Unlock") \
    X(0x0019, TABLE_TENNIS_CATEGORY_UNLOCK, "Table Tennis Category Unlock") \
    X(0x001A, GOLF_CATEGORY_UNLOCK, "Golf Category Unlock") \
    X(0x001B, BOWLING_CATEGORY_UNLOCK, "Bowling Category Unlock") \
    X(0x001C, POWER_CRUISING_CATEGORY_UNLOCK, "Power Cruising Category Unlock") \
    X(0x001D, CANOEING_CATEGORY_UNLOCK, "Canoeing Category Unlock") \
    X(0x001E, CYCLING_CATEGORY_UNLOCK, "Cycling Category Unlock") \
    X(0x001F, AIRSPORTS_CATEGORY_UNLOCK, "Air Sports Category Unlock") \
    X(0x0100, SWORDPLAY_DUEL_BLOCK, "Swordplay Duel Block") \
    X(0x0200, SWORDPLAY_SPEED_SLICE_PAUSE, "Swordplay Speed Slice Pause") \
    X(0x0300, SWORDPLAY_SHOWDOWN_BLOCK, "Swordplay Showdown Block") \
    X(0x0301, SWORDPLAY_SHOWDOWN_HEART, "Swordplay Showdown Heart") \
    X(0x0302, SWORDPLAY_SHOWDOWN_STAGE_1, "Swordplay Showdown Stage 1") \
    X(0x0303, SWORDPLAY_SHOWDOWN_STAGE_2, "Swordplay Showdown Stage 2") \
    X(0x0304, SWORDPLAY_SHOWDOWN_STAGE_3, "Swordplay Showdown Stage 3") \
    X(0x0305, SWORDPLAY_SHOWDOWN_STAGE_4, "Swordplay Showdown Stage 4") \
    X(0x0306, SWORDPLAY_SHOWDOWN_STAGE_5, "Swordplay Showdown Stage 5") \
    X(0x0307, SWORDPLAY_SHOWDOWN_STAGE_6, "Swordplay Showdown Stage 6") \
    X(0x0308, SWORDPLAY_SHOWDOWN_STAGE_7, "Swordplay Showdown Stage 7") \
    X(0x0309, SWORDPLAY_SHOWDOWN_STAGE_8, "Swordplay Showdown Stage 8") \
    X(0x030A, SWORDPLAY_SHOWDOWN_STAGE_9, "Swordplay Showdown Stage 9") \
    X(0x030B, SWORDPLAY_SHOWDOWN_STAGE_10, "Swordplay Showdown Stage 10") \
    X(0x030C, SWORDPLAY_SHOWDOWN_STAGE_11, "Swordplay Showdown Stage 11") \
    X(0x030D, SWORDPLAY_SHOWDOWN_STAGE_12, "Swordplay Showdown Stage 12") \
    X(0x030E, SWORDPLAY_SHOWDOWN_STAGE_13, "Swordplay Showdown Stage 13") \
    X(0x030F, SWORDPLAY_SHOWDOWN_STAGE_14, "Swordplay Showdown Stage 14") \
    X(0x0310, SWORDPLAY_SHOWDOWN_STAGE_15, "Swordplay Showdown Stage 15") \
    X(0x0311, SWORDPLAY_SHOWDOWN_STAGE_16, "Swordplay Showdown Stage 16") \
    X(0x0312, SWORDPLAY_SHOWDOWN_STAGE_17, "Swordplay Showdown Stage 17") \
    X(0x0313, SWORDPLAY_SHOWDOWN_STAGE_18, "Swordplay Showdown Stage 18") \
    X(0x0314, SWORDPLAY_SHOWDOWN_STAGE_19, "Swordplay Showdown Stage 19") \
    X(0x0315, SWORDPLAY_SHOWDOWN_STAGE_20, "Swordplay Showdown Stage 20") \
    X(0x0400, WAKEBOARDING_TIMER, "Wakeboarding Timer") \
    X(0x0401, WAKEBOARDING_BEGINNER, "Wakeboarding Beginner") \
    X(0x0402, WAKEBOARDING_INTERMEDIATE, "Wakeboarding Intermediate") \
    X(0x0403, WAKEBOARDING_EXPERT, "Wakeboarding Expert") \
    X(0x0500, FRISBEE_DOG_FRISBEES, "Frisbee Dog Frisbees") \
    X(0x0501, FRISBEE_DOG_SECRET_POP, "Frisbee Dog Secret Pop") \
    X(0x0600, FRISBEE_GOLF_HUD, "Frisbee Golf Hud") \
    X(0x0601, FRISBEE_GOLF_DRIVER, "Frisbee Golf Driver") \
    X(0x0602, FRISBEE_GOLF_MIDRANGE, "Frisbee Golf Midrange") \
    X(0x0603, FRISBEE_GOLF_PUTTER, "Frisbee Golf Putter") \
    X(0x0604, FRISBEE_GOLF_COURSE_0, "Frisbee Golf Course 0") \
    X(0x0605, FRISBEE_GOLF_COURSE_1, "Frisbee Golf Course 1") \
    X(0x0606, FRISBEE_GOLF_COURSE_2, "Frisbee Golf Course 2") \
    X(0x0607, FRISBEE_GOLF_COURSE_3, "Frisbee Golf Course 3") \
    X(0x0608, FRISBEE_GOLF_COURSE_4, "Frisbee Golf Course 4") \
    X(0x0609, FRISBEE_GOLF_COURSE_5, "Frisbee Golf Course 5") \
    X(0x060A, FRISBEE_GOLF_COURSE_6, "Frisbee Golf Course 6") \
    X(0x060B, FRISBEE_GOLF_COURSE_7, "Frisbee Golf Course 7") \
    X(0x060C, FRISBEE_GOLF_COURSE_8, "Frisbee Golf Course 8") \
    X(0x060D, FRISBEE_GOLF_COURSE_9, "Frisbee Golf Course 9") \
    X(0x0700, ARCHERY_AIM_CIRCLE, "Archery Aim Circle") \
    X(0x0701, ARCHERY_ARROW, "Archery Arrow") \
    X(0x702, ARCHERY_FRUIT_BEGINNER, "Archery Fruit Beginner") \
    X(0x703, ARCHERY_FRUIT_INTERMEDIATE, "Archery Fruit Intermediate") \
    X(0x704, ARCHERY_FRUIT_EXPERT, "Archery Fruit Expert") \
    X(0x705, ARCHERY_BEGINNER, "Archery Beginner") \
    X(0x706, ARCHERY_INTERMEDIATE, "Archery Intermediate") \
    X(0x707, ARCHERY_EXPERT, "Archery Expert") \
    X(0x0800, BASKETBALL_3PT_TIMER, "Basketball 3PT Timer") \
    X(0x0801, BASKETBALL_BONUS_BALLS, "Basketball Bonus Balls") \
    X(0x0900, BASKETBALL_PICKUP_TIMER, "Basketball Pickup Timer") \
    X(0x0901, BASKETBALL_PASS, "Basketball Pass") \
    X(0x0902, BASKETBALL_3PTS, "Basketball 3PTS") \
    X(0x0903, BASKETBALL_DUNK, "Basketball Dunk") \
    X(0x0A00, TABLE_TENNIS_SPIN, "Table Tennis Spin") \
    X(0x0A01, TABLE_TENNIS_SMASH, "Table Tennis Smash") \
    X(0x0A02, TABLE_TENNIS_CANS, "Table Tennis Cans") \
    X(0x0B00, GOLF_HUD, "Golf Hud") \
    X(0x0B01, GOLF_DRIVER, "Golf Driver") \
    X(0x0B02, GOLF_3_WOOD, "Golf 3 Wood") \
    X(0x0B03, GOLF_3_IRON, "Golf 3 Iron") \
    X(0x0B04, GOLF_5_IRON, "Golf 5 Iron") \
    X(0x0B05, GOLF_7_IRON, "Golf 7 Iron") \
    X(0x0B06, GOLF_9_IRON, "Golf 9 Iron") \
    X(0x0B07, GOLF_WEDGE, "Golf Wedge") \
    X(0x0B08, GOLF_PUTTER, "Golf Putter") \
    X(0x0B09, GOLF_TURN, "Golf Turn") \
    X(0x0B0A, GOLF_BACKSPIN, "Golf Backspin") \
    X(0x0B0B, GOLF_COURSE_0, "Golf Course 0") \
    X(0x0B0C, GOLF_COURSE_1, "Golf Course 1") \
    X(0x0B0D, GOLF_COURSE_2, "Golf Course 2") \
    X(0x0B0E, GOLF_COURSE_3, "Golf Course 3") \
    X(0x0B0F, GOLF_COURSE_4, "Golf Course 4") \
    X(0x0B10, GOLF_COURSE_5, "Golf Course 5") \
    X(0x0B11, GOLF_COURSE_6, "Golf Course 6") \
    X(0x0B12, GOLF_COURSE_7, "Golf Course 7") \
    X(0x0B13, GOLF_COURSE_8, "Golf Course 8") \
    X(0x0B14, GOLF_COURSE_9, "Golf Course 9") \
    X(0x0B15, GOLF_VIEW_LOW, "Golf View Low") \
    X(0x0B16, GOLF_VIEW_SLOPE, "Golf View Slope") \
    X(0x0C00, BOWLING_10_PIN_MOVE, "Bowling 10 Pin Move") \
    X(0x0C01, BOWLING_10_PIN_TURN, "Bowling 10 Pin Turn") \
    X(0x0C02, BOWLING_10_PIN_SPIN, "Bowling 10 Pin Spin") \
    X(0x0D00, BOWLING_100_PIN_MOVE, "Bowling 100 Pin Move") \
    X(0x0D01, BOWLING_100_PIN_TURN, "Bowling 100 Pin Turn") \
    X(0x0D02, BOWLING_100_PIN_SPIN, "Bowling 100 Pin Spin") \
    X(0x0D03, BOWLING_100_PIN_SECRET_STRIKE, "Bowling 100 Pin Secret Strike") \
    X(0x0E00, BOWLING_SPIN_CONTROL_MOVE, "Bowling Spin Control Move") \
    X(0x0E01, BOWLING_SPIN_CONTROL_TURN, "Bowling Spin Control Turn") \
    X(0x0E02, BOWLING_SPIN_CONTROL_SPIN, "Bowling Spin Control Spin") \
    X(0x0F00, POWER_CRUISING_BOOST, "Power Cruising Boost") \
    X(0x0F01, POWER_CRUISING_RING_TIMER, "Power Cruising Ring Timer") \
    X(0x0F02, POWER_CRUISING_DOUBLE_RING, "Power Cruising Double Ring") \
    X(0x0F03, POWER_CRUISING_FREE_CRUISING_TIMER, "Power Cruising Free Cruising Timer") \
    X(0x1000, CANOEING_TIMER, "Canoeing Timer") \
    X(0x1001, CANOEING_BEGINNER, "Canoeing Beginner") \
    X(0x1002, CANOEING_INTERMEDIATE, "Canoeing Intermediate") \
    X(0x1003, CANOEING_EXPERT, "Canoeing Expert") \
    X(0x1100, CYCLING_HEART, "Cycling Heart") \
    X(0x1101, CYCLING_STAGE_0, "Cycling Stage 0") \
    X(0x1102, CYCLING_STAGE_1, "Cycling Stage 1") \
    X(0x1103, CYCLING_STAGE_2, "Cycling Stage 2") \
    X(0x1104, CYCLING_STAGE_3, "Cycling Stage 3") \
    X(0x1105, CYCLING_STAGE_4, "Cycling Stage 4") \
    X(0x1106, CYCLING_STAGE_5, "Cycling Stage 5") \
    X(0x1107, CYCLING_STAGE_6, "Cycling Stage 6") \
    X(0x1108, CYCLING_STAGE_7, "Cycling Stage 7") \
    X(0x1200, SKYDIVING_MII, "Skydiving Mii") \
    X(0x1300, ISLAND_FLYOVER_TIMER, "Island Flyover Timer") \
    X(0x1301, ISLAND_FLYOVER_DAY, "Island Flyover Day") \
    X(0x1302, ISLAND_FLYOVER_EVENING, "Island Flyover Evening") \
    X(0x1303, ISLAND_FLYOVER_NIGHT, "Island Flyover Night") \
    X(0x1304, ISLAND_FLYOVER_DOUBLE_BLASTERS, "Island Flyover Double Blasters") \
    X(0x1305, ISLAND_FLYOVER_NIGHT_LIGHTS, "Island Flyover Night Lights") \
    X(0x1306, ISLAND_FLYOVER_UNLOCK_BALLOONS, "Island Flyover Unlock Balloons") \
    X(0x1307, ISLAND_FLYOVER_UNLOCK_TWO_SEATER, "Island Flyover Unlock Two Seater") \
    X(0x1308, ISLAND_FLYOVER_UNLOCK_BOOST, "Island Flyover Unlock Boosting") \
    X(0x1309, ISLAND_FLYOVER_UNLOCK_BRAKE, "Island Flyover Unlock Braking")

// clang-format on

#endif
