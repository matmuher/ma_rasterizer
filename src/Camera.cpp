#include <MaRasterizer.hpp>
#include <Debug.hpp>

sf::Vector3f vec_move(sf::Vector3f src, const sf::Vector3f& move_vector)
{
    return src += move_vector;
}

sf::Vector3f vec_rotate_y(sf::Vector3f vec, float rotate_angle)
{
    return {
            vec.x * cos(deg2rad(rotate_angle)) + vec.z * sin(deg2rad(rotate_angle)),
            vec.y,
            -vec.x * sin(deg2rad(rotate_angle)) + vec.z * cos(deg2rad(rotate_angle))
            };
}

sf::Vector3f vec_transform(sf::Vector3f vec, float rotate_angle, const sf::Vector3f& move_vector)
{
    vec = vec_rotate_y(vec, rotate_angle);

    std::cout << "Rotated vector: " << vec << '\n';

    vec = vec_move(vec, move_vector);

    return vec;
}