#ifndef RP_KERNEL_I_KOKESHI_BODY_MANAGER_H
#define RP_KERNEL_I_KOKESHI_BODY_MANAGER_H
#include <Pack/RPTypes.h>

#include <nw4r/math.h>

#include <RVLFaceLib.h>

//! @addtogroup rp_kernel
//! @{

// Forward declarations
class RPGrpModel;

/**
 * @brief Kokeshi body manager
 */
class IRPSysKokeshiBodyManager {
public:
    virtual u16 GetFriendClothesStartIndex() = 0; // at 0x8
    virtual u16 GetFriendClothesIndexRange() = 0; // at 0xC

    virtual const char* GetBodyFileName(u16, RFLSex) = 0; // at 0x10
    virtual u16 GetDummyHeadModelndex() = 0;              // at 0x14
    virtual const char* GetClothesFileName() = 0;         // at 0x18
    virtual void GetClothesName(u16, RFLSex, const char**,
                                const char**) = 0; // at 0x1C

    virtual void GetHeadJointMtx(u16, RPGrpModel*,
                                 nw4r::math::MTX34*) = 0; // at 0x20
    virtual void GetLeftHandJointMtx(u16, RPGrpModel*,
                                     nw4r::math::MTX34*) = 0; // at 0x24
    virtual void GetRightHandJointMtx(u16, RPGrpModel*,
                                      nw4r::math::MTX34*) = 0; // at 0x28

    virtual ~IRPSysKokeshiBodyManager() = 0; // at 0x2C
};

//! @}

#endif
