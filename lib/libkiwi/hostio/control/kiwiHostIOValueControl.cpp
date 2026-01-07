#include <libkiwi.h>

namespace kiwi {
namespace hostio {
namespace detail {

/******************************************************************************
 *
 * ValueControlImpl
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
ValueControlImpl<TValue>::ValueControlImpl(const String& rName, u32 id,
                                           EValueType type, TValue* pValue,
                                           TValue min, TValue max)
    : IControl(IControl::EType_Value, rName, id),
      mValueType(type),
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
void ValueControlImpl<TValue>::GenMessageImpl(Context& rContext) {
    K_ASSERT_PTR(mpValue);
    MemStream& rStrm = rContext.GetMessageStream();

    rStrm.Write_u8(GetType());
    rStrm.Write_string(GetName());
    rStrm.Write_u32(GetID());

    rStrm.Write_u8(mValueType);
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
void ValueControlImpl<TValue>::ListenPropertyEvent(
    const PropertyEvent& rEvent) {

    K_ASSERT_PTR(mpValue);
    *mpValue = BitCast<TValue>(rEvent.value);
}

// Instantiate class templates
template class ValueControlImpl<u32>;
template class ValueControlImpl<s32>;
template class ValueControlImpl<f32>;

} // namespace detail
} // namespace hostio
} // namespace kiwi