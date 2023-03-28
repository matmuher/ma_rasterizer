#include <MaRasterizer.hpp>

class TestRasterizer : public MaRasterizer
{
public:

    TestRasterizer(int Width, int Height) : MaRasterizer(Width, Height) {}

    virtual void update_scene()
    {
        sf::Vector2i P0{10, 10}, P1{70, 50}, P2{35, 80};
        draw_triangle(P0, P1, P2, sf::Color::Cyan);
    }
};

int main()
{
    TestRasterizer test_rasterizer(90, 90);

    test_rasterizer.update_scene();
    test_rasterizer.save_scene();

    return 0;
}