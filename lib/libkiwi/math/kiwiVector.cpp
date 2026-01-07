#include <libkiwi.h>

namespace kiwi {

/******************************************************************************
 *
 * Vec2f
 *
 ******************************************************************************/

/**
 * @brief Zero vector
 */
const Vec2f Vec2f::ZERO(0.0f, 0.0f);

/**
 * @brief Unit vector pointing along the X-axis
 */
const Vec2f Vec2f::UX(1.0f, 0.0f);

/**
 * @brief Unit vector pointing along the Y-axis
 */
const Vec2f Vec2f::UY(0.0f, 1.0f);

/**
 * @brief Constructor
 *
 * @param pArray Component array
 */
Vec2f::Vec2f(const f32 pArray[2]) {
    K_ASSERT_PTR(pArray);

    x = pArray[0];
    y = pArray[1];
}

/**
 * @brief Gets the length/magnitude of the vector
 */
f32 Vec2f::Length() const {
    return Mathf::Sqrt(Dot(*this));
}

/**
 * @brief Scales the vector to have a magnitude of one
 *
 * @return f32 Original vector magnitude
 */
f32 Vec2f::Normalize() {
    f32 length = Length();

    if (length > 0.0f) {
        *this /= length;
    }

    return length;
}

/**
 * @brief Computes the dot product against another vector
 *
 * @param rOther Other vector
 */
f32 Vec2f::Dot(const Vec2f& rOther) const {
    return x * rOther.x + y * rOther.y;
}

/******************************************************************************
 *
 * Vec3f
 *
 ******************************************************************************/

/**
 * @brief Zero vector
 */
const Vec3f Vec3f::ZERO(0.0f, 0.0f, 0.0f);

/**
 * @brief Unit vector pointing along the X-axis
 */
const Vec3f Vec3f::UX(1.0f, 0.0f, 0.0f);

/**
 * @brief Unit vector pointing along the Y-axis
 */
const Vec3f Vec3f::UY(0.0f, 1.0f, 0.0f);

/**
 * @brief Unit vector pointing along the Z-axis
 */
const Vec3f Vec3f::UZ(0.0f, 0.0f, 1.0f);

/**
 * @brief Constructor
 *
 * @param pOther SDK vector
 */
Vec3f::Vec3f(const Vec* pOther) {
    K_ASSERT_PTR(pOther);

    x = pOther->x;
    y = pOther->y;
    z = pOther->z;
}

/**
 * @brief Constructor
 *
 * @param pArray Component array
 */
Vec3f::Vec3f(const f32 pArray[3]) {
    K_ASSERT_PTR(pArray);

    x = pArray[0];
    y = pArray[1];
    z = pArray[2];
}

/**
 * @brief Gets the length/magnitude of the vector
 */
f32 Vec3f::Length() const {
    return Mathf::Sqrt(Dot(*this));
}

/**
 * @brief Scales the vector to have a length of one
 *
 * @return f32 Original vector length
 */
f32 Vec3f::Normalize() {
    f32 length = Length();

    if (length > 0.0f) {
        *this /= length;
    }

    return length;
}

/**
 * @brief Computes the dot product against another vector
 *
 * @param rOther Other vector
 */
f32 Vec3f::Dot(const Vec3f& rOther) const {
    return x * rOther.x + y * rOther.y + z * rOther.z;
}

} // namespace kiwi