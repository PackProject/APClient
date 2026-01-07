#ifndef RP_GRAPHICS_CAMERA_H
#define RP_GRAPHICS_CAMERA_H
#include <Pack/RPTypes.h>
#include <nw4r/g3d.h>

#include <nw4r/math.h>

class RPGrpCamera {
protected:
    nw4r::math::MTX34 MTX_0x0;  // at 0x0
    nw4r::math::MTX34 MTX_0x30; // at 0x30
    nw4r::math::MTX34 MTX_0x60; // at 0x60
    nw4r::math::MTX34 MTX_0x90; // at 0x90

    nw4r::math::VEC3 VEC3_0xC0; // at 0xC0
    nw4r::math::VEC3 VEC3_0xCC; // at 0xCC
    char _D8[0xF4 - 0xD8];
    nw4r::math::VEC3 VEC3_0xF4;  // at 0xF4
    nw4r::math::VEC3 VEC3_0x100; // at 0x100

    u32 mProjType; // at 0x10C
    u16 mFlags;    // at 0x110

    nw4r::math::MTX34 MTX_0x114; // at 0x114
    nw4r::math::MTX34 MTX_0x144; // at 0x144

public:
    RPGrpCamera();

    virtual ~RPGrpCamera();                                  // at 0x8
    virtual void CopyFromAnother(const RPGrpCamera& rOther); // at 0xC

    void LoadScnCameraMatrix(const nw4r::g3d::ResAnmScn scn, u8 refNumber,
                             f32 frame);
};

#endif
