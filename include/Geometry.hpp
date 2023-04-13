#pragma once

#include <LinearAlgebra.hpp>

struct Sphere
{
    sf::Vector3f center;
    float R;
};

Sphere create_bounding_sphere(const std::vector<sf::Vector3f>& vertices);

struct Plane
{
    sf::Vector3f norm;
    float d; // distance from origin

    Plane(const sf::Vector3f& a_norm, float a_d); // a_ for argument
};

float compute_dist(const sf::Vector3f point, const Plane& plane);
