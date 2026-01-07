#ifndef RP_KERNEL_EFFECT_BASE_H
#define RP_KERNEL_EFFECT_BASE_H
#include <nw4r/ef.h>

#include <RPTypes.h>

class RPSysEffect {
public:
    RPSysEffect(const char* pName, u32 drawScene, u32 owner);
    virtual ~RPSysEffect(); // at 0x8

    virtual bool create();    // at 0xC
    virtual void VF_10();     // at 0x10
    virtual void VF_14();     // at 0x14
    virtual void forceKill(); // at 0x18
    virtual void VF_1C();     // at 0x1C

    virtual void setDisableDraw(bool disable); // at 0x20
    virtual void VF_24();                      // at 0x24
    virtual void setLife(f32 life);            // at 0x28
    virtual void setEmitRatio(f32 ratio);      // at 0x2C

    virtual void VF_30(); // at 0x30
    virtual void VF_34(); // at 0x34
    virtual void VF_38(); // at 0x38
    virtual void VF_3C(); // at 0x3C

    virtual void VF_40(); // at 0x40
    virtual void VF_44(); // at 0x44
    virtual void VF_48(); // at 0x48
    virtual void VF_4C(); // at 0x4C

    virtual void setColor(u8 r, u8 g, u8 b, u8 a); // at 0x50
    virtual void VF_54();                          // at 0x54
    virtual void VF_58();                          // at 0x58
    virtual void VF_5C();                          // at 0x5C

    virtual void VF_60(); // at 0x60
    virtual void VF_64(); // at 0x64
    virtual void VF_68(); // at 0x68
    virtual void VF_6C(); // at 0x6C

    virtual void VF_70();                                  // at 0x70
    virtual void VF_74();                                  // at 0x74
    virtual void setScale(const nw4r::math::VEC3& rScale); // at 0x78
    virtual void setPos(const nw4r::math::VEC3& rPos);     // at 0x7C

    virtual void setMtx(const nw4r::math::MTX34& rMtx); // at 0x80
    virtual void VF_84();                               // at 0x84
    virtual void update();                              // at 0x88
    virtual void VF_8C();                               // at 0x8C

    virtual void VF_90(); // at 0x90
    virtual void VF_94(); // at 0x94

    nw4r::ef::EffectHandle& GetHandle() {
        return mEffectHandle;
    }
    const nw4r::ef::EffectHandle& GetHandle() const {
        return mEffectHandle;
    }

private:
    char _04[0x78 - 0x4];
    nw4r::ef::EffectHandle mEffectHandle; // at 0x78
};

#endif
