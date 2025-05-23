#ifndef LIBKIWI_CORE_COLOR_H
#define LIBKIWI_CORE_COLOR_H
#include <libkiwi/k_types.h>

#include <nw4r/ut.h>

namespace kiwi {
//! @addtogroup libkiwi_core
//! @{

/**
 * @brief RGBA/YUV color
 */
class Color : public nw4r::ut::Color {
public:
    /**
     * @brief Constructor
     * @details The default color is white.
     */
    Color() {
        *this = WHITE;
    }

    /**
     * @brief Constructor
     *
     * @param r Red component
     * @param g Green component
     * @param b Blue component
     * @param a Alpha component
     */
    Color(u8 _r, u8 _g, u8 _b, u8 _a) {
        r = _r;
        g = _g;
        b = _b;
        a = _a;
    }

    /**
     * @brief Constructor
     *
     * @param color RGBA32 color
     */
    Color(u32 color) {
        r = color >> 24 & 0xFF;
        g = color >> 16 & 0xFF;
        b = color >> 8 & 0xFF;
        a = color >> 0 & 0xFF;
    }

    /**
     * @brief Implicit conversion operator (RGBA order)
     */
    operator u32() const {
        return Rgba32();
    }

    /**
     * @brief Converts color to u32 representation (RGBA order)
     */
    u32 Rgba32() const {
        return r << 24 | g << 16 | b << 8 | a;
    }
    /**
     * @brief Converts color to u32 representation (ARGB order)
     */
    u32 Argb32() const {
        return a << 24 | r << 16 | g << 8 | b;
    }

    /**
     * @brief Converts RGB color to YUV format
     */
    Color Yuv() const;

public:
    /**
     * @name Preset Colors
     */
    /**@{*/
    static const u32 RED = 0xFF0000FF;
    static const u32 ORANGE = 0xFF8000FF;
    static const u32 YELLOW = 0xFFFF00FF;
    static const u32 GREEN = 0x00FF00FF;
    static const u32 BLUE = 0x0000FFFF;
    static const u32 PURPLE = 0x8000FFFF;
    static const u32 PINK = 0xFF00FFFF;
    static const u32 CYAN = 0x00FFFFFF;
    static const u32 BLACK = 0x000000FF;
    static const u32 WHITE = 0xFFFFFFFF;
    static const u32 BROWN = 0x643200FF;
    static const u32 GREY = 0x808080FF;
    /**@}*/
};

//! @}
} // namespace kiwi

#endif
