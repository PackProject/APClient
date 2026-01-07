#ifndef RP_PARTY_TNK_SHELL_H
#define RP_PARTY_TNK_SHELL_H
#include <Pack/RPParty/RPTnkScene/RPTnkGameObjBase.h>
#include <Pack/RPTypes.h>

/**
 * @brief Tanks shell (bullet) object
 */
class RPTnkShell : public RPTnkGameObjBase {
public:
    RPTnkShell();
    virtual ~RPTnkShell(); // at 0x8

    void SetForceKill(bool enable) {
        mIsForceKill = enable;
    }

private:
    u32 mRicochetRemain; // at 0xB0
    char _B4[0xC5 - 0xB4];
    bool mIsForceKill; // at 0xC5
};

#endif
