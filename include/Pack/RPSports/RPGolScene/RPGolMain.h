#ifndef RP_SPORTS_GOL_MAIN_H
#define RP_SPORTS_GOL_MAIN_H
#include <Pack/types_pack.h>

#include <Pack/RPSingleton.h>

class RPGolMain {
    RP_SINGLETON_DECL(RPGolMain);

public:
    void NextShot();
};

#endif
