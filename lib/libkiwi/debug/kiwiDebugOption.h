#ifndef LIBKIWI_DEBUG_DEBUG_OPTION_H
#define LIBKIWI_DEBUG_DEBUG_OPTION_H
#include <libkiwi/debug/kiwiDebugMenu.h>
#include <libkiwi/k_types.h>

namespace kiwi {
//! @addtogroup libkiwi_debug
//! @{

/**
 * @brief Basic debug menu option
 */
class DebugOptionBase {
public:
    /**
     * @brief Callback function for option selection
     *
     * @param pArg Callback user argument
     * @return Action result
     */
    typedef DebugMenu::EResult (*SelectCallback)(void* pArg);

    /**
     * @brief Option type
     */
    enum EKind {
        EKind_Int,  //!< DebugIntOption
        EKind_Bool, //!< DebugBoolOption
        EKind_Enum, //!< DebugEnumOption
        EKind_Proc, //!< DebugProcOption
    };

public:
    /**
     * @brief Constructor
     *
     * @param rName Option name
     * @param pCallback Select callback (optional)
     * @param pCallbackArg Select callback user argument (optional)
     */
    explicit DebugOptionBase(const String& rName,
                             SelectCallback* pCallback = nullptr,
                             void* pCallbackArg = nullptr)
        : mIsEnabled(true), mName(rName) {}

    /**
     * @brief Destructor
     */
    virtual ~DebugOptionBase() {}

    /**
     * @brief Gets the type of the option
     */
    virtual EKind GetKind() const = 0;

    /**
     * @brief Attempts to cast the option to a different type
     *
     * @tparam TTo Destination type
     * @return Specified option, or nullptr if the cast is not possible
     */
    template <typename TTo> TTo* DynamicCast() const {
        return GetKind() == TTo::GetKindStatic() ? static_cast<TTo*>(this)
                                                 : nullptr;
    }

    /**
     * @brief Increments the option value
     * @return Action result
     */
    virtual DebugMenu::EResult Increment() {
        return DebugMenu::EResult_None;
    }
    /**
     * @brief Decrements the option value
     * @return Action result
     */
    virtual DebugMenu::EResult Decrement() {
        return DebugMenu::EResult_None;
    }

    /**
     * @brief Performs the option selection logic
     * @return Action result
     */
    virtual DebugMenu::EResult Select() {
        return DebugMenu::EResult_None;
    }

    /**
     * @brief Accesses the option name
     */
    const String& GetName() const {
        return mName;
    }
    /**
     * @brief Accesses the option value in string form
     */
    const String& GetValueText() const {
        return mValueText;
    }

    /**
     * @brief Tests whether the option is enabled
     */
    bool IsEnabled() const {
        return mIsEnabled;
    }
    /**
     * @brief Sets whether the option is enabled
     *
     * @param enable Enable status
     */
    void SetEnabled(bool enable);

protected:
    /**
     * @brief Validates the option value
     */
    virtual void Validate() {}

    /**
     * @brief Updates the option value string
     */
    virtual void UpdateString() {}

protected:
    //! Enable option
    bool mIsEnabled;

    //! Option name
    String mName;
    //! Option value
    String mValueText;
};

/**
 * @brief Debug menu option with an integer value
 */
class DebugIntOption : public DebugOptionBase {
public:
    /**
     * @brief Gets the type of the option (static)
     */
    static EKind GetKindStatic() {
        return EKind_Int;
    }

    /**
     * @brief Constructor
     *
     * @param rName Option name
     * @param min Minimum value (inclusive)
     * @param max Maximum value (inclusive)
     * @param initial Initial value (optional)
     */
    DebugIntOption(const String& rName, int min, int max,
                   Optional<int> initial = kiwi::nullopt);

    /**
     * @brief Gets the type of the option
     */
    virtual EKind GetKind() const {
        return GetKindStatic();
    }

    /**
     * @brief Increments the option value
     * @return Action result
     */
    virtual DebugMenu::EResult Increment();
    /**
     * @brief Decrements the option value
     * @return Action result
     */
    virtual DebugMenu::EResult Decrement();

    /**
     * @brief Gets the integer option value
     */
    int GetValue() const {
        return mValue;
    }

