#pragma once

#include <vector>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <Homogeneous.hpp>
#include <Updater.hpp>

struct TriangleVertices
{
    int a, b, c;
    sf::Color clr;
};

// union of vertices and triangles
struct Model
{
// [MEMBERS]

    std::vector<sf::Vector3f> vertices;
    std::vector<TriangleVertices> triangles;
    Sphere bounding_sphere;

// [FUNCTIONS]

// [ctors]

    Model(  const std::vector<sf::Vector3f>& model_vertices,
            const std::vector<TriangleVertices>& model_triangles)
    :
        vertices{model_vertices},
        triangles{model_triangles},
        bounding_sphere{create_bounding_sphere(vertices)}
    {
        info() << bounding_sphere << '\n';
    }

    Model() = delete;

// [others]


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

    void change_position(const sf::Vector3f& shift_position)
    {
        set_position(m_position + shift_position);
    }

    void set_rotation(float angle)
    {
        m_angle = angle;
        need_update();
    };

    void change_rotation(float shift_angle)
    {
        set_rotation(m_angle + shift_angle);
    }

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