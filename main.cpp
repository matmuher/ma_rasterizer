#include <iostream>
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

    MaRasterizer(int Width = 1280, int Height = 720);
    
    void update_scene()
    {
        for (int x = 0; x < m_Width; ++x)
            for (int y = 0; y < m_Height; ++y)
            {
                if (x < m_Width/2 && y < m_Height/2)
                    image.setPixel(x, y, sf::Color::Blue);
            }
    }

    void draw_scene() const;

    void save_scene() const;
};

MaRasterizer::MaRasterizer(int Width, int Height)
    :
        m_Width{Width},
        m_Height{Height},
        window{sf::VideoMode(m_Width, m_Height), "ma_rasterizer"}
{
    image.create(m_Width, m_Height, sf::Color::Red);
}

void MaRasterizer::draw_scene() const
{
    sf::Texture texture;
    texture.loadFromImage(image);

    sf::Sprite sprite;
    sprite.setTexture(texture);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(sprite);
        window.display();
    }
}

void MaRasterizer::save_scene() const
{
    image.saveToFile(file_name);
}

int main()
{
    MaRasterizer ma_rasterizer;

    ma_rasterizer.update_scene();
    ma_rasterizer.draw_scene();

    return 0;
}