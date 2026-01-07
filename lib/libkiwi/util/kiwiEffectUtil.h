#ifndef LIBKIWI_UTIL_EFFECT_UTIL_H
#define LIBKIWI_UTIL_EFFECT_UTIL_H
#include <libkiwi/core/kiwiColor.h>
#include <libkiwi/k_types.h>

#include <nw4r/ef.h>

namespace kiwi {
//! @addtogroup libkiwi_util
//! @{

/**
 * @brief NW4R effect utilities
 */
class EffectUtil {
public:
    /**
     * @brief Emitter color ID
     */
    enum EEmitColor {
        EEmitColor_Ambient, // Emitter ambient
        EEmitColor_Diffuse, // Emitter diffuse

        EEmitColor_Max
    };

    /**
     * @brief Particle color ID
     */
    enum EPtclColor {
        EPtclColor_Color0Pri, // Particle layer 0 primary color
        EPtclColor_Color0Sec, // Particle layer 0 secondary color
        EPtclColor_Color1Pri, // Particle layer 1 primary color
        EPtclColor_Color1Sec, // Particle layer 1 secondary color

        EPtclColor_Max
    };

public:
    /**
     * @brief Sets the specified emitter color
     *
     * @param rHandle Effect handle
     * @param type Emitter color type
     * @param color New color value
     */
    static void SetEmitterColor(nw4r::ef::EffectHandle& rHandle,
                                EEmitColor type, Color color);

    /**
     * @brief Sets the specified particle color
     *
     * @param rHandle Effect handle
     * @param type Particle color type
     * @param color New color value
     */
    static void SetParticleColor(nw4r::ef::EffectHandle& rHandle,
                                 EPtclColor type, Color color);
};

//! @}
} // namespace kiwi

#endif
