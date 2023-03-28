#include <MaRasterizer.hpp>

class TestRasterizer : public MaRasterizer
{
public:

    TestRasterizer(int Width, int Height) : MaRasterizer(Width, Height) {}

    virtual void update_scene()
    {
        sf::Vector2i P0{10, 10}, P1{20, 20}, P2{10, 30};

        fill_triangle(P1, P0, P2, sf::Color::Cyan);

        draw_triangle(P0, P1, P2, sf::Color::Cyan);

        // draw_line({10, 10},{10, 80}, sf::Color::Green);
        // draw_line({10, 10},{80, 10}, sf::Color::Red);
    }
};

int main()
{
    TestRasterizer test_rasterizer(90, 90);

    test_rasterizer.update_scene();
    test_rasterizer.save_scene();

    return 0;
}