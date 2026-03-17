#ifndef RP_PARTY_STATIC_MEM_H
#define RP_PARTY_STATIC_MEM_H
#include <Pack/types_pack.h>

#include <Pack/RPKernel.h>

class RPPartyStaticMem {
    RP_SINGLETON_DECL(RPPartyStaticMem);

public:
    void Reset();

    void SetPlayerNum(s32 num) {
        mPlayerNum = num;
    }
    s32 GetPlayerNum() const {
        return mPlayerNum;
    }

    u32 GetVariable() const {
        return mVariable;
    }
    void SetVariable(u32 no) {
        mVariable = no;
    }

private:
    s32 mPlayerNum; // at 0x4
    char _08[0x1C - 0x8];
    u32 mVariable; // at 0x1C
};

#endif
