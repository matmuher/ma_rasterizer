#include <MaRasterizer.hpp>
#include <Debug.hpp>
#include <vector>

class TestRasterizer : public MaRasterizer
{
public:

    TestRasterizer(int Width, int Height) : MaRasterizer(Width, Height, 1, 1, 1, true) {}

    virtual void update_scene()
    {
        static float angle = 0.00001;
        Instance cube1{cube, {-4, 0, -15}, angle, 1.5};
        angle += 3;
        Instance cube2{cube, {4, 0, -15}, -90, 1};

        draw_instance(cube1);
        draw_instance(cube2);

    }
};

int main()
{
    TestRasterizer test_rasterizer(500, 500);

    test_rasterizer.update_scene();

    test_rasterizer.render_scene();
    test_rasterizer.save_scene();

    return 0;
}