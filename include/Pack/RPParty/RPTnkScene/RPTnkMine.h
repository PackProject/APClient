#ifndef RP_PARTY_TNK_MINE_H
#define RP_PARTY_TNK_MINE_H
#include <Pack/types_pack.h>

#include <Pack/RPParty/RPTnkScene/RPTnkGameObjBase.h>

/**
 * @brief Tanks mine object
 */
class RPTnkMine : public RPTnkGameObjBase {
public:
    RPTnkMine();
    virtual ~RPTnkMine(); // at 0x8
};

#endif
