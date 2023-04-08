#pragma once

#include <vector>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <Homogeneous.hpp>

// union of vertices and triangles
struct Model
{
    struct TriangleVertices
    {
        int a, b, c;
        sf::Color clr;
    };

    std::vector<sf::Vector3f> vertices;
    std::vector<TriangleVertices> triangles;

    void move(sf::Vector3f move_vector);

    Model() = delete;
};

struct Instance
{
// [members]

    const Model& model;
    
    float scale{1};
    float rotate_angle{0};
    sf::Vector3f position{0, 0, 0};

    Mat4f transform_matrix;
    bool is_need_update{true};

// [functions]

    void set_position(const sf::Vector3f& vec)
    {
        is_need_update = true;
        position = vec;
    }

    void set_rotation(float phi)
    {
        is_need_update = true;
        rotate_angle = phi;
    };

    void set_scale(float scale_)
    {
        is_need_update = true;
        scale = scale_;
    };

    void update_transform()
    {
        if (is_need_update)
        {
            transform_matrix =  create_translation_matrix(position)
                                *
                                create_rotation_y_matrix(deg2rad(rotate_angle))
                                *
                                create_scale_matrix(scale);

            is_need_update = false;
        }
    }

    sf::Vector3f transform(const sf::Vector3f vec) const;
    sf::Vector3f rotate_y(const sf::Vector3f vec) const;

    Instance(const Model& model_, float scale_, float phi, const sf::Vector3f pos)
    :
        model{model_},
        scale{scale_},
        rotate_angle{phi},
        position{pos}
    {
        transform_matrix << 0, 0, 0, 0,
                            0, 0, 0, 0,
                            0, 0, 0, 0,
                            0, 0, 0, 0;
    };
};

extern const Model cube;