#include <libkiwi.h>

namespace kiwi {

/******************************************************************************
 *
 * DebugOptionBase
 *
 ******************************************************************************/

/**
 * @brief Sets whether the option is enabled
 *
 * @param enable Enable status
 */
void DebugOptionBase::SetEnabled(bool enable) {
    mIsEnabled = enable;
    UpdateString();
}

/******************************************************************************
 *
 * DebugIntOption
 *
 ******************************************************************************/

/**
 * @brief Constructor
 *
 * @param rName Option name
 * @param min Minimum value (inclusive)
 * @param max Maximum value (inclusive)
 * @param initial Initial value (optional)
 */
DebugIntOption::DebugIntOption(const String& rName, int min, int max,
                               Optional<int> initial)
    : DebugOptionBase(rName), mMin(min), mMax(max) {

    K_ASSERT(max >= min);

    // Initial value defaults to minimum
    SetValue(initial ? *initial : min);
}

/**
 * @brief Increments the option value
 * @return Action result
 */
DebugMenu::EResult DebugIntOption::Increment() {
    if (!IsEnabled()) {
        return DebugMenu::EResult_Invalid;
    }

    // Value wraps around
    SetValue(mValue == mMax ? mMin : mValue + 1);
    return DebugMenu::EResult_Change;
}

/**
 * @brief Decrements the option value
 * @return Action result
 */
DebugMenu::EResult DebugIntOption::Decrement() {
    if (!IsEnabled()) {
        return DebugMenu::EResult_Invalid;
    }

    // Value wraps around
    SetValue(mValue == mMin ? mMax : mValue - 1);
    return DebugMenu::EResult_Change;
}

/**
 * @brief Sets the maximum value (inclusive)
 * @details The current option value is validated upon range changes.
 *
 * @param max New maximum value (inclusive)
 */
void DebugIntOption::SetMax(int max) {
    K_ASSERT(max >= mMin);

    mMax = max;
    Validate();
}

/**
 * @brief Sets the minimum value (inclusive)
 * @details The current option value is validated upon range changes.
 *
 * @param min New minimum value (inclusive)
 */
void DebugIntOption::SetMin(int min) {
    K_ASSERT(min <= mMax);

    mMin = min;
    Validate();
}

/**
 * @brief Sets the range (inclusive) of acceptable values
 * @details The current option value is validated upon range changes.
 *
 * @param min New minimum value (inclusive)
 * @param max New maximum value (inclusive)
 */
void DebugIntOption::SetRange(int min, int max) {
    K_ASSERT(max >= min);

    mMin = min;
    mMax = max;
    Validate();
}

/**
 * @brief Validates the option value
 */
void DebugIntOption::Validate() {
    if (mValue > mMax) {
        SetValue(mMax);
    } else if (mValue < mMin) {
        SetValue(mMin);
    }
}

/**
 * @brief Updates the option value string
 */
void DebugIntOption::UpdateString() {
    if (IsEnabled()) {
        mValueText = kiwi::ToString(mValue);
    } else {
        mValueText = "DISABLED";
    }
}

/**
 * @brief Sets the integer option value
 *
 * @param value New value
 */
void DebugIntOption::SetValue(int value) {
    mValue = Clamp(mValue, mMin, mMax);
    UpdateString();
}

/******************************************************************************
 *
 * DebugBoolOption
 *
 ******************************************************************************/

/**
 * @brief Updates the option value string
 */
void DebugBoolOption::UpdateString() {
    if (IsEnabled()) {
        mValueText = GetValue() ? "True" : "False";
    } else {
        mValueText = "DISABLED";
    }
}

/******************************************************************************
 *
 * DebugEnumOption
 *
 ******************************************************************************/

/**
 * @brief Sets the option enum value strings
 *
 * @param ppValues Enum value strings
 */
void DebugEnumOption::SetEnumValues(const char** ppValues) {
    K_ASSERT(ppValues != nullptr);

    mppValues = ppValues;
    UpdateString();
}

/**
 * @brief Updates the option value string
 */
void DebugEnumOption::UpdateString() {
    K_ASSERT(mppValues != nullptr);

    if (IsEnabled()) {
        mValueText = mppValues[GetValue()];
    } else {
        mValueText = "DISABLED";
    }
}

/******************************************************************************
 *
 * DebugProcOption
 *
 ******************************************************************************/

/**
 * @brief Performs the option selection logic
 * @return Action result
 */
DebugMenu::EResult DebugProcOption::Select() {
    if (!IsEnabled()) {
        return DebugMenu::EResult_Invalid;
    }

    if (mpCallback != nullptr) {
        return mpCallback(mpCallbackArg);
    }

    return DebugMenu::EResult_None;
}

} // namespace kiwi
