#pragma once

#include <vector>
#include <cmath>
#include <SFML/Graphics.hpp>

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
};

struct Instance
{
    const Model& model;
    
    sf::Vector3f position{0, 0, 0};
    float rotate_angle{0};
    float scale{1};

    sf::Vector3f transform(const sf::Vector3f vec) const;
    sf::Vector3f rotate_y(const sf::Vector3f vec) const;
};

inline float deg2rad(float deg)
{
    return deg / 180. * M_PI;
}

extern const Model cube;