#ifndef LIBKIWI_UTIL_MODEL_UTIL_H
#define LIBKIWI_UTIL_MODEL_UTIL_H
#include <Pack/RPGraphics.h>
#include <libkiwi/k_types.h>
#include <libkiwi/prim/kiwiString.h>

namespace kiwi {
//! @addtogroup libkiwi_util
//! @{

/**
 * @brief Model utilities
 */
class ModelUtil {
public:
    /**
     * @brief Gets a model's material by name
     *
     * @param pModel Model
     * @param rName G3D material name
     * @return RP engine material, or nullptr if not found
     */
    static RPGrpModelMaterial* GetModelMaterial(RPGrpModel* pModel,
                                                const String& rName);
};

//! @}
} // namespace kiwi

#endif
