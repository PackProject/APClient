#ifndef RP_PARTY_TNK_FIELD_MGR_H
#define RP_PARTY_TNK_FIELD_MGR_H
#include <Pack/RPParty/RPTnkScene/RPTnkGameObjMgrBase.h>
#include <Pack/RPTypes.h>

/**
 * @brief Tanks field manager
 */
class RPTnkFieldMgr {
    RP_SINGLETON_DECL(RPTnkFieldMgr);

public:
    f32 GetFieldWidthPixel() const {
        return mFieldWidthPixel;
    }
    f32 GetFieldHeightPixel() const {
        return mFieldHeightPixel;
    }

    u32 GetFieldWidthBlock() const {
        return mFieldWidthBlock;
    }
    u32 GetFieldHeightBlock() const {
        return mFieldHeightBlock;
    }

    f32 GetBlockSizeX() const {
        return mBlockSizeX;
    }
    f32 GetBlockSizeZ() const {
        return mBlockSizeZ;
    }

private:
    f32 mFieldWidthPixel;  // at 0x4
    f32 mFieldHeightPixel; // at 0x8
    u32 mFieldWidthBlock;  // at 0xC
    u32 mFieldHeightBlock; // at 0x10

    f32 mBlockSizeX; // at 0x14
    f32 mBlockSizeZ; // at 0x18
};

#endif
