#ifndef RP_PARTY_TNK_MINE_MGR_H
#define RP_PARTY_TNK_MINE_MGR_H
#include <Pack/types_pack.h>

#include <Pack/RPParty/RPTnkScene/RPTnkGameObjMgrBase.h>
#include <Pack/RPParty/RPTnkScene/RPTnkMine.h>
#include <Pack/RPSingleton.h>

/**
 * @brief Tanks mine object manager
 */
class RPTnkMineMgr : public RPTnkGameObjMgrBase {
    RP_SINGLETON_DECL(RPTnkMineMgr);

public:
    virtual RPTnkMine* Create(); // at 0x24
    virtual void Finalize();     // at 0x2C

    bool IsExplodeBlock(const RPTnkGameObjBase* pOther) const;
    bool IsExplodeMine(const RPTnkGameObjBase* pOther) const;
};

#endif
