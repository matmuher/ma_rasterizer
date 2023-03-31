#pragma once

#include <vector>
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

extern Model cube;