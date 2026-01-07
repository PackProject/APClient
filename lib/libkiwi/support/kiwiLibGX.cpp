#include <libkiwi.h>

#include <revolution/VI.h>

namespace kiwi {

/**
 * @brief Gets "default" GX render mode based on VI format
 */
const GXRenderModeObj* LibGX::GetDefaultRenderMode() {
    switch (VIGetTvFormat()) {
    case VI_TVFORMAT_NTSC: {
        return &GXNtsc480IntDf;
    }

    case VI_TVFORMAT_PAL: {
        return &GXPal528IntDf;
    }

    case VI_TVFORMAT_EURGB60: {
        return &GXEurgb60Hz480IntDf;
    }

    case VI_TVFORMAT_MPAL: {
        return &GXMpal480IntDf;
    }

    default: {
        K_UNREACHABLE();
        return nullptr;
    }
    }
}

} // namespace kiwi
