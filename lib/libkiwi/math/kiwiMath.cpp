#include <libkiwi.h>

#include <nw4r/math.h>

#include <cmath>
#include <limits>

namespace kiwi {
namespace detail {

/******************************************************************************
 *
 * Constants
 *
 ******************************************************************************/

/**
 * @brief pi
 */
template <typename T> const T TMath<T>::PI = 3.14159265358979323846;

/**
 * @brief 2pi (tau)
 */
template <typename T> const T TMath<T>::TWO_PI = 2 * PI;

/**
 * @brief pi/2
 */
template <typename T> const T TMath<T>::PI_HALF = PI / 2;

/**
 * @brief pi/4
 */
template <typename T> const T TMath<T>::PI_QUARTER = PI / 4;

/**
 * @brief ln(2)
 */
template <typename T> const T TMath<T>::LN2 = 0;

/**
 * @brief 1/ln(2)
 */
template <typename T> const T TMath<T>::LN2_INV = 0;

/******************************************************************************
 *
 * Common implementation
 *
 ******************************************************************************/

/**
 * @brief Calculates the absolute value of the input value
 *
 * @param x Input value
 */
template <typename T> T TMath<T>::Abs(T x) {
    return x < 0 ? Neg(x) : x;
}

/**
 * @brief Inverts the input value
 *
 * @param x Input value
 */
template <typename T> T TMath<T>::Inv(T x) {
    return One() / x;
}

/**
 * @brief Calculates the square root of the input value
 *
 * @param x Input value
 */
template <typename T> T TMath<T>::Sqrt(T x) {
    return nw4r::math::FSqrt(static_cast<f32>(x));
}

/**
 * @brief Calculates a power of the input value
 *
 * @param base Base value
 * @param exp Exponent
 */
template <typename T> T TMath<T>::Pow(T base, T exp) {
    f64 result = std::pow(static_cast<f64>(base), static_cast<f64>(exp));
    return static_cast<T>(result);
}

/**
 * @brief Calculates the sine of the input angle, in degrees
 *
 * @param x Input angle
 */
template <typename T> T TMath<T>::SinDeg(T x) {
    f32 result = nw4r::math::SinDeg(static_cast<f32>(x));
    return static_cast<T>(result);
}

/**
 * @brief Calculates the cosine of the input angle, in degrees
 *
 * @param x Input angle
 */
template <typename T> T TMath<T>::CosDeg(T x) {
    f32 result = nw4r::math::CosDeg(static_cast<f32>(x));
    return static_cast<T>(result);
}

/**
 * @brief Calculates the tangent of the input angle, in degrees
 *
 * @param x Input angle
 */
template <typename T> T TMath<T>::TanDeg(T x) {
    f32 result = nw4r::math::TanDeg(static_cast<f32>(x));
    return static_cast<T>(result);
}

/**
 * @brief Calculates the sine of the input angle, in radians
 *
 * @param x Input angle
 */
template <typename T> T TMath<T>::SinRad(T x) {
    f32 result = nw4r::math::SinRad(static_cast<f32>(x));
    return static_cast<T>(result);
}

/**
 * @brief Calculates the cosine of the input angle, in radians
 *
 * @param x Input angle
 */
template <typename T> T TMath<T>::CosRad(T x) {
    f32 result = nw4r::math::CosRad(static_cast<f32>(x));
    return static_cast<T>(result);
}

/**
 * @brief Calculates the tangent of the input angle, in radians
 *
 * @param x Input angle
 */
template <typename T> T TMath<T>::TanRad(T x) {
    f32 result = nw4r::math::TanRad(static_cast<f32>(x));
    return static_cast<T>(result);
}

/******************************************************************************
 *
 * Mathi (s32)
 *
 ******************************************************************************/

/**
 * @brief Represents the smallest possible value
 */
template <> s32 TMath<s32>::MinNumber() {
    return 0x80000000;
}

/**
 * @brief Represents the largest possible value
 */
template <> s32 TMath<s32>::MaxNumber() {
    return 0x7FFFFFFF;
}

/**
 * @brief Represents the numerical constant Infinity
 */
template <> s32 TMath<s32>::Inf() {
    K_NOT_IMPLEMENTED();
    return 0;
}

/**
 * @brief Represents a Quiet NaN
 */
template <> s32 TMath<s32>::QNaN() {
    K_NOT_IMPLEMENTED();
    return 0;
}

/**
 * @brief Represents a Signaling NaN
 */
template <> s32 TMath<s32>::SNaN() {
    K_NOT_IMPLEMENTED();
    return 0;
}

/**
 * @brief Represents the smallest difference between representable values
 */
template <> s32 TMath<s32>::Epsilon() {
    K_NOT_IMPLEMENTED();
    return 0;
}

/******************************************************************************
 *
 * Mathu (u32)
 *
 ******************************************************************************/

/**
 * @brief Represents the smallest possible value
 */
template <> u32 TMath<u32>::MinNumber() {
    return 0;
}

/**
 * @brief Represents the largest possible value
 */
template <> u32 TMath<u32>::MaxNumber() {
    return 0xFFFFFFFF;
}

/**
 * @brief Represents the numerical constant Infinity
 */
template <> u32 TMath<u32>::Inf() {
    K_NOT_IMPLEMENTED();
    return 0;
}

/**
 * @brief Represents a Quiet NaN
 */
template <> u32 TMath<u32>::QNaN() {
    K_NOT_IMPLEMENTED();
    return 0;
}

/**
 * @brief Represents a Signaling NaN
 */
template <> u32 TMath<u32>::SNaN() {
    K_NOT_IMPLEMENTED();
    return 0;
}

/**
 * @brief Represents the smallest difference between representable values
 */
template <> u32 TMath<u32>::Epsilon() {
    K_NOT_IMPLEMENTED();
    return 0;
}

/******************************************************************************
 *
 * Mathf (f32)
 *
 ******************************************************************************/

/**
 * @brief Represents the smallest possible value
 */
template <> f32 TMath<f32>::MinNumber() {
    return 1.17549435082228750797e-38f;
}

/**
 * @brief Represents the largest possible value
 */
template <> f32 TMath<f32>::MaxNumber() {
    return 3.40282346638528859812e+38f;
}

/**
 * @brief Represents the numerical constant Infinity
 */
template <> f32 TMath<f32>::Inf() {
    return BitCast<f32>(0x7FF00000);
}

/**
 * @brief Represents a Quiet NaN
 */
template <> f32 TMath<f32>::QNaN() {
    return BitCast<f32>(0x7FC00000);
}

/**
 * @brief Represents a Signaling NaN
 */
template <> f32 TMath<f32>::SNaN() {
    return BitCast<f32>(0x7FF00000);
}

/**
 * @brief Represents the smallest difference between representable values
 */
template <> f32 TMath<f32>::Epsilon() {
    return 1.1920928955078125e-07f;
}

/**
 * @brief Inverts the input value
 *
 * @param x Input value
 */
template <> f32 TMath<f32>::Inv(f32 x) {
    return nw4r::math::FInv(x);
}

/**
 * @brief Calculates the absolute value of the input value
 *
 * @param x Input value
 */
template <> f32 TMath<f32>::Abs(f32 x) {
    return nw4r::math::FAbs(x);
}

/******************************************************************************
 *
 * Mathd (f64)
 *
 ******************************************************************************/

/**
 * @brief Represents the smallest possible value
 */
template <> f64 TMath<f64>::MinNumber() {
    return 2.22507385850720138309e-308l;
}

/**
 * @brief Represents the largest possible value
 */
template <> f64 TMath<f64>::MaxNumber() {
    return 1.79769313486231570815e+308l;
}

/**
 * @brief Represents the numerical constant Infinity
 */
template <> f64 TMath<f64>::Inf() {
    return BitCast<f64>(0x7FF0000000000000);
}

/**
 * @brief Represents a Quiet NaN
 */
template <> f64 TMath<f64>::QNaN() {
    return BitCast<f64>(0x7FC0000000000000);
}

/**
 * @brief Represents a Signaling NaN
 */
template <> f64 TMath<f64>::SNaN() {
    return BitCast<f64>(0x7FF0000000000000);
}

/**
 * @brief Represents the smallest difference between representable values
 */
template <> f64 TMath<f64>::Epsilon() {
    return 2.22044604925031308085e-16l;
}

/******************************************************************************
 *
 * Instantiate class templates
 *
 ******************************************************************************/

template class TMath<s32>;
template class TMath<u32>;
template class TMath<f32>;
template class TMath<f64>;

} // namespace detail
} // namespace kiwi