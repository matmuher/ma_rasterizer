#include <MaRasterizer.hpp>

// [PROJECT ON VIEW PORT]

float MaRasterizer::project_component(float component, float z) const
{
    return component * (-m_ViewPortDistance) / z;
}

sf::Vector2f MaRasterizer::ProjectOnViewPort(const sf::Vector3f& pnt) const
{
    return sf::Vector2f(project_component(pnt.x, pnt.z), project_component(pnt.y, pnt.z));
}