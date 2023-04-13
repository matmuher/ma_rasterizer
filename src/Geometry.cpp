#include <Geometry.hpp>

Sphere create_bounding_sphere(const std::vector<sf::Vector3f>& vertices)
{
    // center = mean(vertices)

    sf::Vector3f center{};

    for (const auto& vertex : vertices)
    {
        center += vertex;
    }

    center *= float(1. / vertices.size());

    // radius = dist_to_farthest_vertex(vertices)

    float R = 0;

    for (const auto& vertex : vertices)
    {
        R = std::max(R, square(vertex - center));
    }

    return Sphere{center, sqrtf(R)};
}

Plane::Plane(const sf::Vector3f& a_norm, float a_d)
:
    norm{normalize(a_norm)},
    d{a_d}
{
    info() << "norm: " << norm << '\n';
}

float compute_dist(const sf::Vector3f point, const Plane& plane)
{
    return dot_product(point, plane.norm) - plane.d;
}