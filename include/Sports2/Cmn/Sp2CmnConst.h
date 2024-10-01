#ifndef SPORTS2_CMN_CONST_H
#define SPORTS2_CMN_CONST_H
#include <Sports2/Sp2Types.h>

namespace Sp2 {
namespace Cmn {

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

    ESeq_Can = 7,    //!< Canoeing (Speed Challenge)
    ESeq_Can_Vs = 8, //!< Canoeing (VS)

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

} // namespace Cmn
} // namespace Sp2

#endif