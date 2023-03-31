#include <MaRasterizer.hpp>
#include <Debug.hpp>
#include <vector>

class TestRasterizer : public MaRasterizer
{
public:

    TestRasterizer(int Width, int Height) : MaRasterizer(Width, Height) {}

    virtual void update_scene()
    {
        draw_model(cube);
    }
};

int main(int argc, const char* argv[])
{
    cube.move({0, 0, -5});
    TestRasterizer test_rasterizer(500, 500);

    test_rasterizer.update_scene();
    test_rasterizer.save_scene();

    return 0;
}