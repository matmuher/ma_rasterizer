#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class MaRasterizer
{
    const int m_Width;
    const int m_Height;

    mutable sf::RenderWindow window;

    sf::Image image;

    const std::string file_name = "querida_triangulo.png"; 

public:

    MaRasterizer(int Width = 1280, int Height = 720, bool window_mode = false);
    
    virtual void update_scene() = 0;

    void draw_line(sf::Vector2i P0, sf::Vector2i P1, sf::Color color);

    void draw_scene() const;

    void save_scene() const;
};