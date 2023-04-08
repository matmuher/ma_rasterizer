#include <Camera.hpp>
#include <MaRasterizer.hpp>
#include <Debug.hpp>

// [ctors]

Camera::Camera
        (
            int Width,
            int Height,
            float ViewPortDistance,
            float ViewPortWidth,
            float ViewPortHeight,
            float angle,
            sf::Vector3f position
        )
    :
        m_Width{Width},
        m_Height{Height},
        m_ViewPortDistance{ViewPortDistance},
        m_ViewPortWidth{ViewPortWidth},
        m_ViewPortHeight{ViewPortHeight},
        m_angle{angle},
        m_position{position}
{
    update();
}

// [setters]

void Camera::set_rotation(float angle)
{
    is_camera_transform_outdated = true;
    m_angle = angle;
}

void Camera::set_position(const sf::Vector3f& position)
{
    is_camera_transform_outdated = true;
    m_position = position;
}

// [getters]

const Mat4f& Camera::get_camera_transform() const
{
    return camera_transform;
}

const Mat3x4f& Camera::get_project_transform() const
{
    return project_transform;
}

int Camera::get_width() const
{
    return m_Width;
}

int Camera::get_height() const
{
    return m_Height;
}

float Camera::get_vp_width() const
{
    return m_ViewPortWidth;
}

float Camera::get_vp_height() const
{
    return m_ViewPortHeight;
}

float Camera::get_vp_dist() const
{
    return m_ViewPortDistance;
}

// [update]

void Camera::update()
{
    if (is_camera_transform_outdated)
    {
        update_camera_transform();
        is_camera_transform_outdated = false;
    }

    if (is_project_transform_outdated)
    {
        update_project_transform();
        is_project_transform_outdated = false;
    }
}

void Camera::update_camera_transform()
{
    camera_transform =  create_translation_matrix(m_position)
                        *
                        create_rotation_y_matrix(m_angle);
}

void Camera::update_project_transform()
{
    project_transform = create_projection_matrix(
                                                m_ViewPortDistance,
                                                m_ViewPortWidth,
                                                m_ViewPortHeight,
                                                m_Width,
                                                m_Height
                                                );
}
