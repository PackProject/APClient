#ifndef EGG_MATH_RAY_H
#define EGG_MATH_RAY_H
#include <egg/types_egg.h>

#include <egg/math/eggVector.h>

namespace EGG {

class Ray3f {
public:
    Ray3f() {}
    Ray3f(const Vector3f& rDir, const Vector3f& rOrigin)
        : dir(rDir), origin(rOrigin) {}

public:
    Vector3f dir;    // at 0x0
    Vector3f origin; // at 0xC
};

} // namespace EGG

#endif
