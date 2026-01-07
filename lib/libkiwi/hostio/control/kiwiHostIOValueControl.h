#ifndef LIBKIWI_HOSTIO_HOST_IO_VALUE_CONTROL_H
#define LIBKIWI_HOSTIO_HOST_IO_VALUE_CONTROL_H
#include <libkiwi/hostio/kiwiHostIOIControl.h>
#include <libkiwi/k_types.h>
#include <libkiwi/prim/kiwiOptional.h>
#include <libkiwi/prim/kiwiString.h>

namespace kiwi {
//! @addtogroup libkiwi_hostio
//! @{
namespace hostio {
//! @addtogroup libkiwi_hostio
//! @{

/******************************************************************************
 *
 * ValueControlImpl
 *
 ******************************************************************************/
namespace detail {
//! @addtogroup libkiwi_hostio
//! @{

/**
 * @brief Value UI control
 *
 * @tparam TValue Property value type
 */
template <typename TValue> class ValueControlImpl : public IControl {
public:
    /**
     * @brief Value control type
     */
    enum EValueType {
        EValueType_U32, //!< Unsigned 32-bit value
        EValueType_S32, //!< Signed 32-bit value
        EValueType_F32, //!< Floating point value

        EValueType_Max
    };

public:
    /**
     * @brief Constructor
     *
     * @param rName Name
     * @param id Unique ID
     * @param type Value control type
     * @param pValue Value storage
     * @param min Minimum value (inclusive)
     * @param max Maximum value (inclusive)
     */
    ValueControlImpl(const String& rName, u32 id, EValueType type,
                     TValue* pValue, TValue min, TValue max);

    /**
     * @brief Destructor
     */
    virtual ~ValueControlImpl() {}

    /**
     * @brief Handles property event from host client
     *
     * @param rEvent Event structure from the host
     */
    virtual void ListenPropertyEvent(const PropertyEvent& rEvent);

private:
    /**
     * @brief Generates object info for host client (derived implementation)
     *
     * @param rContext Message context
     */
    virtual void GenMessageImpl(Context& rContext);

private:
    //! Value control type
    EValueType mValueType;

    //! Value storage
    TValue* mpValue;

    //! Minimum value
    TValue mMin;
    //! Maximum value
    TValue mMax;
};

//! @}
} // namespace detail

/******************************************************************************
 *
 * ValueControlU32
 *
 ******************************************************************************/

/**
 * @brief Value UI control
 *
 * @tparam TValue Property value type
 */
class ValueControlU32 : public detail::ValueControlImpl<u32> {
public:
    /**
     * @brief Constructor
     *
     * @param rName Name
     * @param id Unique ID
     * @param pValue Value storage
     * @param min Minimum value (inclusive)
     * @param max Maximum value (inclusive)
     */
    ValueControlU32(const String& rName, u32 id, u32* pValue, u32 min, u32 max)
        : ValueControlImpl<u32>(rName, id, EValueType_U32, pValue, min, max) {}

    /**
     * @brief Destructor
     */
    virtual ~ValueControlU32() {}
};

/******************************************************************************
 *
 * ValueControlS32
 *
 ******************************************************************************/

/**
 * @brief Value UI control
 *
 * @tparam TValue Property value type
 */
class ValueControlS32 : public detail::ValueControlImpl<s32> {
public:
    /**
     * @brief Constructor
     *
     * @param rName Name
     * @param id Unique ID
     * @param pValue Value storage
     * @param min Minimum value (inclusive)
     * @param max Maximum value (inclusive)
     */
    ValueControlS32(const String& rName, u32 id, s32* pValue, s32 min, s32 max)
        : ValueControlImpl<s32>(rName, id, EValueType_S32, pValue, min, max) {}

    /**
     * @brief Destructor
     */
    virtual ~ValueControlS32() {}
};

/******************************************************************************
 *
 * ValueControlF32
 *
 ******************************************************************************/

/**
 * @brief Value UI control
 *
 * @tparam TValue Property value type
 */
class ValueControlF32 : public detail::ValueControlImpl<f32> {
public:
    /**
     * @brief Constructor
     *
     * @param rName Name
     * @param id Unique ID
     * @param pValue Value storage
     * @param min Minimum value (inclusive)
     * @param max Maximum value (inclusive)
     */
    ValueControlF32(const String& rName, u32 id, f32* pValue, f32 min, f32 max)
        : ValueControlImpl<f32>(rName, id, EValueType_F32, pValue, min, max) {}

    /**
     * @brief Destructor
     */
    virtual ~ValueControlF32() {}
};

//! @}
} // namespace hostio
//! @}
} // namespace kiwi

#endif
