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

// [HOMOGENEOUS TRANSFROM MATRIXES]

Mat4f create_scale_matrix(float scale);

Mat4f create_translation_matrix(sf::Vector3f vec);

Mat4f create_rotation_y_matrix(float phi);

/*
    Projects point from Scene to pixel_array

    d - ViewPort distance from origin
    v_w, v_h - ViewPort width and height
    C_w, C_h - canvas width and height
*/
Mat3x4f create_projection_matrix(float d,
                                        float v_w,
                                        float v_h,
                                        int C_w,
                                        int C_h);

// [HOMOGENEOUS TO CARTESIAN]

sf::Vector3f homogeneous_to_cartesian_3d(float x, float y, float z, float w);

sf::Vector2f homogeneous_to_cartesian_2d(float x, float y, float z);

// [VECTOR OPERATIONS]

float square(const sf::Vector3f& vec);

float dot_product(const sf::Vector3f& lhs, const sf::Vector3f& rhs);

sf::Vector3f normalize(const sf::Vector3f& vec);

// [OTHERS]

bool is_equal(float lhs, float rhs);

float deg2rad(float deg);

