#include <MaRasterizer.hpp>

int main()
{
    MaRasterizer ma_rasterizer(100, 100);

    ma_rasterizer.update_scene();
    ma_rasterizer.draw_scene();
    ma_rasterizer.save_scene();

    return 0;
}