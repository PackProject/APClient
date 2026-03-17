#ifndef RP_PARTY_TNK_TANK_H
#define RP_PARTY_TNK_TANK_H
#include <Pack/types_pack.h>

#include <Pack/RPParty/RPTnkScene/RPTnkGameObjBase.h>

/**
 * @brief Tanks tank object
 */
class RPTnkTank : public RPTnkGameObjBase {
public:
    RPTnkTank();
    virtual ~RPTnkTank(); // at 0x8
};

#endif
