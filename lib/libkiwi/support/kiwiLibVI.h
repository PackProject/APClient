#ifndef LIBKIWI_SUPPORT_LIBVI_H
#define LIBKIWI_SUPPORT_LIBVI_H
#include <libkiwi/k_types.h>

#include <revolution/OS.h>

namespace kiwi {
//! @addtogroup libkiwi_support
//! @{

/**
 * @brief VI library wrapper/extension
 */
class LibVI {
public:
    /**
     * @brief Gets the target framerate of the current video configuration
     */
    static f32 GetTargetFrameRate();
};

//! @}
} // namespace kiwi

#endif
