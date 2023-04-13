#pragma once

#include <vector>
#include <Camera.hpp>
#include <Model.hpp>

/*
    Clipping is trivial.
    Consdier intersection only with the only - first intersected plane.
    
    I think it's not critical as it's only a technical issue
    to catch all intersections and pop right number of trinagles.
*/

enum class IntersectStatus
{
    OUT,
    IN,
    INTERSECT
};

IntersectStatus is_bounding_sphere_intersect_fov( const Camera& camera,
                            const Instance& instance);

std::vector<TriangleVertices> clip_instance(const Camera& camera,
                                            const Instance& instance);


std::vector<SceneTriangle> clip_triangle(   const std::vector<Plane>& fov_planes,
                                            const SceneTriangle& striangle);