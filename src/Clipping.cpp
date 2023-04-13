#include <Clipping.hpp>
#include <CoordsTransform.hpp>

bool is_bounding_sphere_out_of_fov( const Camera& camera,
                            const Instance& instance)
{
    Sphere bounding_sphere = instance.get_model().bounding_sphere;

    sf::Vector3f updated_center = transformToScene (camera,
                                                    instance,
                                                    bounding_sphere.center);

    const std::vector<Plane>& fov_planes = camera.get_fov_planes();

    float dist = 0;
    for (const auto& plane : fov_planes)
    {
        dist = std::min(compute_dist(updated_center, plane), dist);
    }

    if (dist < -bounding_sphere.R)
    {
        info() << "instance is out of view field: " << dist << '\n';
        return true;
    }

    return false;
}

std::vector<TriangleVertices> clip_triangle(const std::vector<Plane>& fov_planes,
                                            const sf::Vector3f& Pa,
                                            const sf::Vector3f& Pb,
                                            const sf::Vector3f& Pc)
{;
    // for (const auto& point)
    // {
    //     ;
    // }
    
    // for (const auto& plane : fov_planes)
    // {
    //     compute_dist();
    // }
} 

std::vector<TriangleVertices> clip_instance(const Camera& camera,
                                            const Instance& instance)
{
    std::vector<TriangleVertices> clipped_triangles;
    const std::vector<TriangleVertices>& orig_triangles = instance.get_model().triangles;

    clipped_triangles.reserve(orig_triangles.size() * 2);

    for (const auto& triangle : orig_triangles)
    {
        // clip_trinagle()


    }

    clipped_triangles.shrink_to_fit();
}