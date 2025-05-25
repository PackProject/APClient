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
    typedef EDebugMenuResult (*SelectCallback)(void* pArg);

    /**
     * @brief Option type
     */
    enum EKind {
        EKind_Int,      //!< DebugIntOption
        EKind_Bool,     //!< DebugBoolOption
        EKind_Enum,     //!< DebugEnumOption
        EKind_Proc,     //!< DebugProcOption
        EKind_OpenPage, //!< DebugOpenPageOption
    };

public:
    /**
     * @brief Constructor
     *
     * @param rMenu Parent menu
     * @param rName Option name
     */
    DebugOptionBase(DebugMenu& rMenu, const String& rName)
        : mrMenu(rMenu), mIsEnabled(true), mName(rName) {}

    /**
     * @brief Destructor
     */
    virtual ~DebugOptionBase() {}

    /**
     * @brief Gets the option's parent menu
     */
    DebugMenu& GetMenu() const {
        return mrMenu;
    }

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
    virtual EDebugMenuResult Increment() {
        return EDebugMenuResult_None;
    }
    /**
     * @brief Decrements the option value
     * @return Action result
     */
    virtual EDebugMenuResult Decrement() {
        return EDebugMenuResult_None;
    }

    /**
     * @brief Performs the option selection logic
     * @return Action result
     */
    virtual EDebugMenuResult Select() {
        return EDebugMenuResult_None;
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
    //! Parent menu
    DebugMenu& mrMenu;

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
     * @param rMenu Parent menu
     * @param rName Option name
     * @param min Minimum value (inclusive)
     * @param max Maximum value (inclusive)
     * @param initial Initial value (optional)
     */
    DebugIntOption(DebugMenu& rMenu, const String& rName, int min, int max,
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
    virtual EDebugMenuResult Increment();
    /**
     * @brief Decrements the option value
     * @return Action result
     */
    virtual EDebugMenuResult Decrement();

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
     * @param rMenu Parent menu
     * @param rName Option name
     * @param initial Initial value (optional)
     */
    DebugBoolOption(DebugMenu& rMenu, const String& rName, bool initial = false)
        : DebugIntOption(rMenu, rName, static_cast<int>(false),
                         static_cast<int>(true), static_cast<int>(initial)) {

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
     * @param rMenu Parent menu
     * @param rName Option name
     * @param ppValues Enum value strings
     * @param min Minimum value (inclusive)
     * @param max Maximum value (inclusive)
     * @param initial Initial value (optional)
     */
    DebugEnumOption(DebugMenu& rMenu, const String& rName,
                    const char** ppValues, int min, int max,
                    Optional<int> initial = kiwi::nullopt)
        : DebugIntOption(rMenu, rName, min, max, initial), mppValues(ppValues) {

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
     * @param rMenu Parent menu
     * @param rName Option name
     * @param pCallback Select callback function
     * @param pCallbackArg Select callback user argument
     */
    DebugProcOption(DebugMenu& rMenu, const String& rName,
                    SelectCallback pCallback, void* pCallbackArg = nullptr)
        : DebugOptionBase(rMenu, rName),
          mpCallback(pCallback),
          mpCallbackArg(pCallbackArg) {}

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
    virtual EDebugMenuResult Select();

private:
    //! Select procedure
    SelectCallback mpCallback;
    //! Select procedure user argument
    void* mpCallbackArg;
};

/**
 * @brief Debug option which opens a new page
 */
class DebugOpenPageOption : public DebugProcOption {
public:
    /**
     * @brief Gets the type of the option (static)
     */
    static EKind GetKindStatic() {
        return EKind_OpenPage;
    }

    /**
     * @brief Constructor
     *
     * @param rMenu Parent menu
     * @param rName Option name
     * @param rOpenPage Sub-page to open
     */
    DebugOpenPageOption(DebugMenu& rMenu, const String& rName,
                        DebugPage& rOpenPage)
        : DebugProcOption(rMenu, rName, OpenPageProc, this) {

        mpOpenPage = &rOpenPage;
    }

    /**
     * @brief Gets the type of the option
     */
    virtual EKind GetKind() const {
        return GetKindStatic();
    }

private:
    /**
     * @brief Opens the specified sub-page
     *
     * @param pArg Callback user argument
     */
    static EDebugMenuResult OpenPageProc(void* pArg);

private:
    //! Sub-page to open
    DebugPage* mpOpenPage;
};

//! @}
} // namespace kiwi

#endif
