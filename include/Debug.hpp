#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

std::ostream& operator<< (std::ostream& cout, sf::Vector2i P);

std::ostream& info();
