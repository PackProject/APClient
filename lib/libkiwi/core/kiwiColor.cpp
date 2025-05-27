#include <libkiwi.h>

#include <cmath>

namespace kiwi {

/**
 * @brief Converts RGB color to YUV format
 */
Color Color::ToYuv() const {
    u8 y = 0.257f * r + 0.504f * g + 0.098f * b + 16.0f;
    u8 u = -0.148f * r - 0.291f * g + 0.439f * b + 128.0f;
    u8 v = 0.439f * r - 0.368f * g - 0.071f * b + 128.0f;
    return Color(y, u, v, a);
}

/**
 * @brief Creates RGB color from HSV format
 *
 * @param h Hue [0, 1]
 * @param s Saturation [0, 1]
 * @param v Value [0, 1]
 */
Color Color::FromHsv(f32 h, f32 s, f32 v) {
    K_ASSERT(h >= 0.0f && h <= 1.0f);
    K_ASSERT(s >= 0.0f && s <= 1.0f);
    K_ASSERT(v >= 0.0f && v <= 1.0f);

    f32 r = 0.0f;
    f32 g = 0.0f;
    f32 b = 0.0f;

    s32 i = static_cast<s32>(h * 6.0f);
    f32 f = h * 6.0f - i;

    f32 p = v * (1.0f - s);
    f32 q = v * (1.0f - f * s);
    f32 t = v * (1.0f - (1.0f - f) * s);

    // clang-format off
    switch (i % 6) {
        case 0: { r = v, g = t, b = p; break; }
        case 1: { r = q, g = v, b = p; break; }
        case 2: { r = p, g = v, b = t; break; }
        case 3: { r = p, g = q, b = v; break; }
        case 4: { r = t, g = p, b = v; break; }
        case 5: { r = v, g = p, b = q; break; }
    }
    // clang-format on

    r *= 255;
    g *= 255;
    b *= 255;

    // clang-format off
    return Color(static_cast<u8>(r),
                 static_cast<u8>(g),
                 static_cast<u8>(b),
                 255);
    // clang-format on
}

} // namespace kiwi
