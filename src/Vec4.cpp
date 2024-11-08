#include "Vec4.h"
#include <cmath>

Vec4 operator+(Vec4 lhs, const Vec4& rhs) {
    return Vec4(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w);
}

Vec4 operator-(Vec4 lhs, const Vec4& rhs) {
    return Vec4(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w);
}

Vec4 operator*(Vec4 lhs, const Vec4& rhs) {
    return Vec4(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z, lhs.w * rhs.w);
}

Vec4 operator/(Vec4 lhs, const Vec4& rhs) {
    return Vec4(lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z, lhs.w / rhs.w);
}

Vec4 operator*(Vec4 lhs, f32 rhs) {
    return Vec4(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs, lhs.w * rhs);
}

Vec4 operator*(f32 lhs, Vec4 rhs) {
    return rhs * lhs;  // Reuse the above operator
}

Vec4 operator/(Vec4 lhs, f32 rhs) {
    f32 inv = 1.0f / rhs;
    return lhs * inv;
}

Vec4& Vec4::operator+=(const Vec4& rhs) {
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    w += rhs.w;
    return *this;
}

Vec4& Vec4::operator-=(const Vec4& rhs) {
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    w -= rhs.w;
    return *this;
}

Vec4& Vec4::operator*=(const Vec4& rhs) {
    x *= rhs.x;
    y *= rhs.y;
    z *= rhs.z;
    w *= rhs.w;
    return *this;
}

Vec4& Vec4::operator/=(const Vec4& rhs) {
    x /= rhs.x;
    y /= rhs.y;
    z /= rhs.z;
    w /= rhs.w;
    return *this;
}

Vec4& Vec4::operator*=(f32 scalar) {
    x *= scalar;
    y *= scalar;
    z *= scalar;
    w *= scalar;
    return *this;
}

Vec4& Vec4::operator/=(f32 scalar) {
    f32 inv = 1.0f / scalar;
    return *this *= inv;
}

Vec4 normalize(const Vec4& v) {
    f32 len = length(v);
    return v * (1.0f / len);
}

f32 dot(const Vec4& a, const Vec4& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

f32 length(const Vec4& v) {
    return sqrt(length_squared(v));
}

f32 length_squared(const Vec4& v) {
    return dot(v, v);
} 