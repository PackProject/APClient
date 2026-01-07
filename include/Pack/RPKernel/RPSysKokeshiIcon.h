#ifndef RP_KERNEL_KOKESHI_ICON_H
#define RP_KERNEL_KOKESHI_ICON_H
#include <Pack/RPKernel/RPSysAvatar.h>
#include <Pack/RPTypes.h>

class RPSysKokeshiIcon : public RPSysAvatar {
public:
    RPSysKokeshiIcon(const RPSysKokeshiGenInfo*);
    virtual ~RPSysKokeshiIcon(); // at 0x8

    virtual void LoadResource(const RPSysKokeshiOverloadInfo* = NULL);
    virtual void ApplyLightTexture(u8);
};

#endif
