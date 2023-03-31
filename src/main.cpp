#include <MaRasterizer.hpp>
#include <Debug.hpp>

class TestRasterizer : public MaRasterizer
{
public:

    TestRasterizer(int Width, int Height) : MaRasterizer(Width, Height) {}

    virtual void update_scene()
    {
        sf::Vector2i P0{81, 9}, P1{9, 9}, P2{45, 81};
        sf::Vector2f P0f{-0.5, 0.5}, P1f{0.5, 0.5}, P2f{0, -0.5};
        sf::Vector3f P0f3{0, 0, -1}, P1f3{0, 0.5, -1}, P2f3{0.5, 0, -1};

        P0f = ProjectOnViewPort(P0f3);
        P1f = ProjectOnViewPort(P1f3);
        P2f = ProjectOnViewPort(P2f3);

        std::cout << "After projecting: " << P0f << ' ' << P1f << ' ' << P2f << '\n';

        P0 = ViewPortToPixel(P0f);
        P1 = ViewPortToPixel(P1f);
        P2 = ViewPortToPixel(P2f);

        std::cout << "VP -> Pixel: " << P0 << ' ' << P1 << ' ' << P2 << '\n';

        //exit(1);

        fill_triangle(P1, 1, P0, 1, P2, 0, sf::Color::Cyan);

        // draw_triangle(P0, P1, P2, sf::Color::Black);

        draw_line({0, 0},{90, 90}, sf::Color::Green);
        draw_line({90, 0},{0, 90}, sf::Color::Red);
    }
};

int main(int argc, const char* argv[])
{
    TestRasterizer test_rasterizer(90, 90);

    test_rasterizer.update_scene();
    test_rasterizer.save_scene();

    return 0;
}