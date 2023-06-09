#include <Debug.hpp>
#include <Geometry.hpp>

std::ostream& operator<< (std::ostream& cout, sf::Vector2i P)
{
    return cout << '(' << P.x << ',' << P.y << ')';
}

std::ostream& operator<< (std::ostream& cout, sf::Vector3f P)
{
    return cout << '(' << P.x << ',' << P.y << ',' << P.z << ')';
}

std::ostream& operator<< (std::ostream& cout, sf::Vector2f P)
{
    return cout << '(' << P.x << ',' << P.y << ')';
}

std::ostream& operator<< (std::ostream& cout, Sphere sphere)
{
    return cout << "Sphere: " << sphere.center << ", R = " << sphere.R;
}

std::ostream& operator<< (std::ostream& cout, sf::Color clr)
{
    return cout << '('  << unsigned(clr.r) << ','
                        << unsigned(clr.g) << ','
                        << unsigned(clr.b) << ','
                        << unsigned(clr.a) << ')'; 
}

std::ostream& info()
{
    return std::cout << "[info] ";
}

void print_vector(const std::vector<float>& vec, std::size_t num)
{
    for (std::size_t i = 0; i < vec.size() && i < num; ++i)
        std::cout << vec[i] << ' ';

    std::cout << '\n'; 
}

void head_vector(const std::vector<float>& vec)
{
    print_vector(vec, 10);
}