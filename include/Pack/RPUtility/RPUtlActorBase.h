#ifndef RP_UTILITY_ACTOR_BASE_H
#define RP_UTILITY_ACTOR_BASE_H
#include <Pack/RPSystem/RP_DEBUG_STUB_1.h>
#include <Pack/RPTypes.h>

/**
 * @brief Basic actor with lifecycle hooks
 */
class RPUtlActorBase : public RP_DEBUG_STUB_1 {
public:
    RPUtlActorBase();
    virtual ~RPUtlActorBase(); // at 0x8

    virtual void Configure();    // at 0xC
    virtual void LoadResource(); // at 0x10
    virtual void Reset();        // at 0x14
    virtual void Calculate();    // at 0x18
    virtual void Exit();         // at 0x1C
    virtual void UserDraw();     // at 0x20
};

#endif
