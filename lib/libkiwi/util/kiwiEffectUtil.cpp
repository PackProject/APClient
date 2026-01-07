#include <libkiwi.h>

namespace kiwi {
namespace {

/**
 * @brief Common behavior across particle color traversal functions
 *
 * @param pManager Particle manager
 * @param type Particle color type
 * @param rColor New color value
 */
void SetParticleColorCommon(nw4r::ef::ParticleManager* pManager,
                            EffectUtil::EPtclColor type,
                            const GXColor& rColor) {

    K_ASSERT_PTR(pManager);
    K_ASSERT(type < EffectUtil::EPtclColor_Max);

    NW4R_UT_LIST_FOREACH(nw4r::ef::Particle, it,
                         pManager->GetParticleList()->mActiveList, {

        K_ASSERT_PTR(it);
        it->mParameter.mColor[type / 2][type % 2] = rColor;
    });
}

/**
 * @brief For-each traversal function which sets the particles' primary color
 * on layer 0
 *
 * @param pObject For-each object (particle manager)
 * @param param For-each parameter (color)
 */
void ModifierTravFunc_SetColor0Pri(void* pObject,
                                   nw4r::ef::ForEachParam param) {

    K_ASSERT_PTR(pObject);
    K_ASSERT_PTR(reinterpret_cast<void*>(param));

    nw4r::ef::ParticleManager* pManager =
        static_cast<nw4r::ef::ParticleManager*>(pObject);

    const GXColor& rColor = *reinterpret_cast<const GXColor*>(param);

    SetParticleColorCommon(pManager, EffectUtil::EPtclColor_Color0Pri, rColor);
}

/**
 * @brief For-each traversal function which sets the particles' secondary color
 * on layer 0
 *
 * @param pObject For-each object (particle manager)
 * @param param For-each parameter (color)
 */
void ModifierTravFunc_SetColor0Sec(void* pObject,
                                   nw4r::ef::ForEachParam param) {

    K_ASSERT_PTR(pObject);
    K_ASSERT_PTR(reinterpret_cast<void*>(param));

    nw4r::ef::ParticleManager* pManager =
        static_cast<nw4r::ef::ParticleManager*>(pObject);

    const GXColor& rColor = *reinterpret_cast<const GXColor*>(param);

    SetParticleColorCommon(pManager, EffectUtil::EPtclColor_Color0Sec, rColor);
}

/**
 * @brief For-each traversal function which sets the particles' primary color
 * on layer 1
 *
 * @param pObject For-each object (particle manager)
 * @param param For-each parameter (color)
 */
void ModifierTravFunc_SetColor1Pri(void* pObject,
                                   nw4r::ef::ForEachParam param) {

    K_ASSERT_PTR(pObject);
    K_ASSERT_PTR(reinterpret_cast<void*>(param));

    nw4r::ef::ParticleManager* pManager =
        static_cast<nw4r::ef::ParticleManager*>(pObject);

    const GXColor& rColor = *reinterpret_cast<const GXColor*>(param);

    SetParticleColorCommon(pManager, EffectUtil::EPtclColor_Color1Pri, rColor);
}

/**
 * @brief For-each traversal function which sets the particles' secondary color
 * on layer 1
 *
 * @param pObject For-each object (particle manager)
 * @param param For-each parameter (color)
 */
void ModifierTravFunc_SetColor1Sec(void* pObject,
                                   nw4r::ef::ForEachParam param) {

    K_ASSERT_PTR(pObject);
    K_ASSERT_PTR(reinterpret_cast<void*>(param));

    nw4r::ef::ParticleManager* pManager =
        static_cast<nw4r::ef::ParticleManager*>(pObject);

    const GXColor& rColor = *reinterpret_cast<const GXColor*>(param);

    SetParticleColorCommon(pManager, EffectUtil::EPtclColor_Color1Sec, rColor);
}

/**
 * @brief Emitter color traversal functions
 */
const nw4r::ef::ForEachFunc scEmitColorFuncs[EffectUtil::EEmitColor_Max] = {
    nw4r::ef::ParticleManager::ModifierTravFunc_SetSimpleLightAmbient,
    nw4r::ef::ParticleManager::ModifierTravFunc_SetSimpleLightDiffuse,
};

/**
 * @brief Particle color traversal functions
 */
const nw4r::ef::ForEachFunc scPtclColorFuncs[EffectUtil::EPtclColor_Max] = {
    ModifierTravFunc_SetColor0Pri,
    ModifierTravFunc_SetColor0Sec,
    ModifierTravFunc_SetColor1Pri,
    ModifierTravFunc_SetColor1Sec,
};

} // namespace

/**
 * @brief Sets the specified emitter color
 *
 * @param rHandle Effect handle
 * @param type Emitter color type
 * @param color New color value
 */
void EffectUtil::SetEmitterColor(nw4r::ef::EffectHandle& rHandle,
                                 EEmitColor type, Color color) {

    K_ASSERT(rHandle.IsValid());
    K_ASSERT(type < EEmitColor_Max);

    rHandle.GetPtr()->Modifier_SetSimpleLightType(
        type == EEmitColor_Ambient
            ? nw4r::ef::ParticleManager::ParticleModifier::SIMPLELIGHT_AMBIENT
            : nw4r::ef::ParticleManager::ParticleModifier::SIMPLELIGHT_DIFFUSE,
        false);

    rHandle.GetPtr()->ForeachParticleManager(
        scEmitColorFuncs[type],
        reinterpret_cast<nw4r::ef::ForEachParam>(&color), false);
}

/**
 * @brief Sets the specified particle color
 *
 * @param rHandle Effect handle
 * @param type Particle color type
 * @param color New color value
 */
void EffectUtil::SetParticleColor(nw4r::ef::EffectHandle& rHandle,
                                  EPtclColor type, Color color) {

    K_ASSERT(rHandle.IsValid());
    K_ASSERT(type < EPtclColor_Max);

    rHandle.GetPtr()->ForeachParticleManager(
        scPtclColorFuncs[type],
        reinterpret_cast<nw4r::ef::ForEachParam>(&color), false);
}

} // namespace kiwi