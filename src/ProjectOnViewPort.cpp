#include <MaRasterizer.hpp>

// [PROJECT ON VIEW PORT]

float MaRasterizer::project_component(float component, float z) const
{
    return component * (-camera.get_vp_dist()) / z;
}

sf::Vector2f MaRasterizer::ProjectOnViewPort(const sf::Vector3f& pnt) const
{
    return sf::Vector2f(project_component(pnt.x, pnt.z), project_component(pnt.y, pnt.z));
}

sf::Vector2i MaRasterizer::ProjectOnPixel(const sf::Vector3f& pnt) const
{
    return ViewPortToPixel(ProjectOnViewPort(pnt));
}