#include <SFML/Graphics.hpp>
#include <Camera.hpp>
#include <Model.hpp>
#include <LinearAlgebra.hpp>
#include <Geometry.hpp>

sf::Vector2i transformCompletely(   const Camera& camera,
                                    const Instance& instance,
                                    const sf::Vector3f& point)
{
    Mat3x4f transform_mat;
    
    transform_mat <<    0., 0., 0., 0.,
                        0., 0., 0., 0.,
                        0., 0., 0., 0.;

    transform_mat = camera.get_project_transform()
                    *
                    camera.get_camera_transform()
                    *
                    instance.get_instance_transform();
 
    Vec4f homogeneous_point_3d{point.x, point.y, point.z, 1};

    Vec3f homogeneous_point_2d = transform_mat * homogeneous_point_3d;

    sf::Vector2f pixel_array_point_f =  homogeneous_to_cartesian_2d(
                                                                    homogeneous_point_2d(0),
                                                                    homogeneous_point_2d(1),
                                                                    homogeneous_point_2d(2)
                                                                    );

    return sf::Vector2i{int(pixel_array_point_f.x), int(pixel_array_point_f.y)};
}

sf::Vector3f transformToScene(  const Camera& camera,
                                const Instance& instance,
                                const sf::Vector3f& point)
{
    Mat4f transform_mat = camera.get_camera_transform() * instance.get_instance_transform();

    Vec4f homogeneous_point{point.x, point.y, point.z, 1};

    Vec4f transformed_homogeneous_point= transform_mat * homogeneous_point;  

    return sf::Vector3f{transformed_homogeneous_point(0),
                        transformed_homogeneous_point(1),
                        transformed_homogeneous_point(2)}; 
}
