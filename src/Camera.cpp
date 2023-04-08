#include <MaRasterizer.hpp>
#include <Debug.hpp>

sf::Vector3f vec_move(sf::Vector3f src, const sf::Vector3f& move_vector)
{
    return src += move_vector;
}

sf::Vector3f vec_rotate_y(sf::Vector3f vec, float rotate_angle)
{
    return {
            vec.x * cosf(deg2rad(rotate_angle)) + vec.z * sinf(deg2rad(rotate_angle)),
            vec.y,
            -vec.x * sinf(deg2rad(rotate_angle)) + vec.z * cosf(deg2rad(rotate_angle))
            };
}

sf::Vector3f vec_transform(sf::Vector3f vec, float rotate_angle, const sf::Vector3f& move_vector)
{
    vec = vec_rotate_y(vec, rotate_angle);

    std::cout << "Rotated vector: " << vec << '\n';

    vec = vec_move(vec, move_vector);

    return vec;
}

void MaRasterizer::update_camera_transform()
{
    info() << "translation vector: " << translation_vec << '\n';
    info() << "angle: " << rotate_angle << '\n';

    camera_transform = 
            create_translation_matrix(-translation_vec)
            * 
            create_rotation_y_matrix(deg2rad(-rotate_angle));
    
    is_camera_need_update = false;
}


void MaRasterizer::set_camera_rotation(float angle)
{
    rotate_angle = angle;
    is_camera_need_update = true;
}

void MaRasterizer::set_camera_translation(sf::Vector3f vec)
{
    translation_vec = vec;
    is_camera_need_update = true;
}