#include <libkiwi.h>

namespace kiwi {

/**
 * @brief Sets the value of a static variable
 *
 * @param index Variable index
 * @param value Variable value
 */
void StaticMem::SetVariable(u32 index, u32 value) {
    K_ASSERT(index < NUM_VARIABLE);
    mVariables[index] = value;
}

/**
 * @brief Clears the value of a static variable
 *
 * @param index Variable index
 */
void StaticMem::ClearVariable(u32 index) {
    K_ASSERT(index < NUM_VARIABLE);
    mVariables[index].Reset();
}

/**
 * @brief Gets the value of a static variable
 *
 * @param index Variable index
 */
Optional<u32> StaticMem::GetVariable(u32 index) const {
    K_ASSERT(index < NUM_VARIABLE);
    return mVariables[index];
}

/**
 * @brief Tests whether a static variable has been set
 *
 * @param index Variable index
 * @return Whether it has been given a value
 */
bool StaticMem::IsVariableSet(u32 index) const {
    K_ASSERT(index < NUM_VARIABLE);
    return mVariables[index].HasValue();
}

} // namespace kiwi