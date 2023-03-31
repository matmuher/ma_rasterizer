#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <array>

class MaRasterizer
{
    const int m_Width;
    const int m_Height;

    const float m_ViewPortWidth;
    const float m_ViewPortHeight;

    mutable sf::RenderWindow window;

    sf::Image image;

    const std::string file_name = "querida_triangulo.png"; 

public:

// [CTOR]

    MaRasterizer(   int Width = 1000,
                    int Height = 1000,
                    float ViewPortWidth = 1.,
                    float ViewPortHeight = 1., 
                    bool window_mode = false);
    
// [DRAWING]

    std::vector<float> interpolate(int indep_st, int indep_end,
                                   float dep_st, float dep_end) const;

    void draw_line(sf::Vector2i P0, sf::Vector2i P1, sf::Color color);
    
    void draw_triangle(sf::Vector2i P0, sf::Vector2i P1, sf::Vector2i P2, sf::Color color);
    
    void fill_triangle(sf::Vector2i P0, sf::Vector2i P1, sf::Vector2i P2, sf::Color color);

    void fill_triangle( sf::Vector2i P0, float h0,
                        sf::Vector2i P1, float h1,
                        sf::Vector2i P2, float h2,
                        sf::Color color);

// [CONVERTION]

sf::Vector2i CanvasToPixel(const sf::Vector2i& cnvs_pnt);
sf::Vector2i ViewPortToCanvas(const sf::Vector2f& view_port_pnt);
sf::Vector2i ViewPortToPixel(const sf::Vector2f& view_port_pnt);

// [SCENE MANAGING]

    virtual void update_scene() = 0;

    void show_scene() const;

    void save_scene() const;
};

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