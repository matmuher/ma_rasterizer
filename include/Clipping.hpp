#pragma once

#include <vector>
#include <Camera.hpp>
#include <Model.hpp>

bool is_bounding_sphere_out_of_fov( const Camera& camera,
                            const Instance& instance);

std::vector<TriangleVertices> clip_instance(const Camera& camera,
                                            const Instance& instance);

// transformation to position in scene (instance transform + camera transform)
sf::Vector3f map_to_scene(  const Camera& camera,    
                            const Mat4f& instance_transform,
                            const sf::Vector3f& point);
