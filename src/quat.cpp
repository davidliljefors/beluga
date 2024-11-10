#include "quat.h"
#include <cmath>

const float PI_HALF = 1.57079632679f;

Quaternion::Quaternion() : x(0.0f), y(0.0f), z(0.0f), w(1.0f) {}

Quaternion::Quaternion(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

Quaternion Quaternion::identity() {
    return Quaternion(0.0f, 0.0f, 0.0f, 1.0f);
}

Quaternion Quaternion::from_euler(float pitch, float yaw, float roll) {
    float cy = cosf(yaw * 0.5f);
    float sy = sinf(yaw * 0.5f);
    float cp = cosf(pitch * 0.5f);
    float sp = sinf(pitch * 0.5f);
    float cr = cosf(roll * 0.5f);
    float sr = sinf(roll * 0.5f);

    return Quaternion(
        sr * cp * cy - cr * sp * sy,
        cr * sp * cy + sr * cp * sy,
        cr * cp * sy - sr * sp * cy,
        cr * cp * cy + sr * sp * sy
    );
}

Quaternion Quaternion::from_axis_angle(float x, float y, float z, float angle_radians) {
    float s = sinf(angle_radians * 0.5f);
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

float Quaternion::magnitude() const {
    return sqrtf(x * x + y * y + z * z + w * w);
}

Quaternion Quaternion::normalize() const {
    float mag = magnitude();
    return Quaternion(x / mag, y / mag, z / mag, w / mag);
}

void Quaternion::normalize_self() {
    float mag = magnitude();
    x /= mag;
    y /= mag;
    z /= mag;
    w /= mag;
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

void Quaternion::to_axis_angle(float& x, float& y, float& z, float& angle_radians) const {
    float mag = sqrtf(x * x + y * y + z * z);
    if (mag == 0.0f) {
        x = 0.0f;
        y = 0.0f;
        z = 0.0f;
        angle_radians = 0.0f;
    } else {
        float s = 2.0f * atan2f(mag, w);
        x /= mag;
        y /= mag;
        z /= mag;
        angle_radians = s;
    }
}

void Quaternion::to_euler(float& pitch, float& yaw, float& roll) const {
    float x = this->x;
    float y = this->y;
    float z = this->z;
    float w = this->w;

    float test = x * y + z * w;
    if (test > 0.499f * 0.5f) {
        pitch = 2.0f * atan2f(x, w);
        yaw = PI_HALF;
        roll = 0.0f;
    } else if (test < -0.499f * 0.5f) {
        pitch = -2.0f * atan2f(x, w);
        yaw = -PI_HALF;
        roll = 0.0f;
    } else {
        float sqx = x * x;
        float sqy = y * y;
        float sqz = z * z;
        pitch = atan2f(2.0f * y * w - 2.0f * x * z, 1.0f - 2.0f * sqy - 2.0f * sqz);
        yaw = asinf(2.0f * test);
        roll = atan2f(2.0f * x * w - 2.0f * y * z, 1.0f - 2.0f * sqx - 2.0f * sqz);
    }
} 