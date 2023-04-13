#pragma once

#include <vector>
#include <Camera.hpp>
#include <Model.hpp>

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