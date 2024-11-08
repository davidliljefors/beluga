#pragma once
#include "CommonTypes.h"

struct Vec3 {
    f32 x, y, z;

    Vec3() : x(0.0f), y(0.0f), z(0.0f) {}
    Vec3(f32 x, f32 y, f32 z) : x(x), y(y), z(z) {}
    explicit Vec3(f32 scalar) : x(scalar), y(scalar), z(scalar) {}

    // Hidden friend operators for arithmetic
    friend Vec3 operator+(Vec3 lhs, const Vec3& rhs);
    friend Vec3 operator-(Vec3 lhs, const Vec3& rhs);
    friend Vec3 operator*(Vec3 lhs, const Vec3& rhs);
    friend Vec3 operator/(Vec3 lhs, const Vec3& rhs);

    // Scalar operations
    friend Vec3 operator*(Vec3 lhs, f32 rhs);
    friend Vec3 operator*(f32 lhs, Vec3 rhs);
    friend Vec3 operator/(Vec3 lhs, f32 rhs);

    // Compound assignment operators
    Vec3& operator+=(const Vec3& rhs);
    Vec3& operator-=(const Vec3& rhs);
    Vec3& operator*=(const Vec3& rhs);
    Vec3& operator/=(const Vec3& rhs);
    Vec3& operator*=(f32 scalar);
    Vec3& operator/=(f32 scalar);

    // Vector operations
    friend Vec3 normalize(const Vec3& v);
    friend Vec3 cross(const Vec3& a, const Vec3& b);
    friend f32 dot(const Vec3& a, const Vec3& b);
    friend f32 length(const Vec3& v);
    friend f32 length_squared(const Vec3& v);
};