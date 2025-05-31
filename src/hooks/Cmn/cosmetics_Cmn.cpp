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
 * @param pModel Ball model
 */
void PatchBwlBallColor(RPGrpModelG3D* pModel, kiwi::Color color) {
    ASSERT_PTR(pModel);

    /**
     * Get access to the model material
     */
    nw4r::g3d::ScnMdl* pScnMdl = pModel->GetModelEx()->getScnMdl();
    ASSERT_PTR(pScnMdl);

    nw4r::g3d::ResMdl resMdl = pScnMdl->GetResMdl();
    ASSERT(resMdl.IsValid());

    nw4r::g3d::ResMat resMat = resMdl.GetResMat("bwg_ball_mat");
    ASSERT(resMat.IsValid());

    RPGrpModelMaterial* pMaterial = pModel->GetMaterial(resMat.GetID());
    ASSERT_PTR(pMaterial);

    nw4r::g3d::ScnMdl::CopiedMatAccess& rMatAccess =
        pMaterial->GetCopiedMatAccess();

    /**
     * Write the required TEV colors
     */
    // TEVREG0 holds the ball accent color
    pMaterial->SetTevColor(GX_TEVREG0, color.ToS10());
    // TEVKREG2 is used for greyscale conversion (P * 85 == P / 3)
    pMaterial->SetTevKColor(GX_KCOLOR2, kiwi::Color(0, 0, 0, 85));

    /**
     * Prepare the material for the new shader
     */
    nw4r::g3d::ResGenMode genMode = rMatAccess.GetResGenMode(false);
    ASSERT(genMode.IsValid());
    {
        // The new shader will have 7 stages
        genMode.GXSetNumTevStages(7);
    }
    genMode.EndEdit();

    /**
     * Write the TEV shader fragments
     */
    nw4r::g3d::ResTev tev = rMatAccess.GetResTev(false);
    ASSERT(tev.IsValid());
    {
        /**
         * Ball texture color is converted to greyscale,
         * then blended (Addition) with the accent color in TEVREG0
         */
        static const u8 ballShader[] = {
            0x61, 0xfe, 0x00, 0x00, 0x0f, 0x61, 0xf6, 0x00, 0x00, 0x04, 0x61,
            0xfe, 0x00, 0x00, 0x0f, 0x61, 0xf7, 0x00, 0x00, 0x0e, 0x61, 0xfe,
            0x00, 0x00, 0x0f, 0x61, 0xf8, 0x00, 0x00, 0x00, 0x61, 0xfe, 0x00,
            0x00, 0x0f, 0x61, 0xf9, 0x00, 0x00, 0x0c, 0x61, 0xfe, 0x00, 0x00,
            0x0f, 0x61, 0xfa, 0x00, 0x00, 0x05, 0x61, 0xfe, 0x00, 0x00, 0x0f,
            0x61, 0xfb, 0x00, 0x00, 0x0d, 0x61, 0xfe, 0x00, 0x00, 0x0f, 0x61,
            0xfc, 0x00, 0x00, 0x0a, 0x61, 0xfe, 0x00, 0x00, 0x0f, 0x61, 0xfd,
            0x00, 0x00, 0x0e, 0x61, 0x27, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x61, 0xfe, 0xff,
            0xff, 0xf0, 0x61, 0xf6, 0xe7, 0xb9, 0xe0, 0x61, 0x28, 0x3c, 0x03,
            0xc0, 0x61, 0xc0, 0x88, 0xfe, 0x8f, 0x61, 0xc2, 0x88, 0xfe, 0x84,
            0x61, 0xc1, 0x08, 0xff, 0xf4, 0x61, 0xc3, 0x08, 0xff, 0xf8, 0x61,
            0x10, 0x00, 0x00, 0x00, 0x61, 0x11, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x61, 0xfe, 0xff, 0xff, 0xf0, 0x61, 0xf7, 0xe0, 0x39, 0xe0,
            0x61, 0x29, 0x3b, 0xf3, 0xc0, 0x61, 0xc4, 0x08, 0xfe, 0x84, 0x61,
            0xc6, 0x08, 0x2c, 0x0f, 0x61, 0xc5, 0x08, 0xff, 0xfc, 0x61, 0xc7,
            0x08, 0xff, 0xf0, 0x61, 0x12, 0x00, 0x00, 0x00, 0x61, 0x13, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x61, 0xfe, 0xff, 0xff, 0xf0, 0x61,
            0xf8, 0xff, 0xff, 0xf0, 0x61, 0x2a, 0x3c, 0x90, 0x40, 0x61, 0xc8,
            0x08, 0xf0, 0xaf, 0x61, 0xca, 0x08, 0x8f, 0xe0, 0x61, 0xc9, 0x08,
            0xf3, 0x70, 0x61, 0xcb, 0x08, 0x9f, 0x00, 0x61, 0x14, 0x00, 0x00,
            0x00, 0x61, 0x15, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x61, 0xfe,
            0xff, 0xff, 0xf0, 0x61, 0xf9, 0x00, 0x38, 0xc0, 0x61, 0x2b, 0x3b,
            0xf3, 0xd2, 0x61, 0xcc, 0x08, 0xf8, 0x0f, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x61, 0xcd, 0x08, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x61, 0x16, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00,
        };

        std::memcpy(&tev.ref().dl, ballShader, sizeof(ballShader));
        tev.SetNumTevStages(7);
    }
    tev.EndEdit();
}

void InterceptBwlBallColor(RPGrpModelG3D* pModel, RPGrpModelG3D* pModelMirror) {
    ASSERT_PTR(pModel);
    ASSERT_PTR(pModelMirror);

    kiwi::Color color =
        kiwi::Color::FromHsv(kiwi::Random().NextF32(1.0f), 1.0f, 0.7f);

    PatchBwlBallColor(pModel, color);
    PatchBwlBallColor(pModelMirror, color);
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

/**
 * @brief Allow TEV manipulation in bowling ball models
 */
TRAMPOLINE_DEF(0x804c89d4, 0x804c89d8){
    // clang-format off
    li r7, 0x918 // Enable ScnMdl BUFFER_RESTEV buffer option
    blr
    // clang-format on
} TRAMPOLINE_DEF(0x804c89f8, 0x804c89fc){
    // clang-format off
    li r7, 0x918 // Enable ScnMdl BUFFER_RESTEV buffer option
    blr
    // clang-format on
} TRAMPOLINE_DEF(0x804c8a24, 0x804c8a28){
    // clang-format off
    li r7, 0x918 // Enable ScnMdl BUFFER_RESTEV buffer option
    blr
    // clang-format on
} TRAMPOLINE_DEF(0x804c8a48, 0x804c8a4c){
    // clang-format off
    li r7, 0x918 // Enable ScnMdl BUFFER_RESTEV buffer option
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
