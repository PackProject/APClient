#ifndef APCLIENT_CORE_ITEMS_H
#define APCLIENT_CORE_ITEMS_H
#include <types.h>

// clang-format off

// X-macro for all Archipelago items
// X(ID, Code name identifier, Readable name string)
#define AP_ITEMS_X_MACRO \
    X(0x0000, SWORDPLAY_DUEL_SPORT_UNLOCK, "Unlock Swordplay - Duel") \
    X(0x0001, SWORDPLAY_SPEED_SLICE_SPORT_UNLOCK, "Unlock Swordplay - Speed Slice") \
    X(0x0002, SWORDPLAY_SHOWDOWN_SPORT_UNLOCK, "Unlock Swordplay - Showdown") \
    X(0x0003, WAKEBOARDING_SPORT_UNLOCK, "Unlock Wakeboarding") \
    X(0x0004, FRISBEE_DOG_SPORT_UNLOCK, "Unlock Frisbee - Frisbee Dog") \
    X(0x0005, FRISBEE_GOLF_SPORT_UNLOCK, "Unlock Frisbee - Frisbee Golf") \
    X(0x0006, ARCHERY_SPORT_UNLOCK, "Unlock Archery") \
    X(0x0007, BASKETBALL_3POINT_CONTEST_SPORT_UNLOCK, "Unlock Basketball - 3 Point Contest") \
    X(0x0008, BASKETBALL_PICKUP_GAME_SPORT_UNLOCK, "Unlock Basketball - Pickup Game") \
    X(0x0009, TABLE_TENNIS_MATCH_SPORT_UNLOCK, "Unlock Table Tennis - Match") \
    X(0x000A, TABLE_TENNIS_RETURN_CHALLENGE_SPORT_UNLOCK, "Unlock Table Tennis - Return Challenge") \
    X(0x000B, GOLF_SPORT_UNLOCK, "Unlock Golf") \
    X(0x000C, BOWLING_STANDARD_GAME_SPORT_UNLOCK, "Unlock Bowling - 10 Pin Game") \
    X(0x000D, BOWLING_100_PIN_GAME_SPORT_UNLOCK, "Unlock Bowling - 100 Pin Game") \
    X(0x000E, BOWLING_SPIN_CONTROL_SPORT_UNLOCK, "Unlock Bowling - Spin Control") \
    X(0x000F, POWER_CRUISING_SPORT_UNLOCK, "Unlock Power Cruising") \
    X(0x0010, CANOEING_SPEED_CHALLENGE_SPORT_UNLOCK, "Unlock Canoeing") \
    X(0x0011, CYCLING_SINGLE_RACE_UNLOCK, "Unlock Cycling") \
    X(0x0012, AIRSPORTS_SKYDIVING_UNLOCK, "Unlock Air Sports - Skydiving") \
    X(0x0013, AIRSPORTS_ISLAND_FLYOVER_UNLOCK, "Unlock Air Sports - Island Flyover") \
    X(0x0014, SWORDPLAY_CATEGORY_UNLOCK, "Unlock Swordplay") \
    X(0x0015, WAKEBOARD_CATEGORY_UNLOCK, "Unlock Wakeboarding") \
    X(0x0016, FRISBEE_CATEGORY_UNLOCK, "Unlock Frisbee") \
    X(0x0017, ARCHERY_CATEGORY_UNLOCK, "Unlock Archery") \
    X(0x0018, BASKETBALL_CATEGORY_UNLOCK, "Unlock Basketball") \
    X(0x0019, TABLE_TENNIS_CATEGORY_UNLOCK, "Unlock Table Tennis") \
    X(0x001A, GOLF_CATEGORY_UNLOCK, "Unlock Golf") \
    X(0x001B, BOWLING_CATEGORY_UNLOCK, "Unlock Bowling") \
    X(0x001C, POWER_CRUISING_CATEGORY_UNLOCK, "Unlock Power Cruising") \
    X(0x001D, CANOEING_CATEGORY_UNLOCK, "Unlock Canoeing") \
    X(0x001E, CYCLING_CATEGORY_UNLOCK, "Unlock Cycling") \
    X(0x001F, AIRSPORTS_CATEGORY_UNLOCK, "Unlock Air Sports") \
    X(0x0100, SWORDPLAY_DUEL_BLOCK, "Swordplay Duel - Blocking") \
    X(0x0200, SWORDPLAY_SPEED_SLICE_PAUSE, "Swordplay Speed Slice - Pausing") \
    X(0x0300, SWORDPLAY_SHOWDOWN_BLOCK, "Swordplay Showdown - Blocking") \
    X(0x0301, SWORDPLAY_SHOWDOWN_HEART, "Swordplay - Progressive Heart") \
    X(0x0302, SWORDPLAY_SHOWDOWN_STAGE_1, "Unlock Swordplay Showdown - Bridge") \
    X(0x0303, SWORDPLAY_SHOWDOWN_STAGE_2, "Unlock Swordplay Showdown - Lighthouse") \
    X(0x0304, SWORDPLAY_SHOWDOWN_STAGE_3, "Unlock Swordplay Showdown - Beach") \
    X(0x0305, SWORDPLAY_SHOWDOWN_STAGE_4, "Unlock Swordplay Showdown - Mountain") \
    X(0x0306, SWORDPLAY_SHOWDOWN_STAGE_5, "Unlock Swordplay Showdown - Forest") \
    X(0x0307, SWORDPLAY_SHOWDOWN_STAGE_6, "Unlock Swordplay Showdown - Ruins") \
    X(0x0308, SWORDPLAY_SHOWDOWN_STAGE_7, "Unlock Swordplay Showdown - Waterfall") \
    X(0x0309, SWORDPLAY_SHOWDOWN_STAGE_8, "Unlock Swordplay Showdown - Cliffs") \
    X(0x030A, SWORDPLAY_SHOWDOWN_STAGE_9, "Unlock Swordplay Showdown - Castle") \
    X(0x030B, SWORDPLAY_SHOWDOWN_STAGE_10, "Unlock Swordplay Showdown - Volcano") \
    X(0x030C, SWORDPLAY_SHOWDOWN_STAGE_11, "Unlock Swordplay Showdown - Bridge Reverse") \
    X(0x030D, SWORDPLAY_SHOWDOWN_STAGE_12, "Unlock Swordplay Showdown - Lighthouse Reverse") \
    X(0x030E, SWORDPLAY_SHOWDOWN_STAGE_13, "Unlock Swordplay Showdown - Beach Reverse") \
    X(0x030F, SWORDPLAY_SHOWDOWN_STAGE_14, "Unlock Swordplay Showdown - Mountain Reverse") \
    X(0x0310, SWORDPLAY_SHOWDOWN_STAGE_15, "Unlock Swordplay Showdown - Forest Reverse") \
    X(0x0311, SWORDPLAY_SHOWDOWN_STAGE_16, "Unlock Swordplay Showdown - Ruins Reverse") \
    X(0x0312, SWORDPLAY_SHOWDOWN_STAGE_17, "Unlock Swordplay Showdown - Waterfall Reverse") \
    X(0x0313, SWORDPLAY_SHOWDOWN_STAGE_18, "Unlock Swordplay Showdown - Cliffs Reverse") \
    X(0x0314, SWORDPLAY_SHOWDOWN_STAGE_19, "Unlock Swordplay Showdown - Castle Reverse") \
    X(0x0315, SWORDPLAY_SHOWDOWN_STAGE_20, "Unlock Swordplay Showdown - Volcano Reverse") \
    X(0x0400, WAKEBOARDING_TIMER, "Wakeboarding Timer") \
    X(0x0401, WAKEBOARDING_BEGINNER, "Unlock Wakeboarding - Beginner") \
    X(0x0402, WAKEBOARDING_INTERMEDIATE, "Unlock Wakeboarding - Intermediate") \
    X(0x0403, WAKEBOARDING_EXPERT, "Unlock Wakeboarding - Expert") \
    X(0x0500, FRISBEE_DOG_PROG_FRISBEES, "Progressive Frisbee (Frisbee Dog)") \
    X(0x0501, FRISBEE_DOG_PUTTER, "Frisbee Dog - Putter Frisbee") \
    X(0x0502, FRISBEE_DOG_MIDRANGE, "Frisbee Dog - Midrange Frisbee") \
    X(0x0503, FRISBEE_DOG_DRIVER, "Frisbee Dog - Driver Frisbee") \
    X(0x0504, FRISBEE_DOG_SECRET_POP, "Frisbee Dog - A+2 Balloon Pop") \
    X(0x0600, FRISBEE_GOLF_HUD, "Frisbee Golf - HUD") \
    X(0x0601, FRISBEE_GOLF_PROG_FRISBEE, "Progressive Frisbee (Frisbee Golf)") \
    X(0x0602, FRISBEE_GOLF_DRIVER, "Frisbee Golf - Driver") \
    X(0x0603, FRISBEE_GOLF_MIDRANGE, "Frisbee Golf - Midrange") \
    X(0x0604, FRISBEE_GOLF_PUTTER, "Frisbee Golf - Putter") \
    X(0x0605, FRISBEE_GOLF_COURSE_0, "Unlock Frisbee Golf - Resort A") \
    X(0x0606, FRISBEE_GOLF_COURSE_1, "Unlock Frisbee Golf - Resort B") \
    X(0x0607, FRISBEE_GOLF_COURSE_2, "Unlock Frisbee Golf - Resort C") \
    X(0x0608, FRISBEE_GOLF_COURSE_3, "Unlock Frisbee Golf - Classic A") \
    X(0x0609, FRISBEE_GOLF_COURSE_4, "Unlock Frisbee Golf - Classic B") \
    X(0x060A, FRISBEE_GOLF_COURSE_5, "Unlock Frisbee Golf - Classic C") \
    X(0x060B, FRISBEE_GOLF_COURSE_6, "Unlock Frisbee Golf - Special") \
    X(0x060C, FRISBEE_GOLF_COURSE_7, "Unlock Frisbee Golf - Resort 9") \
    X(0x060D, FRISBEE_GOLF_COURSE_8, "Unlock Frisbee Golf - Classic 9") \
    X(0x060E, FRISBEE_GOLF_COURSE_9, "Unlock Frisbee Golf - 18 Hole") \
    X(0x0700, ARCHERY_AIM_CIRCLE, "Archery - Aiming Circle") \
    X(0x0701, ARCHERY_ARROW, "Progressive Arrow (Archery)") \
    X(0x0702, ARCHERY_FRUIT_PROG, "Progressive Fruit (Archery)") \
    X(0x0702, ARCHERY_FRUIT_BEGINNER, "Archery Fruit Beginner") \
    X(0x0703, ARCHERY_FRUIT_INTERMEDIATE, "Archery Fruit Intermediate") \
    X(0x0704, ARCHERY_FRUIT_EXPERT, "Archery Fruit Expert") \
    X(0x0705, ARCHERY_BEGINNER, "Unlock Archery - Beginner") \
    X(0x0706, ARCHERY_INTERMEDIATE, "Unlock Archery - Intermediate") \
    X(0x0707, ARCHERY_EXPERT, "Unlock Archery - Expert") \
    X(0x0800, BASKETBALL_3PT_TIMER, "Basketball (3-Point Contest) Timer") \
    X(0x0801, BASKETBALL_BONUS_BALLS, "Basketball (3-Point Contest) - Golden Balls") \
    X(0x0900, BASKETBALL_PICKUP_TIMER, "Basketball (Pickup) Timer") \
    X(0x0901, BASKETBALL_PASS, "Basketball Pickup Game - Passing") \
    X(0x0902, BASKETBALL_3PTS, "Basketball Pickup Game - 3-Pointers") \
    X(0x0903, BASKETBALL_DUNK, "Basketball Pickup Game - Dunk") \
    X(0x0A00, TABLE_TENNIS_SPIN, "Table Tennis - Spin") \
    X(0x0A01, TABLE_TENNIS_SMASH, "Table Tennis - Smash Hit") \
    X(0x0A02, TABLE_TENNIS_CANS, "Table Tennis (Return Challenge) - Cans") \
    X(0x0B00, GOLF_HUD, "Golf - HUD") \
    X(0x0B01, GOLF_PROG_CLUB, "Progressive Club (Golf)") \
    X(0x0B02, GOLF_DRIVER, "Golf - Driver") \
    X(0x0B03, GOLF_3_WOOD, "Golf - 3 Wood") \
    X(0x0B04, GOLF_3_IRON, "Golf - 3 Iron") \
    X(0x0B05, GOLF_5_IRON, "Golf - 5 Iron") \
    X(0x0B06, GOLF_7_IRON, "Golf - 7 Iron") \
    X(0x0B07, GOLF_9_IRON, "Golf - 9 Iron") \
    X(0x0B08, GOLF_WEDGE, "Golf - Wedge") \
    X(0x0B09, GOLF_PUTTER, "Golf - Putter") \
    X(0x0B0A, GOLF_TURN, "Golf - Turn") \
    X(0x0B0B, GOLF_BACKSPIN, "Golf - Backspin") \
    X(0x0B0C, GOLF_COURSE_0, "Unlock Golf - Resort A") \
    X(0x0B0D, GOLF_COURSE_1, "Unlock Golf - Resort B") \
    X(0x0B0E, GOLF_COURSE_2, "Unlock Golf - Resort C") \
    X(0x0B0F, GOLF_COURSE_3, "Unlock Golf - Classic A") \
    X(0x0B10, GOLF_COURSE_4, "Unlock Golf - Classic B") \
    X(0x0B11, GOLF_COURSE_5, "Unlock Golf - Classic C") \
    X(0x0B12, GOLF_COURSE_6, "Unlock Golf - Special") \
    X(0x0B13, GOLF_COURSE_7, "Unlock Golf - Resort 9") \
    X(0x0B14, GOLF_COURSE_8, "Unlock Golf - Classic 9") \
    X(0x0B15, GOLF_COURSE_9, "Unlock Golf - 18 Hole") \
    X(0x0B16, GOLF_VIEW_LOW, "Golf - Green Low View") \
    X(0x0B17, GOLF_VIEW_SLOPE, "Golf - Green Slope View") \
    X(0x0C00, BOWLING_10_PIN_MOVE, "Bowling (Standard) - Moving") \
    X(0x0C01, BOWLING_10_PIN_TURN, "Bowling (Standard) - Turning") \
    X(0x0C02, BOWLING_10_PIN_SPIN, "Bowling (Standard) - Spin") \
    X(0x0D00, BOWLING_100_PIN_MOVE, "Bowling (100 Pin) - Moving") \
    X(0x0D01, BOWLING_100_PIN_TURN, "Bowling (100 Pin) - Turning") \
    X(0x0D02, BOWLING_100_PIN_SPIN, "Bowling (100 Pin) - Spin") \
    X(0x0D03, BOWLING_100_PIN_SECRET_STRIKE, "Bowling 100 Pin Secret Strike") \
    X(0x0E00, BOWLING_SPIN_CONTROL_MOVE, "Bowling (Spin Control) - Moving") \
    X(0x0E01, BOWLING_SPIN_CONTROL_TURN, "Bowling (Spin Control) - Turning") \
    X(0x0E02, BOWLING_SPIN_CONTROL_SPIN, "Bowling (Spin Control) - Spin") \
    X(0x0F00, POWER_CRUISING_BOOST, "Power Cruising - Boost") \
    X(0x0F01, POWER_CRUISING_RING_TIMER, "Power Cruising - Progressive Ring Timer") \
    X(0x0F02, POWER_CRUISING_DOUBLE_RING, "Power Cruising - Double Ring") \
    X(0x0F03, POWER_CRUISING_FREE_CRUISING_TIMER, "Power Cruising - Free Cruising Timer") \
    X(0x0F04, POWER_CRUISING_BEACH, "Unlock Power Cruising - Beach") \
    X(0x0F05, POWER_CRUISING_LAGOON, "Unlock Power Cruising - Lagoon") \
    X(0x0F06, POWER_CRUISING_LIGHTHOUSE, "Unlock Power Cruising - Lighthouse") \
    X(0x0F07, POWER_CRUISING_MARINA, "Unlock Power Cruising - Marina") \
    X(0x0F08, POWER_CRUISING_CAVERN, "Unlock Power Cruising - Cavern") \
    X(0x0F09, POWER_CRUISING_SHOALS, "Unlock Power Cruising - Shoals") \
    X(0x1000, CANOEING_TIMER, "Canoeing Timer") \
    X(0x1001, CANOEING_BEGINNER, "Canoeing Beginner") \
    X(0x1002, CANOEING_INTERMEDIATE, "Canoeing Intermediate") \
    X(0x1003, CANOEING_EXPERT, "Canoeing Expert") \
    X(0x1100, CYCLING_HEART, "Cycling - Progressive Heart") \
    X(0x1101, CYCLING_STAGE_0, "Unlock Cycling - Around The Island") \
    X(0x1102, CYCLING_STAGE_1, "Unlock Cycling - To The Beach") \
    X(0x1103, CYCLING_STAGE_2, "Unlock Cycling - Across The Bridge") \
    X(0x1104, CYCLING_STAGE_3, "Unlock Cycling - Over Talon Rock") \
    X(0x1105, CYCLING_STAGE_4, "Unlock Cycling - Up The Volcano") \
    X(0x1106, CYCLING_STAGE_5, "Unlock Cycling - Into Maka Wuhu") \
    X(0x1107, CYCLING_STAGE_6, "Unlock Cycling - 3-Stage Race A") \
    X(0x1108, CYCLING_STAGE_7, "Unlock Cycling - 3-Stage Race B") \
    X(0x1108, CYCLING_STAGE_8, "Unlock Cycling - 6 Stage") \
    X(0x1109, CYCLING_DRAFT, "Cycling - Drafting") \
    X(0x1200, SKYDIVING_MII, "Skydiving - Mii") \
    X(0x1300, ISLAND_FLYOVER_TIMER, "Island Flyover Timer") \
    X(0x1301, ISLAND_FLYOVER_DAY, "Unlock Island Flyover - Daytime") \
    X(0x1302, ISLAND_FLYOVER_EVENING, "Unlock Island Flyover - Evening") \
    X(0x1303, ISLAND_FLYOVER_NIGHT, "Unlock Island Flyover - Night") \
    X(0x1304, ISLAND_FLYOVER_DOUBLE_BLASTERS, "Island Flyover - Double Blasters") \
    X(0x1305, ISLAND_FLYOVER_NIGHT_LIGHTS, "Island Flyover - Night Lights") \
    X(0x1306, ISLAND_FLYOVER_UNLOCK_BALLOONS, "Island Flyover - Unlock Balloons") \
    X(0x1307, ISLAND_FLYOVER_UNLOCK_TWO_SEATER, "Island Flyover - Unlock Two Seater") \
    X(0x1308, ISLAND_FLYOVER_UNLOCK_BOOST, "Island Flyover - Unlock Boosting") \
    X(0x1309, ISLAND_FLYOVER_UNLOCK_BRAKE, "Island Flyover - Unlock Braking") \
    X(0xFF00, ISLAND_FLYOVER_XP_DUEL, "100 Skill Points (Swordplay Duel)") \
    X(0xFF01, XP_SPEED_SLICE, "100 Skill Points (Swordplay Speed Slice)") \
    X(0xFF02, XP_SHOWDOWN, "100 Skill Points (Swordplay Showdown)") \
    X(0xFF03, XP_WAKEBOARDING, "100 Skill Points (Wakeboarding)") \
    X(0xFF04, XP_FRISBEE_DOG, "100 Skill Points (Frisbee Dog)") \
    X(0xFF05, XP_FRISBEE_GOLF, "100 Skill Points (Frisbee Golf)") \
    X(0xFF06, XP_ARCHERY, "100 Skill Points (Archery)") \
    X(0xFF07, XP_3PC, "100 Skill Points (Basketball - 3 Point Contest)") \
    X(0xFF08, XP_PICKUP_GAME, "100 Skill Points (Basketball - Pickup Game)") \
    X(0xFF09, XP_RETURN_CHALLENGE, "100 Skill Points (Table Tennis - Return Challenge)") \
    X(0xFF0A, XP_MATCH, "100 Skill Points (Table Tennis - Match)") \
    X(0xFF0B, XP_GOLF, "100 Skill Points (Golf)") \
    X(0xFF0C, XP_BOWLING_STD, "100 Skill Points (Bowling - 10-pin Game)") \
    X(0xFF0D, XP_BOWLING_HUNDRED, "100 Skill Points (Bowling - 100-pin Game)") \
    X(0xFF0E, XP_BOWLING_SPIN_CONTROL, "100 Skill Points (Bowling - Spin Control)") \
    X(0xFF0F, XP_POWER_CRUISING, "100 Skill Points (Power Cruising)") \
    X(0xFF10, XP_CANOEING, "100 Skill Points (Canoeing)") \
    X(0xFF11, XP_CYCLING, "100 Skill Points (Cycling)") \
    X(0xFF12, XP_SKYDIVING, "100 Skill Points (Air Sports - Skydiving)") \
    X(0xFF13, SWORDPLAY_SHOWDOWN_EXTRA_HEART, "Extra Max Heart (Swordplay Showdown)") \
    X(0xFF14, CYCLING_EXTRA_HEART, "Extra Max Heart (Cycling)") \
    X(0xFF15, RANDOM_COSMETIC, "Random Cosmetic")

// clang-format on

#endif
