#include <MaRasterizer.hpp>
#include <Debug.hpp>

MaRasterizer::MaRasterizer(int Width, int Height, bool window_mode)
    :
        m_Width{Width},
        m_Height{Height}
{
    image.create(m_Width, m_Height, sf::Color::White);

    if (window_mode)
        window.create(sf::VideoMode(m_Width, m_Height), "ma_rasterizer");
}

#include <vector>

// general interpolation function:
/*
        ^ (dep)
        |
        |        ******
        |   *****
        |***
        - - - - - - - > (indep)
*/
std::vector<float>  MaRasterizer::interpolate(int indep_st, int indep_end,
                                              int dep_st, int dep_end) const
{
    std::vector<float> dep_values;

        // let i0 = 0, i1 = 1 -> all in all 2 pixels
        // i.e. (i1 - i0 + 1)
    int range_len_indep = indep_end - indep_st + 1;
    int range_len_dep   = dep_end - dep_st + 1;

    dep_values.reserve(range_len_indep);

        // slope shows how much should we move in dependent-axis
        // when move one step in independent axis
    float slope = float(range_len_dep) / range_len_indep; 
    
    float dep_walker = dep_st;
    for (int indep_walker = 0; indep_walker < range_len_indep; ++indep_walker)
    {
        dep_walker += slope;
        dep_values[indep_walker] = dep_walker;
    }

    return dep_values;
}

void MaRasterizer::draw_line(sf::Vector2i P0, sf::Vector2i P1, sf::Color color)
{
    /*
        As we interpolate with function y = f(x) - for every X there
        the only Y = f(X).
    
        If line is steep this approach leads to line with holes:

        ^ (Y)
        |  *
        |
        | *
        |
        |*
        - - - - - - - > (X)

        instead of:

        ^ (Y)
        |  *
        |  *
        | *
        | *
        |*
        - - - - - - - > (X)

        But this issue can be overcomed with swapping axis.
    */

    if (abs(P1.x - P0.x) >= abs(P1.y - P0.y))
    {
        info() << "x is independent\n";

        if (P1.x - P0.x < 0)
        {
            info() << "swap\n";
            std::swap(P0, P1);
        }

        std::vector<float> y_values = interpolate(P0.x, P1.x, P0.y, P1.y);

        for (int x = P0.x; x < P1.x; ++x)
            image.setPixel(x, y_values[x - P0.x], color);
    }
    else
    {
        info() << "y is independent\n";

        if (P1.y - P0.y < 0)
        {
            info() << "swap\n";
            std::swap(P0, P1);
        }

        std::vector<float> x_values = interpolate(P0.y, P1.y, P0.x, P1.x);

        for (int y = P0.y; y < P1.y; ++y)
            image.setPixel(x_values[y - P0.y], y, color);
    }
}

void MaRasterizer::draw_triangle(sf::Vector2i P0, sf::Vector2i P1,
                                 sf::Vector2i P2, sf::Color color)
{
    draw_line(P0, P1, color);
    draw_line(P1, P2, color);
    draw_line(P2, P0, color);
}

void MaRasterizer::show_scene() const
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
