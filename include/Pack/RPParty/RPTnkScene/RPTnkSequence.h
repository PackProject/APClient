#ifndef RP_PARTY_TNK_SEQUENCE_H
#define RP_PARTY_TNK_SEQUENCE_H
#include <Pack/RPTypes.h>

class RPTnkSequence /* some base class */ {
    RP_SINGLETON_DECL(RPTnkSequence);

public:
    void SetLevelNo(u32 no) {
        mLevelNo = no;
    }
    u32 GetLevelNo() const {
        return mLevelNo;
    }

    void SetMaxLevelNo(u32 no) {
        mMaxLevelNo = no;
    }
    u32 GetMaxLevelNo() const {
        return mMaxLevelNo;
    }

    u32 GetPlayerNum() const {
        return mPlayerNum;
    }

private:
    char _04[0x8 - 0x4];
    u32 mLevelNo;    // at 0x8
    u32 mMaxLevelNo; // at 0xC
    char _10[0x28 - 0x10];
    u32 mPlayerNum; // at 0x28
};

#endif
