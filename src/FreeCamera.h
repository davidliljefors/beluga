#pragma once

#include "Core.h"
#include "Vec3.h"
#include "Matrix.h"

class FreeCamera {
public:
    FreeCamera(f32 fov_degrees = 75.0f, f32 aspect_ratio = 16.0f/9.0f, 
           f32 near_plane = 0.1f, f32 far_plane = 1000.0f);

    void set_position(const Vec3& position);
    void look_at(const Vec3& target);
    void set_perspective(f32 fov_degrees, f32 aspect_ratio, 
                        f32 near_plane, f32 far_plane);

    const Vec3& get_position() const { return m_position; }
    const Vec3& get_forward() const { return m_forward; }
    const Mat4x4& get_view_matrix() const { return m_view_matrix; }
    const Mat4x4& get_projection_matrix() const { return m_projection_matrix; }

    void update(f32 dt);

private:
    void update_view_matrix();
    void update_projection_matrix();

    Vec3 m_position;
    Vec3 m_forward;
    Vec3 m_up;
    
    f32 m_fov;
    f32 m_aspect_ratio;
    f32 m_near;
    f32 m_far;

    Mat4x4 m_view_matrix;
    Mat4x4 m_projection_matrix;
}; 