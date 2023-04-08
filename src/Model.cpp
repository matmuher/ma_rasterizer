#include <Model.hpp>
#include <cmath>

void Model::move(sf::Vector3f move_vector)
{
    for (auto& vertex : vertices)
    {
        vertex += move_vector;
    }
}

sf::Vector3f Instance::transform(const sf::Vector3f vec) const
{
    sf::Vector3f transformed_vec = vec;

    transformed_vec = rotate_y(transformed_vec);
    transformed_vec *= scale;
    transformed_vec += position;

    return transformed_vec;
}

sf::Vector3f Instance::rotate_y(const sf::Vector3f vec) const
{
    return {
            vec.x * cosf(deg2rad(rotate_angle)) + vec.z * sinf(deg2rad(rotate_angle)),
            vec.y,
            -vec.x * sinf(deg2rad(rotate_angle)) + vec.z * cosf(deg2rad(rotate_angle))
            };
    // return vec;
}

const Model cube =
{
    .vertices =
    {
        { 1,  1,  1},
        {-1,  1,  1},
        {-1, -1,  1},
        { 1, -1,  1},
        { 1,  1, -1},
        {-1,  1, -1},
        {-1, -1, -1},
        { 1, -1, -1}
    },

    .triangles =
    {
        {0, 1, 2, sf::Color::Red},
        {0, 2, 3, sf::Color::Red},
        {4, 0, 3, sf::Color::Green},
        {4, 3, 7, sf::Color::Green},
        {5, 4, 7, sf::Color::Blue},
        {5, 7, 6, sf::Color::Blue},
        {1, 5, 6, sf::Color::Yellow},
        {1, 6, 2, sf::Color::Yellow},
        {4, 5, 1, sf::Color::Magenta},
        {4, 1, 0, sf::Color::Magenta},
        {2, 6, 7, sf::Color::Cyan},
        {2, 7, 3, sf::Color::Cyan}
    }
};