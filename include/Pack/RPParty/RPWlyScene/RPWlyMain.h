#ifndef RP_PARTY_WLY_MAIN_H
#define RP_PARTY_WLY_MAIN_H
#include <Pack/types_pack.h>

#include <Pack/RPSingleton.h>

class RPWlyMain {
    RP_SINGLETON_DECL(RPWlyMain);

public:
    void Reset();
};

#endif
