#include "Vec3.h"
#include <cmath>

Vec3 operator+(Vec3 lhs, const Vec3& rhs) {
    return Vec3(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
}

Vec3 operator-(Vec3 lhs, const Vec3& rhs) {
    return Vec3(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
}

Vec3 operator*(Vec3 lhs, const Vec3& rhs) {
    return Vec3(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z);
}

Vec3 operator/(Vec3 lhs, const Vec3& rhs) {
    return Vec3(lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z);
}

Vec3 operator*(Vec3 lhs, f32 rhs) {
    return Vec3(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs);
}

Vec3 operator*(f32 lhs, Vec3 rhs) {
    return rhs * lhs;  // Reuse the above operator
}

Vec3 operator/(Vec3 lhs, f32 rhs) {
    f32 inv = 1.0f / rhs;
    return lhs * inv;
}

Vec3& Vec3::operator+=(const Vec3& rhs) {
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    return *this;
}

Vec3& Vec3::operator-=(const Vec3& rhs) {
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    return *this;
}

Vec3& Vec3::operator*=(const Vec3& rhs) {
    x *= rhs.x;
    y *= rhs.y;
    z *= rhs.z;
    return *this;
}

Vec3& Vec3::operator/=(const Vec3& rhs) {
    x /= rhs.x;
    y /= rhs.y;
    z /= rhs.z;
    return *this;
}

Vec3& Vec3::operator*=(f32 scalar) {
    x *= scalar;
    y *= scalar;
    z *= scalar;
    return *this;
}

Vec3& Vec3::operator/=(f32 scalar) {
    f32 inv = 1.0f / scalar;
    return *this *= inv;
}

Vec3 normalize(const Vec3& v) {
    f32 len = length(v);
    return v * (1.0f / len);
}

Vec3 cross(const Vec3& a, const Vec3& b) {
    return Vec3(
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    );
}

f32 dot(const Vec3& a, const Vec3& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

f32 length(const Vec3& v) {
    return sqrt(length_squared(v));
}

f32 length_squared(const Vec3& v) {
    return dot(v, v);
} 