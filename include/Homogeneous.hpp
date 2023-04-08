#pragma once

#include <cmath>
#include <Eigen/Geometry>
#include <SFML/Graphics.hpp>
#include <Debug.hpp>

using Mat4f = Eigen::Matrix4f;
using Mat3x4f = Eigen::Matrix<float, 3, 4>;
using Vec4f = Eigen::Vector4f;
using Vec3f = Eigen::Vector3f;
using Vec2i = Eigen::Vector2i;

/*
    Make all transformations homogeneous using
    homogeneous coords
*/

inline bool is_equal(float lhs, float rhs)
{
    const float PRESICION = 0.0001;
    return fabs(lhs - rhs) < PRESICION;    
}

inline Mat4f create_scale_matrix(float scale)
{
    Mat4f temp;
    
    temp << 
            scale,  0.f,    0.f,    0,
            0.f,    scale,  0.f,    0,
            0.f,    0.f,    scale,  0,
            0.f,    0.f,    0.f,    1.f
            ;

    info() << "Scale matrix:\n\n" << temp << "\n\n";

    return temp;
}

inline Mat4f create_translation_matrix(sf::Vector3f vec)
{
    Mat4f temp;

    temp << 
            1.f, 0.f, 0.f, vec.x,
            0.f, 1.f, 0.f, vec.y,
            0.f, 0.f, 1.f, vec.z,
            0.f, 0.f, 0.f, 1.f
            ;

    info() << "Translation matrix:\n\n" << temp << "\n\n";

    return temp;
}

inline Mat4f create_rotation_y_matrix(float phi)
{
    Mat4f temp;
    
    temp <<
            cosf(phi),  0, sinf(phi),   0,
                0,      1,   0,         0,
            -sinf(phi), 0, cosf(phi),   0,
                0,      0,   0,         1;

    info() << "Rotation matrix:\n\n" << temp << "\n\n";

    return temp;
}

// It is all children toys. Time for PROJECTINGGWP

/*
    This function projects point from scene to pixel_array

    d - ViewPort distance from origin
    v_w, v_h - ViewPort width and height
    C_w, C_h - canvas width and height
*/
inline Mat3x4f create_projection_matrix(float d, float v_w, float v_h,
                                 int C_w, int C_h)
{
    Mat3x4f temp;
    
    temp << 
            (-d) * C_w / v_w,         0,                 C_w / 2.,    0,
                0,           -(-d) * C_h / v_h,          C_h / 2.,    0,
                0,                    0,                      1,      0;

    info() << "Projection matrix:\n\n" << temp << "\n\n";

    return temp;
}

inline sf::Vector3f homogeneous_to_cartesian_3d(float x, float y, float z, float w)
{
    sf::Vector3f vec{x, y, z};

    if (is_equal(w, 0))
    {
        return vec;
    }
    else
    {
        return vec * (1/w);
    }
}

inline sf::Vector2f homogeneous_to_cartesian_2d(float x, float y, float z)
{
    sf::Vector2f vec{x, y};

    if (is_equal(z, 0))
    {
        return vec;
    }
    else
    {
        return vec * (1/z);
    }
}

inline sf::Vector2i transform_point(const Mat4f& camera_transform,
                             const Mat4f& instance_transform,
                             const Mat3x4f& project_transform,
                             const sf::Vector3f& point)
{
    Mat3x4f transform_mat;
    transform_mat.Zero();

    transform_mat = project_transform
                    *
                    camera_transform
                    *
                    instance_transform;
 
    Vec4f homogeneous_point_3d{point.x, point.y, point.z, 1};
    info() << "Homogen3d: \n" << homogeneous_point_3d << "\n\n";

    info() << "Todos transformations matrix: \n" << transform_mat << "\n\n";

    Vec3f homogeneous_point_2d = transform_mat * homogeneous_point_3d;
    info() << "Homogen2d: \n" << homogeneous_point_2d << "\n\n";

    sf::Vector2f pixel_array_point_f =  homogeneous_to_cartesian_2d(
                                                                    homogeneous_point_2d(0),
                                                                    homogeneous_point_2d(1),
                                                                    homogeneous_point_2d(2)
                                                                    );

    return sf::Vector2i{int(pixel_array_point_f.x), int(pixel_array_point_f.y)};
}

inline float deg2rad(float deg)
{
    return deg / 180. * M_PI;
}
