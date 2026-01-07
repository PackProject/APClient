#ifndef RP_PARTY_BODY_MANAGER_H
#define RP_PARTY_BODY_MANAGER_H
#include <Pack/RPKernel/IRPSysKokeshiBodyManager.h>
#include <Pack/RPTypes.h>

//! @addtogroup rp_kernel
//! @{

/**
 * @brief Party Pack kokeshi body manager
 */
class RPPartyBodyManager : public IRPSysKokeshiBodyManager {
public:
    RPPartyBodyManager();
    virtual ~RPPartyBodyManager(); // at 0x2C

    virtual u16 GetFriendClothesStartIndex(); // at 0x8
    virtual u16 GetFriendClothesIndexRange(); // at 0xC

    virtual const char* GetBodyFileName(u16, RFLSex); // at 0x10
    virtual u16 GetDummyHeadModelndex();              // at 0x14
    virtual const char* GetClothesFileName();         // at 0x18
    virtual void GetClothesName(u16, RFLSex, const char**,
                                const char**); // at 0x1C

    virtual void GetHeadJointMtx(u16, RPGrpModel*,
                                 nw4r::math::MTX34*); // at 0x20
    virtual void GetLeftHandJointMtx(u16, RPGrpModel*,
                                     nw4r::math::MTX34*); // at 0x24
    virtual void GetRightHandJointMtx(u16, RPGrpModel*,
                                      nw4r::math::MTX34*); // at 0x28
};

//! @}

#endif
