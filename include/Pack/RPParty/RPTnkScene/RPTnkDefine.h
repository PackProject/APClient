#ifndef RP_PARTY_TNK_DEFINE_H
#define RP_PARTY_TNK_DEFINE_H
#include <Pack/RPTypes.h>

namespace RPTnkDefine {

/**
 * @brief Model view ID
 */
enum EView {
    EView_0,
    EView_Actor,
};

/**
 * @brief Model draw scene ID
 */
enum EDrawScene {
    EDrawScene_Actor,
    EDrawScene_1,
    EDrawScene_2,
    EDrawScene_3,
    EDrawScene_4,

    EDrawScene_Max
};

/**
 * @brief Model draw group ID
 */
enum EDrawGroup {
    EDrawGroup_Actor,
};

} // namespace RPTnkDefine

#endif
