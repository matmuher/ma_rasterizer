#include <Debug.hpp>

std::ostream& operator<< (std::ostream& cout, sf::Vector2i P)
{
    return cout << '(' << P.x << ',' << P.y << ')';
}

std::ostream& info()
{
    return std::cout << "[info] ";
}