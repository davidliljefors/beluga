#include <cmath>

#include "Matrix.h"


Mat4x4::Mat4x4() {
    identity();
}

Mat4x4::Mat4x4(f32 m00, f32 m01, f32 m02, f32 m03,
               f32 m10, f32 m11, f32 m12, f32 m13,
               f32 m20, f32 m21, f32 m22, f32 m23,
               f32 m30, f32 m31, f32 m32, f32 m33) 
{
    m[0][0] = m00; m[0][1] = m01; m[0][2] = m02; m[0][3] = m03;
    m[1][0] = m10; m[1][1] = m11; m[1][2] = m12; m[1][3] = m13;
    m[2][0] = m20; m[2][1] = m21; m[2][2] = m22; m[2][3] = m23;
    m[3][0] = m30; m[3][1] = m31; m[3][2] = m32; m[3][3] = m33;
}

void Mat4x4::identity() {
    m[0][0] = 1.0f; m[0][1] = 0.0f; m[0][2] = 0.0f; m[0][3] = 0.0f;
    m[1][0] = 0.0f; m[1][1] = 1.0f; m[1][2] = 0.0f; m[1][3] = 0.0f;
    m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = 1.0f; m[2][3] = 0.0f;
    m[3][0] = 0.0f; m[3][1] = 0.0f; m[3][2] = 0.0f; m[3][3] = 1.0f;
}

Mat4x4 operator*(const Mat4x4& lhs, const Mat4x4& rhs) {
    Mat4x4 result;
    for (u32 i = 0; i < 4; i++) {
        for (u32 j = 0; j < 4; j++) {
            result.m[i][j] = 0.0f;
            for (u32 k = 0; k < 4; k++) {
                result.m[i][j] += lhs.m[i][k] * rhs.m[k][j];
            }
        }
    }
    return result;
}

Vec4 operator*(const Mat4x4& lhs, const Vec4& rhs) {
    return Vec4(
        lhs.m[0][0] * rhs.x + lhs.m[0][1] * rhs.y + lhs.m[0][2] * rhs.z + lhs.m[0][3] * rhs.w,
        lhs.m[1][0] * rhs.x + lhs.m[1][1] * rhs.y + lhs.m[1][2] * rhs.z + lhs.m[1][3] * rhs.w,
        lhs.m[2][0] * rhs.x + lhs.m[2][1] * rhs.y + lhs.m[2][2] * rhs.z + lhs.m[2][3] * rhs.w,
        lhs.m[3][0] * rhs.x + lhs.m[3][1] * rhs.y + lhs.m[3][2] * rhs.z + lhs.m[3][3] * rhs.w
    );
}

Mat4x4 Mat4x4::create_translation(const Vec3& translation) {
    Mat4x4 result;
    result.m[3][0] = translation.x;
    result.m[3][1] = translation.y;
    result.m[3][2] = translation.z;
    return result;
}

Mat4x4 Mat4x4::create_scale(const Vec3& scale) {
    Mat4x4 result;
    result.m[0][0] = scale.x;
    result.m[1][1] = scale.y;
    result.m[2][2] = scale.z;
    return result;
}

Mat4x4 Mat4x4::create_rotation_x(f32 radians) {
    Mat4x4 result;
    f32 cos_angle = cos(radians);
    f32 sin_angle = sin(radians);
    result.m[1][1] = cos_angle;
    result.m[1][2] = -sin_angle;
    result.m[2][1] = sin_angle;
    result.m[2][2] = cos_angle;
    return result;
}

Mat4x4 Mat4x4::create_rotation_y(f32 radians) {
    Mat4x4 result;
    f32 cos_angle = cos(radians);
    f32 sin_angle = sin(radians);
    result.m[0][0] = cos_angle;
    result.m[0][2] = sin_angle;
    result.m[2][0] = -sin_angle;
    result.m[2][2] = cos_angle;
    return result;
}

Mat4x4 Mat4x4::create_rotation_z(f32 radians) {
    Mat4x4 result;
    f32 cos_angle = cos(radians);
    f32 sin_angle = sin(radians);
    result.m[0][0] = cos_angle;
    result.m[0][1] = -sin_angle;
    result.m[1][0] = sin_angle;
    result.m[1][1] = cos_angle;
    return result;
}

Mat4x4 Mat4x4::create_perspective(f32 fov_radians, f32 aspect_ratio, f32 near_plane, f32 far_plane) {
    Mat4x4 result;
    f32 tan_half_fov = tan(fov_radians * 0.5f);
    f32 f = 1.0f / tan_half_fov;
    
    result.m[0][0] = f / aspect_ratio;
    result.m[1][1] = f;
    result.m[2][2] = (far_plane + near_plane) / (near_plane - far_plane);
    result.m[2][3] = -1.0f;
    result.m[3][2] = (2.0f * far_plane * near_plane) / (near_plane - far_plane);
    result.m[3][3] = 0.0f;
    
    return result;
}

Mat4x4 Mat4x4::create_look_at(const Vec3& eye, const Vec3& target, const Vec3& up) {
    Vec3 f = normalize(target - eye);
    Vec3 r = normalize(cross(up, f));
    Vec3 u = cross(f, r);

    return Mat4x4(
        r.x,            u.x,            f.x,            0.0f,
        r.y,            u.y,            f.y,            0.0f,
        r.z,            u.z,            f.z,            0.0f,
        -dot(r, eye),   -dot(u, eye),   -dot(f, eye),   1.0f
    );
}
