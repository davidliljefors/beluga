#pragma once
#include "CommonTypes.h"
#include "Vec3.h"

struct Vec4 {
    f32 x, y, z, w;

    Vec4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
    Vec4(f32 x, f32 y, f32 z, f32 w) : x(x), y(y), z(z), w(w) {}
    Vec4(const Vec3& v, f32 w) : x(v.x), y(v.y), z(v.z), w(w) {}
    explicit Vec4(f32 scalar) : x(scalar), y(scalar), z(scalar), w(scalar) {}

    // Hidden friend operators for arithmetic
    friend Vec4 operator+(Vec4 lhs, const Vec4& rhs);
    friend Vec4 operator-(Vec4 lhs, const Vec4& rhs);
    friend Vec4 operator*(Vec4 lhs, const Vec4& rhs);
    friend Vec4 operator/(Vec4 lhs, const Vec4& rhs);

    // Scalar operations
    friend Vec4 operator*(Vec4 lhs, f32 rhs);
    friend Vec4 operator*(f32 lhs, Vec4 rhs);
    friend Vec4 operator/(Vec4 lhs, f32 rhs);

    // Compound assignment operators
    Vec4& operator+=(const Vec4& rhs);
    Vec4& operator-=(const Vec4& rhs);
    Vec4& operator*=(const Vec4& rhs);
    Vec4& operator/=(const Vec4& rhs);
    Vec4& operator*=(f32 scalar);
    Vec4& operator/=(f32 scalar);

    // Vector operations
    friend Vec4 normalize(const Vec4& v);
    friend f32 dot(const Vec4& a, const Vec4& b);
    friend f32 length(const Vec4& v);
    friend f32 length_squared(const Vec4& v);

    // Conversion to Vec3
    Vec3 xyz() const { return Vec3(x, y, z); }
};