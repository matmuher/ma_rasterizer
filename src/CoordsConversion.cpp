#include <MaRasterizer.hpp>

// [CONVERTION]

sf::Vector2i MaRasterizer::transform_point( const Mat4f& instance_transform,
                                            const sf::Vector3f& point) const
{
    return ::transform_point(   camera.get_camera_transform(),
                                instance_transform,
                                camera.get_project_transform(),
                                point);
}

sf::Vector3f map_to_scene(  const Camera& camera,
                            const Mat4f& instance_transform,
                            const sf::Vector3f& point)
{
    return ::transform_point(   camera.get_camera_transform(),
                                instance_transform,
                                point);    
}
