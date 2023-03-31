#include <MaRasterizer.hpp>
#include <Debug.hpp>
#include <vector>

class TestRasterizer : public MaRasterizer
{
public:

    TestRasterizer(int Width, int Height) : MaRasterizer(Width, Height) {}

    virtual void update_scene()
    {
        sf::Vector3f 
            vAf = {-2, -0.5, 5},
            vBf = {-2,  0.5, 5},
            vCf = {-1,  0.5, 5},
            vDf = {-1, -0.5, 5},

            // The four "back" vertices
            vAb = {-2, -0.5, 6},
            vBb = {-2,  0.5, 6},
            vCb = {-1,  0.5, 6},
            vDb = {-1, -0.5, 6};

        draw_line(ProjectOnPixel(vAf), ProjectOnPixel(vBf), sf::Color::Blue);
        draw_line(ProjectOnPixel(vBf), ProjectOnPixel(vCf), sf::Color::Blue);
        draw_line(ProjectOnPixel(vCf), ProjectOnPixel(vDf), sf::Color::Blue);
        draw_line(ProjectOnPixel(vDf), ProjectOnPixel(vAf), sf::Color::Blue);

        draw_line(ProjectOnPixel(vAb), ProjectOnPixel(vAf), sf::Color::Magenta);
        draw_line(ProjectOnPixel(vBb), ProjectOnPixel(vBf), sf::Color::Magenta);
        draw_line(ProjectOnPixel(vCb), ProjectOnPixel(vCf), sf::Color::Magenta);
        draw_line(ProjectOnPixel(vDb), ProjectOnPixel(vDf), sf::Color::Magenta);

        draw_line(ProjectOnPixel(vAb), ProjectOnPixel(vBb), sf::Color::Cyan);
        draw_line(ProjectOnPixel(vBb), ProjectOnPixel(vCb), sf::Color::Cyan);
        draw_line(ProjectOnPixel(vCb), ProjectOnPixel(vDb), sf::Color::Cyan);
        draw_line(ProjectOnPixel(vDb), ProjectOnPixel(vAb), sf::Color::Cyan);
    }
};

int main(int argc, const char* argv[])
{
    TestRasterizer test_rasterizer(500, 500);

    test_rasterizer.update_scene();
    test_rasterizer.save_scene();

    return 0;
}