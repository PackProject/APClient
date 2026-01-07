#ifndef RP_KERNEL_KOKESHI_MANAGER_H
#define RP_KERNEL_KOKESHI_MANAGER_H
#include <Pack/RPTypes.h>

// Forward declarations
class IRPSysKokeshiBodyManager;

class RPSysKokeshiManager {
    RP_SINGLETON_DECL(RPSysKokeshiManager);

public:
    enum GenType {};

public:
    void LoadStaticResource();

    void SetBodyManager(IRPSysKokeshiBodyManager* pManager) {
        mBodyManager = pManager;
    }

private:
    char _04[0x54];
    IRPSysKokeshiBodyManager* mBodyManager; // at 0x58
};

#endif
