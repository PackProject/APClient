#ifndef LIBKIWI_CORE_STATIC_MEM_H
#define LIBKIWI_CORE_STATIC_MEM_H
#include <libkiwi/core/kiwiSceneHookMgr.h>
#include <libkiwi/k_types.h>
#include <libkiwi/prim/kiwiOptional.h>
#include <libkiwi/util/kiwiStaticSingleton.h>

namespace kiwi {
//! @addtogroup libkiwi_core
//! @{

/**
 * @brief Static-lifetime variable storage
 */
class StaticMem : public StaticSingleton<StaticMem> {
    friend class StaticSingleton<StaticMem>;

public:
    //! Number of static variables
    static const u32 NUM_VARIABLE = 256;

public:
    /**
     * @brief Sets the value of a static variable
     *
     * @param index Variable index
     * @param value Variable value
     */
    void SetVariable(u32 index, u32 value);

    /**
     * @brief Clears the value of a static variable
     *
     * @param index Variable index
     */
    void ClearVariable(u32 index);

    /**
     * @brief Gets the value of a static variable
     *
     * @param index Variable index
     */
    Optional<u32> GetVariable(u32 index) const;

    /**
     * @brief Tests whether a static variable has been set
     *
     * @param index Variable index
     * @return Whether it has been given a value
     */
    bool IsVariableSet(u32 index) const;

private:
    //! Static variables
    Optional<u32> mVariables[NUM_VARIABLE];
};

//! @}
} // namespace kiwi

#endif
