#ifndef RVL_SDK_GX_DISPLAY_LIST_H
#define RVL_SDK_GX_DISPLAY_LIST_H
#include <types.h>

#include <revolution/GX/GXHardware.h>
#ifdef __cplusplus
extern "C" {
#endif

void GXBeginDisplayList(void* list, u32 size);
u32 GXEndDisplayList(void);
void GXCallDisplayList(void* list, u32 size);

#if defined(LIBKIWI_PRECOMPILE)
#define static inline
#endif

static void GXFastCallDisplayList(void* list, u32 size) {
    WGPIPE.c = GX_FIFO_CMD_CALL_DL;
    WGPIPE.p = list;
    WGPIPE.ui = size;
}

#if defined(LIBKIWI_PRECOMPILE)
#undef static
#endif

#ifdef __cplusplus
}
#endif
#endif
