#pragma once

#include <SFML/Graphics.hpp>
#include <Camera.hpp>
#include <Model.hpp>

/*
    Instance Transform
    +
    Camera Transform
    +
    Project Transform
*/
sf::Vector2i transformCompletely(   const Camera& camera,
                                    const Instance& instance,
                                    const sf::Vector3f& point);

/*
    Instance Transform
    +
    Camera Transform
*/
sf::Vector3f transformToScene(  const Camera& camera,
                                const Instance& instance,
                                const sf::Vector3f& point);
