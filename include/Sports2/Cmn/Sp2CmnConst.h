#ifndef SPORTS2_CMN_CONST_H
#define SPORTS2_CMN_CONST_H
#include <Sports2/Sp2Types.h>

namespace Sp2 {
namespace Cmn {

/**
 * @brief Sport ID
 */
enum ESport {
    ESport_Swf,
    ESport_Wkb,
    ESport_Fld,
    ESport_Arc,
    ESport_Bsk,
    ESport_Png,
    ESport_Glf,
    ESport_Bwl,
    ESport_Jsk,
    ESport_Can,
    ESport_Bic,
    ESport_Pln,
    ESport_Omk,

    ESport_Max
};

/**
 * @brief Sequence ("category") ID
 */
enum ESeq {
    ESeq_Swf_Sgl = 1, //!< Swordplay (Showdown)
    ESeq_Swf_Vs = 5,  //!< Swordplay (Duel)
    ESeq_Swf_Prc = 6, //!< Swordplay (Speed Slice)

    ESeq_Jsk_Rng = 2, //!< Power Cruising (Slalom Course)
    ESeq_Jsk_Vs = 5,  //!< Power Cruising (VS)

    ESeq_Arc = 2, //!< Archery

    ESeq_Fld = 2, //!< Frisbee Dog

    ESeq_Bsk_3pt = 2, //!< Basketball (3-Point Contest)
    ESeq_Bsk_Vs = 5,  //!< Basketball (Pickup Game)

    ESeq_Bwl_Std = 2, //!< Bowling (Standard Game)
    ESeq_Bwl_100 = 3, //!< Bowling (100-Pin Game)
    ESeq_Bwl_Wal = 4, //!< Bowling (Spin Control)

    ESeq_Can = 8,    //!< Canoeing (Speed Challenge)
    ESeq_Can_Vs = 7, //!< Canoeing (VS)

    ESeq_Png_Ret = 2, //!< Table Tennis (Return Challenge)
    ESeq_Png = 5,     //!< Table Tennis (Match)

    ESeq_Wkb = 2, //!< Wakeboarding

    ESeq_Pln = 0,    //!< Airplane (Island Flyover)
    ESeq_Pln_Vs = 5, //!< Airplane (Dogfight)

    ESeq_Glf = 2, //!< Golf

    ESeq_Dgl = 2, //!< Frisbee Golf

    ESeq_Bic_Vs = 2, //!< Cycling (VS)
    ESeq_Bic = 8,    //!< Cycling (Road Race)

    ESeq_Omk = 1 //!< Skydiving
};

/**
 * @brief Sequence ID in the save data
 */
enum ESaveSeq {
    ESaveSeq_Swf_Sgl = 0, //!< Swordplay (Showdown)
    ESaveSeq_Swf_Vs = 1,  //!< Swordplay (Duel)
    ESaveSeq_Swf_Prc = 2, //!< Swordplay (Speed Slice)

    ESaveSeq_Jsk_Rng = 3, //!< Power Cruising (Slalom Course)
    ESaveSeq_Jsk_Vs = 4,  //!< Power Cruising (Slalom Course)

    ESaveSeq_Fld = 6, //!< Frisbee Dog

    ESaveSeq_Bsk_3pt = 7, //!< Basketball (3-Point Contest)
    ESaveSeq_Bsk_Vs = 8,  //!< Basketball (Pickup Game)

    ESaveSeq_Bwl_Std = 9,  //!< Bowling (Standard Game)
    ESaveSeq_Bwl_100 = 10, //!< Bowling (100-Pin Game)
    ESaveSeq_Bwl_Wal = 11, //!< Bowling (Spin Control)

    ESaveSeq_Can_Vs = 12, //!< Canoeing (VS)
    ESaveSeq_Can = 13,    //!< Canoeing (Speed Challenge)

    ESaveSeq_Png_Ret = 14, //!< Table Tennis (Return Challenge)
    ESaveSeq_Png = 15,     //!< Table Tennis (Match)

    ESaveSeq_Pln = 17,    //!< Airplane (Island Flyover)
    ESaveSeq_Pln_Vs = 18, //!< Airplane (Dogfight)

    ESaveSeq_Dgl = 20, //!< Frisbee Golf

    ESaveSeq_Bic_Vs = 21, //!< Cycling (VS)
    ESaveSeq_Bic = 22,    //!< Cycling (Road Race)

    ESaveSeq_Omk = 23, //!< Skydiving

    ESaveSeq_Max
};

/**
 * @brief Save data unlockables
 */
enum EUnlockState {
    EUnlockState_Unlocked,    //!< Unlocked
    EUnlockState_UnlockedNew, //!< Unlocked with "NEW!" text
    EUnlockState_Locked,      //!< Locked
};

} // namespace Cmn
} // namespace Sp2

#endif