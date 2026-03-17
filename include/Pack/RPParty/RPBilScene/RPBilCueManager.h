#ifndef RP_PARTY_BIL_CUE_MANAGER_H
#define RP_PARTY_BIL_CUE_MANAGER_H
#include <Pack/types_pack.h>

#include <Pack/RPParty/RPBilScene/RPBilCue.h>
#include <Pack/RPParty/RPBilScene/RPBilMain.h>

// Forward declarations
class RPBilCue;

class RPBilCueManager {
    RP_SINGLETON_DECL(RPBilCueManager);

public:
    RPBilCue* GetCue(u32 index) {
        return mpCues[index];
    }

private:
    static const u32 MAX_CUE = 2;

    s32 mCueNum; // at 0x4
    char _08[0x10 - 0x8];
    RPBilCue* mpCues[MAX_CUE]; // at 0x10
};

#endif
