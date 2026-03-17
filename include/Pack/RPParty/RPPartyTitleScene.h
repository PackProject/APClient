#ifndef RP_PARTY_TITLE_SCENE_H
#define RP_PARTY_TITLE_SCENE_H
#include <Pack/types_pack.h>

#include <Pack/RPSystem.h>

/**
 * @brief Party Pack title scene
 */
class RPPartyTitleScene : public RPSysScene {
public:
    enum EState {};

private:
    void CalculateFsm();

private:
    EState mState; // at 0x44
};

#endif
