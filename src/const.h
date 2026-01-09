#ifndef APCLIENT_CONST_H
#define APCLIENT_CONST_H
#include <types.h>

#include "checks.h"
#include "items.h"

#include <libkiwi.h>

namespace AP {

#define X(ID, IDENT, STR) CHECK_##IDENT = ID,
/**
 * @brief Archipelago world check ID
 */
enum CheckID { AP_CHECKS_X_MACRO CHECK_COUNT };
#undef X

#define X(ID, IDENT, STR) ITEM_##IDENT = ID,
/**
 * @brief Archipelago world item ID
 */
enum ItemID { AP_ITEMS_X_MACRO ITEM_COUNT, ITEM_INVALID = -1 };
#undef X

/**
 * @brief Sport ID
 */
enum ESport {
    ESport_Swf, //!< Swordplay
    ESport_Wkb, //!< Wakeboarding
    ESport_Fld, //!< Frisbee Dog
    ESport_Dgl, //!< Frisbee Golf
    ESport_Arc, //!< Archery
    ESport_Bsk, //!< Basketball
    ESport_Png, //!< Table Tennis
    ESport_Glf, //!< Golf
    ESport_Bwl, //!< Bowling
    ESport_Jsk, //!< Power Cruising
    ESport_Can, //!< Canoeing
    ESport_Bic, //!< Cycling
    ESport_Pln, //!< Airplane
    ESport_Omk, //!< Skydiving

    ESport_Max
};

/**
 * @brief Sequence ID
 */
enum ESeq {
    ESeq_None = -1, //!< None

    ESeq_Swf_Vs,  //!< Swordplay (Duel)
    ESeq_Swf_Prc, //!< Swordplay (Speed Slice)
    ESeq_Swf_Sgl, //!< Swordplay (Showdown)

    ESeq_Bsk_3pt, //!< Basketball (3-Point Contest)
    ESeq_Bsk_Vs,  //!< Basketball (Pickup Game)

    ESeq_Png,     //!< Table Tennis (Match)
    ESeq_Png_Ret, //!< Table Tennis (Return Challenge)

    ESeq_Bwl_Std, //!< Bowling (Standard Game)
    ESeq_Bwl_100, //!< Bowling (100-Pin Game)
    ESeq_Bwl_Wal, //!< Bowling (Spin Control)

    ESeq_Jsk_Rng, //!< Power Cruising (Slalom Course)
    ESeq_Jsk_Vs,  //!< Power Cruising (VS)

    ESeq_Can,    //!< Canoeing (Speed Challenge)
    ESeq_Can_Vs, //!< Canoeing (VS)

    ESeq_Bic,    //!< Cycling (Road Race)
    ESeq_Bic_Vs, //!< Cycling (VS)

    ESeq_Pln,    //!< Island Flyover
    ESeq_Pln_Vs, //!< Dogfight

    ESeq_Max
};

/**
 * @brief Champion ID
 */
enum EChamp {
    EChamp_Swf_Vs,  //!< Swordplay (Duel)
    EChamp_Swf_Prc, //!< Swordplay (Speed Slice)
    EChamp_Bsk_Vs,  //!< Basketball (Pickup Game)
    EChamp_Png,     //!< Table Tennis (Match)

    EChamp_Max
};

/**
 * @brief Archipelago scene ID
 */
enum ESceneID {
    ESceneID_DebugRootScene = kiwi::ESceneID_Max,
    // . . .

    ESceneID_Max
};

} // namespace AP

#endif
