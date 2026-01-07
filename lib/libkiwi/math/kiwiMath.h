#ifndef LIBKIWI_MATH_MATH_H
#define LIBKIWI_MATH_MATH_H
#include <libkiwi/k_types.h>

namespace kiwi {
//! @addtogroup libkiwi_math
//! @{

namespace detail {
//! @addtogroup libkiwi_math
//! @{

/**
 * @brief Primitive math utilities
 *
 * @tparam T Operand type
 */
template <typename T> class TMath {
public:
    /**
     * @name Constants
     */
    /**@{*/
    /**
     * @brief Represents the numerical constant zero
     */
    static T Zero() {
        return static_cast<T>(0);
    }
    /**
     * @brief Represents the numerical constant one
     */
    static T One() {
        return static_cast<T>(1);
    }

    /**
     * @brief Represents the numerical constant pi
     */
    static T Pi() {
        return PI;
    }
    /**
     * @brief Represents the numerical constant 2pi
     */
    static T TwoPi() {
        return TWO_PI;
    }
    /**
     * @brief Represents the numerical constant Tau (2pi)
     */
    static T Tau() {
        return TWO_PI;
    }

    /**
     * @brief Represents the numerical constant pi/2
     */
    static T PiHalf() {
        return PI_HALF;
    }
    /**
     * @brief Represents the numerical constant pi/4
     */
    static T PiQuart() {
        return PI_QUARTER;
    }

    /**
     * @brief Represents the numerical constant ln(2)
     */
    static T Ln2() {
        return LN2;
    }
    /**
     * @brief Represents the numerical constant 1/ln(2)
     */
    static T Ln2Inv() {
        return LN2_INV;
    }

    /**
     * @brief Represents the smallest possible value
     */
    static T MinNumber();
    /**
     * @brief Represents the largest possible value
     */
    static T MaxNumber();

    /**
     * @brief Represents the numerical constant Infinity
     */
    static T Inf();
    /**
     * @brief Represents a Quiet NaN
     */
    static T QNaN();
    /**
     * @brief Represents a Signaling NaN
     */
    static T SNaN();

    /**
     * @brief Represents the smallest difference between representable values
     */
    static T Epsilon();
    /**@}*/

    /**
     * @name Basic operations
     */
    /**@{*/
    /**
     * @brief Calculates the sign of the input value
     *
     * @param x Input value
     */
    static T Sign(T x) {
        return x < 0 ? -1 : 1;
    }

    /**
     * @brief Calculates the absolute value of the input value
     *
     * @param x Input value
     */
    static T Abs(T x);

    /**
     * @brief Negates the input value
     *
     * @param x Input value
     */
    static T Neg(T x) {
        return -x;
    }

    /**
     * @brief Inverts the input value
     *
     * @param x Input value
     */
    static T Inv(T x);
    /**@}*/

    /**
     * @name Power functions
     */
    /**@{*/
    /**
     * @brief Calculates the square root of the input value
     *
     * @param x Input value
     */
    static T Sqrt(T x);

    /**
     * @brief Calculates a power of the input value
     *
     * @param base Base value
     * @param exp Exponent
     */
    static T Pow(T base, T exp);
    /**@}*/

    /**
     * @name Trigonometric functions
     */
    /**@{*/
    /**
     * @brief Calculates the sine of the input angle, in degrees
     *
     * @param x Input angle
     */
    static T SinDeg(T x);
    /**
     * @brief Calculates the cosine of the input angle, in degrees
     *
     * @param x Input angle
     */
    static T CosDeg(T x);
    /**
     * @brief Calculates the tangent of the input angle, in degrees
     *
     * @param x Input angle
     */
    static T TanDeg(T x);

    /**
     * @brief Calculates the sine of the input angle, in radians
     *
     * @param x Input angle
     */
    static T SinRad(T x);
    /**
     * @brief Calculates the cosine of the input angle, in radians
     *
     * @param x Input angle
     */
    static T CosRad(T x);
    /**
     * @brief Calculates the tangent of the input angle, in radians
     *
     * @param x Input angle
     */
    static T TanRad(T x);
    /**@}*/

private:
    //! pi
    static const T PI;
    //! 2pi
    static const T TWO_PI;
    //! pi/2
    static const T PI_HALF;
    //! pi/4
    static const T PI_QUARTER;

    //! ln(2)
    static const T LN2;
    //! 1/ln(2)
    static const T LN2_INV;
};

//! @}
} // namespace detail

typedef detail::TMath<s32> Mathi;
typedef detail::TMath<u32> Mathu;
typedef detail::TMath<f32> Mathf;
typedef detail::TMath<f64> Mathd;

//! @}
} // namespace kiwi

#endif
