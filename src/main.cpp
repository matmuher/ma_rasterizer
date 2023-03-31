#include <MaRasterizer.hpp>
#include <Debug.hpp>
#include <vector>

class TestRasterizer : public MaRasterizer
{
public:

    TestRasterizer(int Width, int Height) : MaRasterizer(Width, Height) {}

    virtual void update_scene()
    {
        Instance cube1{cube, {-4, 0, -15}};
        Instance cube2{cube, {4, 0, -15}};

        draw_instance(cube1);
        draw_instance(cube2);

        // fill_triangle({50, 50}, {50, 0}, {150, 25}, sf::Color::Blue);
    }
};

int main()
{
    TestRasterizer test_rasterizer(500, 500);

    test_rasterizer.update_scene();
    test_rasterizer.save_scene();

    return 0;
}