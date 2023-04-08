#include <MaRasterizer.hpp>

// [CONVERTION]

sf::Vector2i MaRasterizer::transform_point( const Mat4f& instance_transform,
                                            const sf::Vector3f& point) const
{
    return ::transform_point(   camera.get_camera_transform(),
                                instance_transform,
                                camera.get_project_transform(),
                                point);
}

sf::Vector2i MaRasterizer::CanvasToPixel(const sf::Vector2i& cnvs_pnt) const
{
    return sf::Vector2i {
                        camera.get_width()  / 2 + cnvs_pnt.x,
                        camera.get_height() / 2 - cnvs_pnt.y
                        };
}

sf::Vector2i MaRasterizer::ViewPortToCanvas(const sf::Vector2f& view_port_pnt) const
{
    return sf::Vector2i {
                        int(view_port_pnt.x / camera.get_vp_width() * camera.get_width()),
                        int(view_port_pnt.y / camera.get_vp_height() * camera.get_height())
                        };
}

sf::Vector2i MaRasterizer::ViewPortToPixel(const sf::Vector2f& view_port_pnt) const
{
    return CanvasToPixel(ViewPortToCanvas(view_port_pnt));
}
