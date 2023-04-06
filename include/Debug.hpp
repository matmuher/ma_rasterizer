#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

std::ostream& operator<< (std::ostream& cout, sf::Vector2i P);
std::ostream& operator<< (std::ostream& cout, sf::Vector2f P);
std::ostream& operator<< (std::ostream& cout, sf::Vector3f P);

std::ostream& operator<< (std::ostream& cout, sf::Color clr);

std::ostream& info();

void print_vector(const std::vector<float>& vec, std::size_t num);

void head_vector(const std::vector<float>& vec);
