#include "trampoline.h"
#include <Pack/RPGraphics.h>
#include <Sports2/Sp2Cmn.h>
#include <nw4r/g3d.h>

#include <libkiwi.h>

namespace AP {
namespace Bwl {
namespace Cosmetic {

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
 * @param mirror Whether this model is the mirror model
 * @param color New ball color
 */
void PatchBwlBallColor(RPGrpModelG3D* pModel, bool mirror, kiwi::Color color) {
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
    // TEVKREG2 is used for greyscale conversion constants
    pMaterial->SetTevKColor(GX_KCOLOR2, kiwi::Color(85, 150, 29, 0));

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
        static const u32 ballShader[] = {
            0x61FE0000, 0x0F61F600, 0x000461FE, 0x00000F61, 0xF700000E,
            0x61FE0000, 0x0F61F800, 0x000061FE, 0x00000F61, 0xF900000C,
            0x61FE0000, 0x0F61FA00, 0x000561FE, 0x00000F61, 0xFB00000D,
            0x61FE0000, 0x0F61FC00, 0x000A61FE, 0x00000F61, 0xFD00000E,
            0x6127FFFF, 0xFF000000, 0x00000000, 0x00000000, 0x61FEFFFF,
            0xF061F6E5, 0xB9206128, 0x3C03C061, 0xC088FE8F, 0x61C288FE,
            0x8461C108, 0xFFF461C3, 0x08FFF861, 0x10000000, 0x61110000,
            0x00000000, 0x61FEFFFF, 0xF061F7E0, 0x39A06129, 0x3BF3C061,
            0xC408FE84, 0x61C6002C, 0x0261C508, 0xFFFC61C7, 0x08FFF061,
            0x12000000, 0x61130000, 0x00000000, 0x61FEFFFF, 0xF061F8FF,
            0xFFF0612A, 0x3C904061, 0xC808F0AF, 0x61CA088F, 0xE061C908,
            0xF37061CB, 0x089F0061, 0x14000000, 0x61150000, 0x00000000,
            0x61FEFFFF, 0xF061F900, 0x38C0612B, 0x3BF3D261, 0xCC08F80F,
            0x00000000, 0x0061CD08, 0xFFE00000, 0x00000061, 0x16000000};

        std::memcpy(&tev.ref().dl, ballShader, sizeof(ballShader));
        tev.SetNumTevStages(7);
    }
    tev.EndEdit();
}

/**
 * @brief Intercepts the bowling ball model after construction to apply patches
 *
 * @param pModel Bowling ball model
 */
void InterceptBwlBallConstruct(RPGrpModelG3D* pModel) {
    ASSERT_PTR(pModel);

    static kiwi::Color color;
    static int numCalls = 0;

    /**
     * Every two calls to this function will be one for the regular model and
     * one for the mirror model.
     *
     * We re-randomize the color after each set of two.
     */
    if (numCalls % 2 == 0) {
        color = kiwi::Color::FromHsv(kiwi::RNG.NextF32(1.0f), 1.0f, 1.0f);
    }

    PatchBwlBallColor(pModel, numCalls % 2 != 0, color);
    numCalls++;
}

/**
 * @brief InterceptBwlBallConstruct common trampoline code
 */
asm void BwlBallCmnTrampoline(...) {
    // clang-format off
    TRAMPOLINE_BEGIN

    // Enable ScnMdl BUFFER_RESTEV buffer option
    ori r7, r7, (1 << 11)

    // RPGrpModelG3D::Construct
    lis r12, 0x8024E630@h
    ori r12, r12, 0x8024E630@l
    mtctr r12
    bctrl
    mr r31, r3

    // Patch the resulting model
    bl InterceptBwlBallConstruct

    mr r0, r31
    TRAMPOLINE_END
    mr r3, r0
    blr
    // clang-format on
}

/**
 * @brief Hook all relevant RPGrpModelG3D::Construct calls
 */
KM_CALL(0x804c89e0, BwlBallCmnTrampoline);
KM_CALL(0x804c89fc, BwlBallCmnTrampoline);
KM_CALL(0x804c8a30, BwlBallCmnTrampoline);
KM_CALL(0x804c8a4c, BwlBallCmnTrampoline);

KM_CALL(0x804c9cb0, BwlBallCmnTrampoline);
KM_CALL(0x804c9ccc, BwlBallCmnTrampoline);

KM_CALL(0x804c9f60, BwlBallCmnTrampoline);
KM_CALL(0x804c9f7c, BwlBallCmnTrampoline);
KM_CALL(0x804c9fb0, BwlBallCmnTrampoline);
KM_CALL(0x804c9fcc, BwlBallCmnTrampoline);

} // namespace Cosmetic
} // namespace Bwl
} // namespace AP
