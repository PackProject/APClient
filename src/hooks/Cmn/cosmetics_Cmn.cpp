#include <types.h>

#include "core/CosmeticMgr.h"
#include "core/ItemMgr.h"
#include "hooks/Swf/items_Swf.h"
#include "hooks/trampoline.h"

#include <Pack/RPGraphics.h>
#include <Pack/RPKernel.h>
#include <Pack/RPSystem.h>
#include <Sports2/Sp2Cmn.h>
#include <nw4r/g3d.h>

#include <libkiwi.h>

#include <RVLFaceLibInternal.h>

namespace AP {
namespace Cmn {
namespace Cosmetic {

/******************************************************************************
 *
 * Random Music
 *
 ******************************************************************************/

/**
 * @brief Overrides the BGM ID based on the randomizer settings
 *
 * @param id Original music ID
 */
u32 InterceptBgm(u32 id) {
    // Randomization disabled
    if (!CosmeticMgr::GetInstance().IsRandomBgm()) {
        return id;
    }

    // Not music
    if (!CosmeticMgr::IsBgm(id)) {
        return id;
    }

    return CosmeticMgr::GetInstance().GetRandomBgm(id);
}

/**
 * @brief InterceptBgm trampoline
 */
TRAMPOLINE_DEF(0x802B722C, 0x802B7230){
    // clang-format off
    TRAMPOLINE_BEGIN

    bl InterceptBgm
    mr r0, r3 // New ID must outlive the stack frame

    TRAMPOLINE_END
    mr r4, r0
    blr
    // clang-format on
}

/******************************************************************************
 *
 * Random Mii Outfit/Color
 *
 ******************************************************************************/

/**
 * @brief Generates a random Mii favorite color
 */
kiwi::Color GetRandomFavoriteColor() {
    kiwi::Random r;

    // 1% chance for white/black/grey
    if (r.Chance(0.01)) {
        return kiwi::Color::WHITE;
    }
    if (r.Chance(0.01)) {
        return kiwi::Color::BLACK;
    }
    if (r.Chance(0.01)) {
        return kiwi::Color::GREY;
    }

    f32 h = r.NextF32(1.0f);
    f32 s = 0.0f;
    f32 v = 0.0f;

    switch (r.NextU32(4)) {
    // High saturation, high value
    case 0:
    case 1: {
        s = r.NextF32(0.75f, 0.95f);
        v = r.NextF32(0.8f, 1.0f);
        break;
    }

    // Low saturation, high value
    case 2: {
        s = r.NextF32(0.6f, 0.7f);
        v = r.NextF32(0.8f, 1.0f);
        break;
    }

    // High saturation, low value
    case 3: {
        s = r.NextF32(0.8f, 1.0f);
        v = r.NextF32(0.4f, 0.8f);
        break;
    }
    }

    return kiwi::Color::FromHsv(h, s, v);

    // return kiwi::Color::FromHsv(r.NextF32(1.0f), r.NextF32(0.65f, 1.0f),
    //                             r.NextF32(0.40f, 1.0f));
}

/**
 * @brief Generates a random RFL favorite color
 *
 * @param color Favorite color ID
 */
GXColor InterceptFavoriteColor(RFLFavoriteColor color) {
    static const GXColor cFavoriteColor[RFLFavoriteColor_Max] = {
        // clang-format off
        {184, 64,  48,  255}, //!< RFLFavoriteColor_Red
        {240, 120, 40,  255}, //!< RFLFavoriteColor_Orange
        {248, 216, 32,  255}, //!< RFLFavoriteColor_Yellow
        {128, 200, 40,  255}, //!< RFLFavoriteColor_YellowGreen
        {0,   116, 40,  255}, //!< RFLFavoriteColor_Green
        {32,  72,  152, 255}, //!< RFLFavoriteColor_Blue
        {64,  160, 216, 255}, //!< RFLFavoriteColor_SkyBlue
        {232, 96,  120, 255}, //!< RFLFavoriteColor_Pink
        {112, 44,  168, 255}, //!< RFLFavoriteColor_Purple
        {72,  56,  24,  255}, //!< RFLFavoriteColor_Brown
        {224, 224, 224, 255}, //!< RFLFavoriteColor_White
        {24,  24,  20,  255}, //!< RFLFavoriteColor_Black
        // clang-format on
    };

    if (!CosmeticMgr::GetInstance().IsRandomFavoriteColor()) {
        return cFavoriteColor[color];
    }

    return GetRandomFavoriteColor();
}

/**
 * @brief InterceptFavoriteColor trampoline
 */
TRAMPOLINE_DEF(0x80102a20, 0x80102a30) {
    // clang-format off
    TRAMPOLINE_BEGIN_SAVED

    bl InterceptFavoriteColor

    TRAMPOLINE_END_SAVED
    blr
    // clang-format on
}

/**
 * @brief Intercepts RFLiInitCharModel calls to store the hat randomized color
 *
 * @param pCharModel RFL character model
 * @param ... RFLInitCharModel params
 */
void InterceptInitCharModel(RFLCharModel* pCharModel, RFLiCharInfo* pCharInfo,
                            void* pModelWork, RFLResolution modelRes,
                            u32 exprFlags) {

    ASSERT_PTR(pCharModel);
    RFLiInitCharModel(pCharModel, pCharInfo, pModelWork, modelRes, exprFlags);

    // Access internal RFL structure
    RFLiCharModel* pModelImpl = reinterpret_cast<RFLiCharModel*>(pCharModel);
    ASSERT_PTR(pModelImpl->res);

    GXColor favColor = InterceptFavoriteColor(
        static_cast<RFLFavoriteColor>(pModelImpl->res->favoriteColor));

    // Use unused space as work memory for the random color
    *reinterpret_cast<GXColor*>(pModelImpl->res->UNK_0x8250) = favColor;
}

/**
 * @brief InterceptInitCharModel trampoline
 */
TRAMPOLINE_DEF(0x80102614, 0x80102618) {
    // clang-format off
    TRAMPOLINE_BEGIN

    bl InterceptInitCharModel

    TRAMPOLINE_END
    blr
    // clang-format on
}

/**
 * @brief Intercepts the RFL favorite color used for drawing hat models
 *
 * @param pChara RFL character model resources
 * @param pSetting RFL draw setting
 */
void InterceptFavoriteColorHat(const RFLiCharModelRes* pCharModel,
                               const RFLDrawCoreSetting* pSetting) {
    ASSERT_PTR(pCharModel);
    ASSERT_PTR(pSetting);

    if (!CosmeticMgr::GetInstance().IsRandomFavoriteColor()) {
        RFLFavoriteColor color =
            static_cast<RFLFavoriteColor>(pCharModel->favoriteColor);

        GXSetTevKColor(pSetting->tevKColorID, RFLGetFavoriteColor(color));

    } else {
        // InterceptInitCharModel writes the color to this unused memory
        GXColor favColor =
            *reinterpret_cast<const GXColor*>(pCharModel->UNK_0x8250);
        GXSetTevKColor(pSetting->tevKColorID, favColor);
    }
}

/**
 * @brief Disable MiiClothChanger
 */
TRAMPOLINE_DEF(0x801f546c, 0x801f5514){
    // clang-format off
    TRAMPOLINE_BEGIN
    nop
    TRAMPOLINE_END
    blr
    // clang-format on
}

/**
 * @brief InterceptFavoriteColorHat trampoline
 */
TRAMPOLINE_DEF(0x801032c4, 0x801032c8) {
    // clang-format off
    TRAMPOLINE_BEGIN

    mr r3, r30
    mr r4, r29
    bl InterceptFavoriteColorHat

    TRAMPOLINE_END
    blr
    // clang-format on
}

/******************************************************************************
 *
 * Random Bowling Ball Color
 *
 ******************************************************************************/
/**
 * @brief Overrides the bowling ball model color based on the randomizer
 * settings
 *
 * @param mdl Ball model
 */
void PatchBwlBallColor(nw4r::g3d::ResMdl mdl, kiwi::Color color) {
    ASSERT(mdl.IsValid());

    nw4r::g3d::ResMat bwg_ball_mat = mdl.GetResMat("bwg_ball_mat");
    ASSERT(bwg_ball_mat.IsValid());

    // Ball color is stored in TEV color 0
    nw4r::g3d::ResMatTevColor tevColor = bwg_ball_mat.GetResMatTevColor();
    ASSERT(tevColor.IsValid());

    tevColor.GXSetTevColor(GX_TEVREG0, color);

    // TODO: Patch the shader to use the TEV color
    ;
}

void InterceptBwlBallColor(RPGrpModelG3D* pModel, RPGrpModelG3D* pModelMirror) {
    ASSERT_PTR(pModel);
    ASSERT_PTR(pModelMirror);

    nw4r::g3d::ResMdl mdl =
        pModel->GetModelEx()->getScnMdlSimple()->GetResMdl();

    ASSERT(mdl.IsValid());

    nw4r::g3d::ResMdl mdlMirror =
        pModelMirror->GetModelEx()->getScnMdlSimple()->GetResMdl();

    ASSERT(mdlMirror.IsValid());

    kiwi::Color color =
        kiwi::Color::FromHsv(kiwi::Random().NextF32(1.0f), 0.5f, 1.0f);

    PatchBwlBallColor(mdl, color);
    PatchBwlBallColor(mdlMirror, color);
}

/**
 * @brief InterceptBwlBallColor trampoline
 */
TRAMPOLINE_DEF(0x804d1174, 0x804d1178){
    // clang-format off
    TRAMPOLINE_BEGIN

    mr r3, r5
    mr r4, r6
    bl InterceptBwlBallColor

    TRAMPOLINE_END
    rlwinm r0, r4, 0x3, 0x0, 0x1C // original instruction
    blr
    // clang-format on
}

/******************************************************************************
 *
 * Random Island Time
 *
 ******************************************************************************/

/**
 * @brief Overrides the island time based on the randomizer settings
 *
 * @param pScene Incoming scene
 */
RPSysScene::ETime InterceptIslandTime(RPSysScene* pScene) {
    ASSERT_PTR(pScene);

    // Randomization disabled
    if (!CosmeticMgr::GetInstance().IsRandomTime()) {
        return pScene->getIslandTime();
    }

    s32 group = RP_GET_INSTANCE(Sp2::Cmn::StaticMem)->getSceneGroup();

    // Ignore Island Flyover
    if (group == Sp2::Cmn::EGroupID_Pln) {
        return pScene->getIslandTime();
    }

    // 'Auto' delegates to the scene
    RPSysScene::ETime time = CosmeticMgr::GetInstance().GetRandomTime(group);
    return time != RPSysScene::ETime_Auto ? time : pScene->getIslandTime();
}
KM_CALL(0x8026a56c, InterceptIslandTime);

} // namespace Cosmetic
} // namespace Cmn
} // namespace AP