    /**
     * @brief Gets the minimum (inclusive) value
     */
    int GetMin() const {
        return mMin;
    }
    /**
     * @brief Sets the minimum (inclusive) value
     * @details The current option value is validated upon range changes.
     *
     * @param min New minimum value (inclusive)
     */
    void SetMin(int min);

    /**
     * @brief Accesses the maximum value (inclusive)
     */
    int GetMax() const {
        return mMax;
    }
    /**
     * @brief Sets the maximum (inclusive) value
     * @details The current option value is validated upon range changes.
     *
     * @param max New maximum value (inclusive)
     */
    void SetMax(int max);

    /**
     * @brief Sets the range (inclusive) of acceptable values
     * @details The current option value is validated upon range changes.
     *
     * @param min New minimum value (inclusive)
     * @param max New maximum value (inclusive)
     */
    void SetRange(int min, int max);

protected:
    /**
     * @brief Validates the option value
     */
    virtual void Validate();

    /**
     * @brief Updates the option value string
     */
    virtual void UpdateString();

private:
    /**
     * @brief Sets the integer option value
     *
     * @param value New value
     */
    void SetValue(int value);

private:
    //! Minimum value
    int mMin;
    //! Maximum value
    int mMax;

    //! Current value
    int mValue;
};

/**
 * @brief Debug option with a boolean value
 */
class DebugBoolOption : public DebugIntOption {
public:
    /**
     * @brief Gets the type of the option (static)
     */
    static EKind GetKindStatic() {
        return EKind_Bool;
    }

    /**
     * @brief Constructor
     *
     * @param rName Option name
     * @param initial Initial value (optional)
     */
    explicit DebugBoolOption(const String& rName, bool initial = false)
        : DebugIntOption(rName, static_cast<int>(false), static_cast<int>(true),
                         static_cast<int>(initial)) {

        UpdateString();
    }

    /**
     * @brief Gets the type of the option
     */
    virtual EKind GetKind() const {
        return GetKindStatic();
    }

protected:
    /**
     * @brief Updates the option value string
     */
    virtual void UpdateString();
};

/**
 * @brief Debug option with an enum value
 */
class DebugEnumOption : public DebugIntOption {
public:
    /**
     * @brief Gets the type of the option (static)
     */
    static EKind GetKindStatic() {
        return EKind_Enum;
    }

    /**
     * @brief Constructor
     *
     * @param rName Option name
     * @param ppValues Enum value strings
     * @param min Minimum value (inclusive)
     * @param max Maximum value (inclusive)
     * @param initial Initial value (optional)
     */
    DebugEnumOption(const String& rName, const char** ppValues, int min,
                    int max, Optional<int> initial = kiwi::nullopt)
        : DebugIntOption(rName, min, max, initial), mppValues(ppValues) {

        ASSERT(ppValues != nullptr);

        UpdateString();
    }

    /**
     * @brief Gets the type of the option
     */
    virtual EKind GetKind() const {
        return GetKindStatic();
    }

    /**
     * @brief Gets the option enum value strings
     */
    const char** GetEnumValues() const {
        return mppValues;
    }
    /**
     * @brief Sets the option enum value strings
     *
     * @param ppValues Enum value strings
     */
    void SetEnumValues(const char** ppValues);

protected:
    /**
     * @brief Updates the option value string
     */
    virtual void UpdateString();

private:
    //! Enum value strings
    const char** mppValues;
};

/**
 * @brief Debug option with procedure
 */
class DebugProcOption : public DebugOptionBase {
public:
    /**
     * @brief Gets the type of the option (static)
     */
    static EKind GetKindStatic() {
        return EKind_Proc;
    }

    /**
     * @brief Constructor
     *
     * @param rName Option name
     * @param pCallback Select callback function
     * @param pCallbackArg Select callback user argument
     */
    DebugProcOption(const String& rName, SelectCallback* pCallback,
                    void* pCallbackArg = nullptr)
        : DebugOptionBase(rName, pCallback, pCallbackArg) {}

    /**
     * @brief Gets the type of the option
     */
    virtual EKind GetKind() const {
        return GetKindStatic();
    }

    /**
     * @brief Performs the option selection logic
     * @return Action result
     */
    virtual DebugMenu::EResult Select();

private:
    //! Select procedure
    SelectCallback mpCallback;
    //! Select procedure user argument
    void* mpCallbackArg;
};

//! @}
} // namespace kiwi

#endif
