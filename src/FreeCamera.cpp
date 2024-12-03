#include "FreeCamera.h"

#include <cmath>

FreeCamera::FreeCamera(f32 fov_degrees, f32 aspect_ratio, f32 near_plane, f32 far_plane)
    : m_position(0.0f, 0.0f, 0.0f)
    , m_forward(0.0f, 0.0f, 1.0f)
    , m_up(0.0f, 1.0f, 0.0f)
    , m_fov(fov_degrees)
    , m_aspect_ratio(aspect_ratio)
    , m_near(near_plane)
    , m_far(far_plane)
{
    update_view_matrix();
    update_projection_matrix();
}

void FreeCamera::set_position(const Vec3& position) {
    m_position = position;
    update_view_matrix();
}

void FreeCamera::look_at(const Vec3& target) {
    m_forward = normalize(target - m_position);
    update_view_matrix();
}

void FreeCamera::set_perspective(
    f32 fov_degrees, 
    f32 aspect_ratio,
	f32 near_plane, 
    f32 far_plane)
{
    m_fov = fov_degrees;
    m_aspect_ratio = aspect_ratio;
    m_near = near_plane;
    m_far = far_plane;
    update_projection_matrix();
}

void FreeCamera::update(f32 dt)
{

}

void FreeCamera::update_view_matrix() {
    Vec3 right = normalize(cross(m_up, m_forward));
    Vec3 up = cross(m_forward, right);
    
    m_view_matrix = Mat4x4(
        right.x,           right.y,           right.z,     -dot(right, m_position),
        up.x,              up.y,              up.z,        -dot(up, m_position),
        m_forward.x,       m_forward.y,       m_forward.z, -dot(m_forward, m_position),
        0.0f,              0.0f,              0.0f,        1.0f
    );
}

void FreeCamera::update_projection_matrix() {
    f32 tan_half_fov = tan(m_fov * 0.5f * 3.14159f / 180.0f);
    f32 f = 1.0f / tan_half_fov;
    
	m_projection_matrix = Mat4x4(
		f / m_aspect_ratio, 0.0f, 0.0f, 0.0f,
		0.0f, f, 0.0f, 0.0f,
		0.0f, 0.0f, (m_far + m_near) / (m_near - m_far), (2.0f * m_far * m_near) / (m_near - m_far),
		0.0f, 0.0f, -1.0f, 0.0f
	);
} 