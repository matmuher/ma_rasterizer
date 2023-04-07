#pragma once

#include <Eigen/Geometry>
#include <SFML/Graphics.hpp>
#include <cmath>

using Mat4f = Eigen::Matrix<float, 4, 4>;
using Mat3x4f = Eigen::Matrix<float, 3, 4>;

/*
    Make all transformations homogeneous using
    homogeneous coords
*/

inline Mat4f create_scale_matrix(float scale)
{
        Mat4f temp;
    
    temp << 
            scale,  0.f,    0.f,    0,
            0.f,    scale,  0.f,    0,
            0.f,    0.f,    scale,  0,
            0.f,    0.f,    0.f,    1.f
            ;

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

    return temp;
}

inline Mat4f create_rotation_y_matrix(float phi)
{
    Mat4f temp;
    
    temp <<
            cos(phi),  0, sin(phi), 0,
                0,     1,   0,      0,
            -sin(phi), 0, cos(phi), 0,
                0,     0,   0,      1;

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

    return temp;
}

inline sf::Vector2f homogeneous_to_cartesian2d(float x, float y, float z)
{
    return sf::Vector2f{x / z, y / z};
}
