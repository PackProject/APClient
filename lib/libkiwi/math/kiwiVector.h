#ifndef LIBKIWI_MATH_VECTOR_H
#define LIBKIWI_MATH_VECTOR_H
#include <libkiwi/k_types.h>

#include <egg/math.h>

#include <nw4r/math.h>

#include <revolution/MTX.h>

namespace kiwi {
//! @addtogroup libkiwi_math
//! @{

/**
 * @brief 3D, floating-point vector
 */
class Vec2f : public EGG::Vector2f {
public:
    //! Zero vector
    static const Vec2f ZERO;

    //! Unit vector pointing along the X-axis
    static const Vec2f UX;
    //! Unit vector pointing along the Y-axis
    static const Vec2f UY;

public:
    /**
     * @brief Constructor
     */
    Vec2f() : EGG::Vector2f(0.0f, 0.0f) {}

    /**
     * @brief Constructor
     *
     * @param fx X-component
     * @param fy Y-component
     */
    Vec2f(f32 fx, f32 fy) : EGG::Vector2f(fx, fy) {}

    /**
     * @brief Constructor
     *
     * @param rOther EGG vector
     */
    Vec2f(const EGG::Vector2f& rOther) : EGG::Vector2f(rOther) {}

    /**
     * @brief Constructor
     *
     * @param rOther NW4R vector
     */
    Vec2f(const nw4r::math::VEC2& rOther) : EGG::Vector2f(rOther) {}

    /**
     * @brief Constructor
     *
     * @param pArray Component array
     */
    Vec2f(const f32 pArray[2]);

    /**
     * @brief Gets the length/magnitude of the vector
     */
    f32 Length() const;

    /**
     * @brief Scales the vector to have a magnitude of one
     *
     * @return f32 Original vector magnitude
     */
    f32 Normalize();

    /**
     * @brief Computes the dot product against another vector
     *
     * @param rOther Other vector
     */
    f32 Dot(const Vec2f& rOther) const;
};

/**
 * @brief 3D, floating-point vector
 */
class Vec3f : public EGG::Vector3f {
public:
    //! Zero vector
    static const Vec3f ZERO;

    //! Unit vector pointing along the X-axis
    static const Vec3f UX;
    //! Unit vector pointing along the Y-axis
    static const Vec3f UY;
    //! Unit vector pointing along the Z-axis
    static const Vec3f UZ;

public:
    operator Vec*() {
        return reinterpret_cast<Vec*>(this);
    }
    operator const Vec*() const {
        return reinterpret_cast<const Vec*>(this);
    }

    /**
     * @brief Constructor
     */
    Vec3f() : EGG::Vector3f(0.0f, 0.0f, 0.0f) {}

    /**
     * @brief Constructor
     *
     * @param fx X-component
     * @param fy Y-component
     * @param fz Z-component
     */
    Vec3f(f32 fx, f32 fy, f32 fz) : EGG::Vector3f(fx, fy, fz) {}

    /**
     * @brief Constructor
     *
     * @param rOther EGG vector
     */
    Vec3f(const EGG::Vector3f& rOther) : EGG::Vector3f(rOther) {}

    /**
     * @brief Constructor
     *
     * @param rOther NW4R vector
     */
    Vec3f(const nw4r::math::VEC3& rOther) : EGG::Vector3f(rOther) {}

    /**
     * @brief Constructor
     *
     * @param pOther SDK vector
     */
    Vec3f(const Vec* pOther);

    /**
     * @brief Constructor
     *
     * @param pArray Component array
     */
    Vec3f(const f32 pArray[3]);

    /**
     * @brief Gets the length/magnitude of the vector
     */
    f32 Length() const;

    /**
     * @brief Scales the vector to have a magnitude of one
     *
     * @return f32 Original vector magnitude
     */
    f32 Normalize();

    /**
     * @brief Computes the dot product against another vector
     *
     * @param rOther Other vector
     */
    f32 Dot(const Vec3f& rOther) const;
};

//! @}
} // namespace kiwi

#endif
