#include <Model.hpp>

const Model cube =
{
    .vertices =
    {
        { 1,  1,  1},
        {-1,  1,  1},
        {-1, -1,  1},
        { 1, -1,  1},
        { 1,  1, -1},
        {-1,  1, -1},
        {-1, -1, -1},
        { 1, -1, -1}
    },

    .triangles =
    {
        {0, 1, 2, sf::Color::Red},
        {0, 2, 3, sf::Color::Red},
        {4, 0, 3, sf::Color::Green},
        {4, 3, 7, sf::Color::Green},
        {5, 4, 7, sf::Color::Blue},
        {5, 7, 6, sf::Color::Blue},
        {1, 5, 6, sf::Color::Yellow},
        {1, 6, 2, sf::Color::Yellow},
        {4, 5, 1, sf::Color::Magenta},
        {4, 1, 0, sf::Color::Magenta},
        {2, 6, 7, sf::Color::Cyan},
        {2, 7, 3, sf::Color::Cyan}
    }
};