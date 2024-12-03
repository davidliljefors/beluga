#include "quat.h"

#include <cmath>

const f32 PI_HALF = 1.57079632679f;

Quaternion::Quaternion() : x(0.0f), y(0.0f), z(0.0f), w(1.0f) {}

Quaternion::Quaternion(f32 x, f32 y, f32 z, f32 w) : x(x), y(y), z(z), w(w) {}

Quaternion Quaternion::identity() {
    return Quaternion(0.0f, 0.0f, 0.0f, 1.0f);
}

Quaternion Quaternion::from_euler(f32 pitch, f32 yaw, f32 roll) {
    f32 cy = cosf(yaw * 0.5f);
    f32 sy = sinf(yaw * 0.5f);
    f32 cp = cosf(pitch * 0.5f);
    f32 sp = sinf(pitch * 0.5f);
    f32 cr = cosf(roll * 0.5f);
    f32 sr = sinf(roll * 0.5f);

    return Quaternion(
        sr * cp * cy - cr * sp * sy,
        cr * sp * cy + sr * cp * sy,
        cr * cp * sy - sr * sp * cy,
        cr * cp * cy + sr * sp * sy
    );
}

Quaternion Quaternion::from_axis_angle(f32 x, f32 y, f32 z, f32 angle_radians) {
    f32 s = sinf(angle_radians * 0.5f);
    return Quaternion(
        x * s,
        y * s,
        z * s,
        cosf(angle_radians * 0.5f)
    );
}

Quaternion Quaternion::conjugate() const {
    return Quaternion(-x, -y, -z, w);
}

f32 Quaternion::magnitude() const {
    return sqrtf(x * x + y * y + z * z + w * w);
}

Quaternion Quaternion::normalize() const {
    f32 inv_mag =  1.0f / magnitude();
    return Quaternion(x * inv_mag, y * inv_mag, z * inv_mag, w * inv_mag);
}

void Quaternion::normalize_self() {
    f32 inv_mag =  1.0f / magnitude();
    x *= inv_mag;
    y *= inv_mag;
    z *= inv_mag;
    w *= inv_mag;
}

Quaternion Quaternion::operator*(const Quaternion& other) const {
    return Quaternion(
        w * other.x + x * other.w + y * other.z - z * other.y,
        w * other.y + y * other.w + z * other.x - x * other.z,
        w * other.z + z * other.w + x * other.y - y * other.x,
        w * other.w - x * other.x - y * other.y - z * other.z
    );
}

Quaternion& Quaternion::operator*=(const Quaternion& other) {
    *this = *this * other;
    return *this;
}

bool Quaternion::operator==(const Quaternion& other) const {
    return x == other.x && y == other.y && z == other.z && w == other.w;
}

bool Quaternion::operator!=(const Quaternion& other) const {
    return !(*this == other);
}

void Quaternion::to_axis_angle(f32& x, f32& y, f32& z, f32& angle_radians) const {
    f32 mag = sqrtf(x * x + y * y + z * z);
    if (mag == 0.0f) {
        x = 0.0f;
        y = 0.0f;
        z = 0.0f;
        angle_radians = 0.0f;
    } else {
        f32 s = 2.0f * atan2f(mag, w);
        x /= mag;
        y /= mag;
        z /= mag;
        angle_radians = s;
    }
}

void Quaternion::to_euler(f32& pitch, f32& yaw, f32& roll) const {
    f32 x = this->x;
    f32 y = this->y;
    f32 z = this->z;
    f32 w = this->w;

    f32 test = x * y + z * w;
    if (test > 0.499f * 0.5f) {
        pitch = 2.0f * atan2f(x, w);
        yaw = PI_HALF;
        roll = 0.0f;
    } else if (test < -0.499f * 0.5f) {
        pitch = -2.0f * atan2f(x, w);
        yaw = -PI_HALF;
        roll = 0.0f;
    } else {
        f32 sqx = x * x;
        f32 sqy = y * y;
        f32 sqz = z * z;
        pitch = atan2f(2.0f * y * w - 2.0f * x * z, 1.0f - 2.0f * sqy - 2.0f * sqz);
        yaw = asinf(2.0f * test);
        roll = atan2f(2.0f * x * w - 2.0f * y * z, 1.0f - 2.0f * sqx - 2.0f * sqz);
    }
} 