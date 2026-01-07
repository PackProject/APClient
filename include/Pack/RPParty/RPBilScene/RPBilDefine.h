#ifndef RP_PARTY_BIL_DEFINE_H
#define RP_PARTY_BIL_DEFINE_H
#include <Pack/RPTypes.h>

namespace RPBilDefine {

/**
 * @brief Model view ID
 */
enum EDrawView {
    EView_0,
    EView_3DDisplay,
    EView_2,
    EView_3,
    EView_3DTable,
    EView_2DLayout,
    EView_6,
    EView_7,
    EView_8,
    EView_9,
    EView_10,

    EView_Max
};

/**
 * @brief Model scene ID
 */
enum EDrawScene {
    EDrawScene_0,
    EDrawScene_Table,
    EDrawScene_2,
    EDrawScene_3,
    EDrawScene_Display,

    EDrawScene_Max
};

} // namespace RPBilDefine

#endif
