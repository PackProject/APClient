#ifndef RP_PARTY_TNK_SHELL_MGR_H
#define RP_PARTY_TNK_SHELL_MGR_H
#include <Pack/RPParty/RPTnkScene/RPTnkGameObjMgrBase.h>
#include <Pack/RPParty/RPTnkScene/RPTnkShell.h>
#include <Pack/RPTypes.h>

/**
 * @brief Tanks mine object manager
 */
class RPTnkShellMgr : public RPTnkGameObjMgrBase {
    RP_SINGLETON_DECL(RPTnkShellMgr);

public:
    virtual RPTnkShell* Create(); // at 0x24
    virtual void Finalize();      // at 0x2C

private:
    char _18[0x40 - 0x18];
};

#if defined(__KOKESHI__)
DECL_WEAK inline RPTnkShellMgr::RPTnkShellMgr() {}
#endif

#endif
