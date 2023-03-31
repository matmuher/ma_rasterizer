#include <MaRasterizer.hpp>

// [CONVERTION]

sf::Vector2i MaRasterizer::CanvasToPixel(const sf::Vector2i& cnvs_pnt) const
{
    return sf::Vector2i {
                        m_Width  / 2 + cnvs_pnt.x,
                        m_Height / 2 - cnvs_pnt.y
                        };
}

sf::Vector2i MaRasterizer::ViewPortToCanvas(const sf::Vector2f& view_port_pnt) const
{
    return sf::Vector2i {
                        view_port_pnt.x / m_ViewPortWidth * m_Width,
                        view_port_pnt.y / m_ViewPortHeight * m_Height
                        };
}

sf::Vector2i MaRasterizer::ViewPortToPixel(const sf::Vector2f& view_port_pnt) const
{
    return CanvasToPixel(ViewPortToCanvas(view_port_pnt));
}
