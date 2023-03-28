#include <MaRasterizer.hpp>

class TestRasterizer : public MaRasterizer
{
public:

    TestRasterizer(int Width, int Height) : MaRasterizer(Width, Height) {}

    virtual void update_scene()
    {
        draw_line(sf::Vector2i{0, 0}, sf::Vector2i{20, 90}, sf::Color::Red);

        draw_line(sf::Vector2i{0, 0}, sf::Vector2i{90, 90}, sf::Color::Green);

        draw_line(sf::Vector2i{0, 0}, sf::Vector2i{90, 10}, sf::Color::Blue);
    }
};

int main()
{
    TestRasterizer test_rasterizer(90, 90);

    test_rasterizer.update_scene();
    test_rasterizer.save_scene();

    return 0;
}