#include <MaRasterizer.hpp>

MaRasterizer::MaRasterizer(int Width, int Height)
    :
        m_Width{Width},
        m_Height{Height},
        window{sf::VideoMode(m_Width, m_Height), "ma_rasterizer"}
{
    image.create(m_Width, m_Height, sf::Color::White);
}

void MaRasterizer::update_scene()
{
    draw_line(sf::Vector2i{0, 0}, sf::Vector2i{10, 90}, sf::Color::Red);
}

void MaRasterizer::draw_line(sf::Vector2i P0, sf::Vector2i P1, sf::Color color)
{
    float slope = float(P1.y - P0.y) / (P1.x - P0.x);
    float y = P0.y;

    info() << P0 << ' ' << P1 << '\n';
    info() << "slope: " << slope << '\n';

    for (int x = P0.x; x < P1.x; ++x)
    {
        y += slope;
        image.setPixel(x, y, color);
    }

    info() << y << '\n';
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

std::ostream& operator<< (std::ostream& cout, sf::Vector2i P)
{
    return cout << '(' << P.x << ',' << P.y << ')';
}

std::ostream& info()
{
    return std::cout << "[info] ";
}