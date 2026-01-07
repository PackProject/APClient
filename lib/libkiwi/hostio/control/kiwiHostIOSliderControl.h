#ifndef LIBKIWI_HOSTIO_HOST_IO_SLIDER_CONTROL_H
#define LIBKIWI_HOSTIO_HOST_IO_SLIDER_CONTROL_H
#include <libkiwi/hostio/kiwiHostIOIControl.h>
#include <libkiwi/k_types.h>
#include <libkiwi/prim/kiwiString.h>

namespace kiwi {
//! @addtogroup libkiwi_hostio
//! @{
namespace hostio {
//! @addtogroup libkiwi_hostio
//! @{

/******************************************************************************
 *
 * SliderControlImpl
 *
 ******************************************************************************/
namespace detail {
//! @addtogroup libkiwi_hostio
//! @{

/**
 * @brief Slider UI control
 *
 * @tparam TValue Property value type
 */
template <typename TValue> class SliderControlImpl : public IControl {
public:
    /**
     * @brief Slider control type
     */
    enum ESliderType {
        ESliderType_U32, //!< Unsigned 32-bit value
        ESliderType_S32, //!< Signed 32-bit value
        ESliderType_F32, //!< Floating point value

        ESliderType_Max
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
    SliderControlImpl(const String& rName, u32 id, ESliderType type,
                      TValue* pValue, TValue min, TValue max);

    /**
     * @brief Destructor
     */
    virtual ~SliderControlImpl() {}

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
    //! Slider control type
    ESliderType mSliderType;

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
 * SliderControlU32
 *
 ******************************************************************************/

/**
 * @brief Slider UI control
 *
 * @tparam TValue Property value type
 */
class SliderControlU32 : public detail::SliderControlImpl<u32> {
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
    SliderControlU32(const String& rName, u32 id, u32* pValue, u32 min, u32 max)
        : SliderControlImpl<u32>(rName, id, ESliderType_U32, pValue, min, max) {
    }

    /**
     * @brief Destructor
     */
    virtual ~SliderControlU32() {}
};

/******************************************************************************
 *
 * SliderControlS32
 *
 ******************************************************************************/

/**
 * @brief Slider UI control
 *
 * @tparam TValue Property value type
 */
class SliderControlS32 : public detail::SliderControlImpl<s32> {
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
    SliderControlS32(const String& rName, u32 id, s32* pValue, s32 min, s32 max)
        : SliderControlImpl<s32>(rName, id, ESliderType_S32, pValue, min, max) {
    }

    /**
     * @brief Destructor
     */
    virtual ~SliderControlS32() {}
};

/******************************************************************************
 *
 * SliderControlF32
 *
 ******************************************************************************/

/**
 * @brief Slider UI control
 *
 * @tparam TValue Property value type
 */
class SliderControlF32 : public detail::SliderControlImpl<f32> {
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
    SliderControlF32(const String& rName, u32 id, f32* pValue, f32 min, f32 max)
        : SliderControlImpl<f32>(rName, id, ESliderType_F32, pValue, min, max) {
    }

    /**
     * @brief Destructor
     */
    virtual ~SliderControlF32() {}
};

//! @}
} // namespace hostio
//! @}
} // namespace kiwi

#endif
