#ifndef RP_PARTY_TNK_BLOCK_MGR_H
#define RP_PARTY_TNK_BLOCK_MGR_H
#include <Pack/RPParty/RPTnkScene/RPTnkBlock.h>
#include <Pack/RPParty/RPTnkScene/RPTnkGameObjMgrBase.h>
#include <Pack/RPTypes.h>

/**
 * @brief Tanks block object manager
 */
class RPTnkBlockMgr : public RPTnkGameObjMgrBase {
    RP_SINGLETON_DECL(RPTnkBlockMgr);

public:
    virtual RPTnkBlock* Create(); // at 0x24
    virtual void Finalize();      // at 0x2C

    void Clear();
};

#if defined(__KOKESHI__)
DECL_WEAK inline RPTnkBlockMgr::RPTnkBlockMgr() {}
#endif

#endif
