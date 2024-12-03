#pragma once
#include "Core.h"

#include "Vec3.h"
#include "Vec4.h"

class Mat4x4 {
public:
    Mat4x4();
    Mat4x4(f32 m00, f32 m01, f32 m02, f32 m03,
           f32 m10, f32 m11, f32 m12, f32 m13,
           f32 m20, f32 m21, f32 m22, f32 m23,
           f32 m30, f32 m31, f32 m32, f32 m33);

    void identity();

    // Matrix operations
    friend Mat4x4 operator*(const Mat4x4& lhs, const Mat4x4& rhs);
    friend Vec4 operator*(const Mat4x4& lhs, const Vec4& rhs);

    // Static creation methods
    static Mat4x4 create_translation(const Vec3& translation);
    static Mat4x4 create_scale(const Vec3& scale);
    static Mat4x4 create_rotation_x(f32 radians);
    static Mat4x4 create_rotation_y(f32 radians);
    static Mat4x4 create_rotation_z(f32 radians);
    static Mat4x4 create_perspective(f32 fov_radians, f32 aspect_ratio, f32 near_plane, f32 far_plane);
    static Mat4x4 create_look_at(const Vec3& eye, const Vec3& target, const Vec3& up);

private:
    f32 m[4][4];
};

using mat4x4 = Mat4x4; 