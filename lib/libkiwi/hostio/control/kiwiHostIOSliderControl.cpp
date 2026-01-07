#include <libkiwi.h>

namespace kiwi {
namespace hostio {
namespace detail {

/******************************************************************************
 *
 * SliderControlImpl
 *
 ******************************************************************************/

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
template <typename TValue>
SliderControlImpl<TValue>::SliderControlImpl(const String& rName, u32 id,
                                             ESliderType type, TValue* pValue,
                                             TValue min, TValue max)
    : IControl(IControl::EType_Value, rName, id),
      mSliderType(type),
      mpValue(pValue),
      mMin(min),
      mMax(max) {

    K_ASSERT_PTR(mpValue);
}

/**
 * @brief Generates object info for host client (derived implementation)
 *
 * @param rContext Message context
 */
template <typename TValue>
void SliderControlImpl<TValue>::GenMessageImpl(Context& rContext) {
    K_ASSERT_PTR(mpValue);
    MemStream& rStrm = rContext.GetMessageStream();

    rStrm.Write_u8(mSliderType);
    rStrm.Write_u32(BitCast<u32>(*mpValue));
    rStrm.Write_u32(BitCast<u32>(mMin));
    rStrm.Write_u32(BitCast<u32>(mMax));
}

/**
 * @brief Handles property event from host client
 *
 * @param rEvent Event structure from the host
 */
template <typename TValue>
void SliderControlImpl<TValue>::ListenPropertyEvent(
    const PropertyEvent& rEvent) {

    K_ASSERT_PTR(mpValue);
    *mpValue = BitCast<TValue>(rEvent.value);
}

// Instantiate class templates
template class SliderControlImpl<u32>;
template class SliderControlImpl<s32>;
template class SliderControlImpl<f32>;

} // namespace detail
} // namespace hostio
} // namespace kiwi