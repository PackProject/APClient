#include <nw4r/g3d.h>

#include <libkiwi.h>

#include <egg/gfx.h>

namespace kiwi {

/**
 * @brief Gets a model's material by name
 *
 * @param pModel Model
 * @param rName G3D material name
 * @return RP engine material, or nullptr if not found
 */
RPGrpModelMaterial* ModelUtil::GetModelMaterial(RPGrpModel* pModel,
                                                const String& rName) {

    ASSERT_PTR(pModel);

    EGG::ModelEx* pModelEx = pModel->GetModelEx();
    ASSERT_PTR(pModelEx);

    nw4r::g3d::ScnMdlSimple* pScnMdlSimple = pModelEx->getScnMdlSimple();
    ASSERT_PTR_EX(pScnMdlSimple, "This model is not a ScnMdl");

    nw4r::g3d::ResMdl resMdl = pScnMdlSimple->GetResMdl();
    ASSERT(resMdl.IsValid());

    nw4r::g3d::ResMat resMat = resMdl.GetResMat(rName);
    ASSERT_EX(resMat.IsValid(), "Cannot find material: %s", rName.CStr());

    return pModel->GetMaterial(resMat.GetID());
}

} // namespace kiwi