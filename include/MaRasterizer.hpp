#pragma once

#include <string>
#include <array>
#include <vector>
#include <SFML/Graphics.hpp>
#include <Interpolation.hpp>
#include <Camera.hpp>
#include <Model.hpp>
#include <Geometry.hpp>
#include <Updater.hpp>

enum class RenderMode
{
    Window,
    Picture
};

struct ScreenSubstrate
{
    std::vector<std::vector<float>> vec;

    ScreenSubstrate(int Width, int Height, float filler)
    :
        vec(Height, std::vector<float>(Width, filler))
    {}

    void setPixel(int x, int y, float val)
    {
        vec[y][x] = val;
    }
};

class MaRasterizer
{
protected:

    Updater updater;

    Camera camera;

// [interactive]

    const float StdRotateAngle = 1.0;

    const float StdShiftLen = 0.2;

private:

// [implementation details]

    mutable sf::RenderWindow window;

    sf::Image image;
    ScreenSubstrate z_buffer;

    const std::string file_name = "querida_triangulo.png"; 

    RenderMode m_mode;

public:

// [CTOR]

    MaRasterizer(   int Width = 1000,
                    int Height = 1000,
                    float ViewPortDistance = 1.,
                    float ViewPortWidth = 1.,
                    float ViewPortHeight = 1.,
                    RenderMode mode = RenderMode::Picture);
    
// [DRAWING]

    inline bool is_in_borders(int x, int y) const;

    void setPixel(int x, int y, const sf::Color& color);

    void draw_line(sf::Vector2i P0, sf::Vector2i P1, sf::Color color);
    
    void draw_triangle(sf::Vector2i P0, sf::Vector2i P1, sf::Vector2i P2, sf::Color color);
    
    void fill_triangle(sf::Vector2i P0, sf::Vector2i P1, sf::Vector2i P2, sf::Color color);

    void fill_triangle( sf::Vector2i P0, float h0,
                        sf::Vector2i P1, float h1,
                        sf::Vector2i P2, float h2,
                        sf::Color color);

    void rasterize_triangle(    sf::Vector2i P0, Dict<Attribute, float> P0_attr,
                                sf::Vector2i P1, Dict<Attribute, float> P1_attr,
                                sf::Vector2i P2, Dict<Attribute, float> P2_attr,
                                sf::Color color);

    void draw_instance_complete(const Instance& instance);
    void draw_instance_clip(const Instance& instance);
    void draw_instance(const Instance& instance);

// [SCENE MANAGING]

    void process_key(sf::Keyboard::Key key);

    void clear_scene();

    virtual void update_scene() = 0;

    void render_scene();

    void save_scene() const;
};

// [USEFUL]

inline float clamp(float num)
{
    if (num < 0)
        return 0;

    if (num > 1)
        return 1;

    return num;
}

inline sf::Color shade(const sf::Color& clr, float h);

void sort_by_y(sf::Vector2i& P0, sf::Vector2i& P1, sf::Vector2i& P2);

void sort_by_y( sf::Vector2i& P0, float& h0,
                sf::Vector2i& P1, float& h1,
                sf::Vector2i& P2, float& h2);
