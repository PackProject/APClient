#ifndef RP_PARTY_DUC_SEQUENCE_H
#define RP_PARTY_DUC_SEQUENCE_H
#include "RPTypes.h"

class RPDucSequence {
    RP_SINGLETON_DECL(RPDucSequence);

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

private:
    char _04[0x10 - 0x4];
    u32 mLevelNo;    // at 0x10
    u32 mMaxLevelNo; // at 0x14
};

#endif
