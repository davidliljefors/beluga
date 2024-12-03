#pragma once
#include "Core.h"

class Quaternion {
public:
    f32 x, y, z, w;

    Quaternion();
    Quaternion(f32 x, f32 y, f32 z, f32 w);
    
    static Quaternion identity();
    static Quaternion from_euler(f32 pitch, f32 yaw, f32 roll);
    static Quaternion from_axis_angle(f32 x, f32 y, f32 z, f32 angle_radians);

    Quaternion conjugate() const;
    f32 magnitude() const;
    Quaternion normalize() const;
    void normalize_self();

    Quaternion operator*(const Quaternion& other) const;
    Quaternion& operator*=(const Quaternion& other);
    bool operator==(const Quaternion& other) const;
    bool operator!=(const Quaternion& other) const;

    void to_axis_angle(f32& x, f32& y, f32& z, f32& angle_radians) const;
    void to_euler(f32& pitch, f32& yaw, f32& roll) const;
}; 