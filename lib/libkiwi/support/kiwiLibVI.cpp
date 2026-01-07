#include <libkiwi.h>

#include <revolution/VI.h>

namespace kiwi {

/**
 * @brief Gets the target framerate of the current video configuration
 */
f32 LibVI::GetTargetFrameRate() {
    switch (VIGetTvFormat()) {
    case VI_TVFORMAT_NTSC:
    case VI_TVFORMAT_EURGB60:
    default: {
        return 59.94f;
    }

    case VI_TVFORMAT_PAL:
    case VI_TVFORMAT_MPAL: {
        return 50.0f;
    }
    }
}

} // namespace kiwi