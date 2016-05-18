#ifndef MATH_HPP
#define MATH_HPP

namespace Math {

/// PI
constexpr auto PI = 3.14159265358979;

constexpr float radian(float degree) {
    return degree / 180 * PI;
}

}

#endif // MATH_HPP
