#pragma once

#include <vector>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <Homogeneous.hpp>
#include <Updater.hpp>

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

class Instance : public Updatable
{
// [members]

    const Model& m_model;
    
    float m_scale{1};
    float m_angle{0};
    sf::Vector3f m_position{0, 0, 0};

    Mat4f instance_transform;

public:

// [functions]

// [ctor]

    Instance(   Updater& updater,
                const Model& model,
                float scale,
                float angle,
                const sf::Vector3f position)
    :
        Updatable{updater},
        m_model{model},
        m_scale{scale},
        m_angle{angle},
        m_position{position}
    {
        update();
    };

// [setters]

    void set_position(const sf::Vector3f& position)
    {
        m_position = position;
        need_update();
    }

    void set_rotation(float angle)
    {
        m_angle = angle;
        need_update();
    };

    void set_scale(float scale)
    {
        m_scale = scale;
        need_update();
    };

// [getters]

const Model& get_model() const { return m_model; }

const Mat4f& get_instance_transform() const { return instance_transform; }

// [update]

    void update() override
    {
        instance_transform =    create_translation_matrix(m_position)
                                *
                                create_rotation_y_matrix(deg2rad(m_angle))
                                *
                                create_scale_matrix(m_scale);
    }
};

extern const Model cube;