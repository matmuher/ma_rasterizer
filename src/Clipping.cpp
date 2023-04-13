#include <Clipping.hpp>
#include <CoordsTransform.hpp>
#include <LinearAlgebra.hpp>
#include <Geometry.hpp>

IntersectStatus is_bounding_sphere_intersect_fov( const Camera& camera,
                                    const Instance& instance)
{
    Sphere bounding_sphere = instance.get_model().bounding_sphere;

    sf::Vector3f updated_center = transformToScene (camera,
                                                    instance,
                                                    bounding_sphere.center);

    const std::vector<Plane>& fov_planes = camera.get_fov_planes();

    float dist = INFINITY;
    for (const auto& plane : fov_planes)
    {
        dist = std::min(compute_dist(updated_center, plane), dist);
    }

    info() << dist << '\n';

    if (dist < (-bounding_sphere.R * instance.get_scale()))
    {
        info() << "instance OUT fov\n";
        return IntersectStatus::OUT;
    }
    else if (dist > (bounding_sphere.R * instance.get_scale()))
    {
        info() << "instance IN fov\n";
        return IntersectStatus::IN;
    }
    else
    {
        info() << "instance INTERSECT fov\n";
        return IntersectStatus::INTERSECT;   
    }

    info() << "cant't determine how instance is placed relative to fov planes\n";
    return IntersectStatus::OUT;
}

// TODO too big function!!!
std::vector<SceneTriangle> clip_triangle(   const std::vector<Plane>& fov_planes,
                                            const SceneTriangle& striangle)
{
    std::vector<SceneTriangle> clipped_triangles;

    std::array<sf::Vector3f, 3> points{striangle.a, striangle.b, striangle.c};

    std::vector<sf::Vector3f> in_fov_points, out_fov_points;

    in_fov_points.reserve(3);
    out_fov_points.reserve(3);

    const Plane* divider_plane_ptr{};
    bool is_divided{false};

    // Find 1st plane intersect
    for (const Plane& plane : fov_planes)
    {
        divider_plane_ptr = &plane;

        for (const auto& point : points)
        {
            float dist = compute_dist(point, plane);

            if (is_less(dist, 0))
            {
                out_fov_points.push_back(point);
                is_divided = true;
            }
            else
            {
                in_fov_points.push_back(point);
            }
        }

        if (is_divided)
        {
            break;
        }

        in_fov_points.clear();
        out_fov_points.clear();
    }

    std::size_t out_fov_num = out_fov_points.size();

    switch (out_fov_num)
    {
        case 0:
            {
                clipped_triangles.push_back(striangle);

                break;
            }
            
        case 1:
            {
                sf::Vector3f newA = compute_intersect(  in_fov_points[0],
                                                        *divider_plane_ptr,
                                                        out_fov_points[0]);

                sf::Vector3f newB = compute_intersect(  in_fov_points[1],
                                                        *divider_plane_ptr,
                                                        out_fov_points[0]);

                clipped_triangles.emplace_back( in_fov_points[0],
                                                newA,
                                                in_fov_points[1],
                                                striangle.clr);

                clipped_triangles.emplace_back( newA,
                                                newB,
                                                in_fov_points[1],
                                                striangle.clr);

                break;
            }

        case 2:
            {
                sf::Vector3f newB = compute_intersect(  in_fov_points[0],
                                                        *divider_plane_ptr,
                                                        out_fov_points[0]);

                sf::Vector3f newC = compute_intersect(  in_fov_points[0],
                                                        *divider_plane_ptr,
                                                        out_fov_points[1]);

                clipped_triangles.emplace_back(in_fov_points[0], newB, newC, striangle.clr);

                break;
            }

        case 3:
            
            clipped_triangles.clear();
            break;

        default:

            info() << "Invalid number of out of fov points: " << out_fov_num << '\n';
    } 

    clipped_triangles.shrink_to_fit();
    return clipped_triangles;
} 

// std::vector<TriangleVertices> clip_instance(const Camera& camera,
//                                             const Instance& instance)
// {
//     std::vector<TriangleVertices> clipped_triangles;
//     const std::vector<TriangleVertices>& orig_triangles = instance.get_model().triangles;

//     clipped_triangles.reserve(orig_triangles.size() * 2);

//     for (const auto& triangle : orig_triangles)
//     {
//         // clip_trinagle()


//     }

//     clipped_triangles.shrink_to_fit();

//     return clipped_triangles;
// }