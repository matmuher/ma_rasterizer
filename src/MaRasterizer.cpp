#include <vector>
#include <cassert>
#include <MaRasterizer.hpp>
#include <Debug.hpp>

// [CTOR]

MaRasterizer::MaRasterizer( int Width, int Height,
                            float ViewPortDistance,
                            float ViewPortWidth, float ViewPortHeight, 
                            bool window_mode)
    :
        m_Width{Width},
        m_Height{Height},
        m_ViewPortDistance{ViewPortDistance},
        m_ViewPortWidth{ViewPortWidth},
        m_ViewPortHeight{ViewPortHeight}
{
    image.create(m_Width, m_Height, sf::Color::White);

    if (window_mode)
        window.create(sf::VideoMode(m_Width, m_Height), "ma_rasterizer");
}

// [SORT]

inline bool is_less_by_y(sf::Vector2i lhs, sf::Vector2i rhs)
{
    return lhs.y < rhs.y;
}

void sort_by_y(sf::Vector2i& P0, sf::Vector2i& P1, sf::Vector2i& P2)
{
    // unrolled bubble
    
    if (!is_less_by_y(P0, P1)) std::swap(P0, P1);
    if (!is_less_by_y(P1, P2)) std::swap(P1, P2);
    if (!is_less_by_y(P0, P1)) std::swap(P0, P1);
}

void sort_by_y( sf::Vector2i& P0, float& h0,
                sf::Vector2i& P1, float& h1,
                sf::Vector2i& P2, float& h2)
{
    if (!is_less_by_y(P0, P1))
    {
        std::swap(P0, P1);
        std::swap(h0, h1);
    }

    if (!is_less_by_y(P1, P2))
    {
        std::swap(P1, P2);
        std::swap(h1, h2);
    }

    if (!is_less_by_y(P0, P1))
    {
        std::swap(P0, P1);
        std::swap(h0, h1);
    }
}

// [DRAWING]

inline bool MaRasterizer::is_in_borders(int x, int y) const
{
    return  (0 <= x)  && (x < m_Width) &&
            (0 <= y)  && (y < m_Height);
}

void MaRasterizer::setPixel(int x, int y, const sf::Color& color)
{
    if (is_in_borders(x, y))
    {
        image.setPixel(x, y, color);
    }
}

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
                                              float dep_st, float dep_end) const
{
    if (indep_st == indep_end)
        return {};

    std::vector<float> dep_values;

        // let i0 = 0, i1 = 1 -> all in all 2 pixels
        // i.e. (i1 - i0 + 1)
    int range_len_indep = indep_end - indep_st;
    float range_len_dep   = dep_end - dep_st;

    dep_values.reserve(range_len_indep);

        // slope shows how much should we move in dependent-axis
        // when move one step in independent axis
    float slope = range_len_dep / range_len_indep; 
    
    float dep_walker = dep_st;
    for (int indep_walker = 0; indep_walker <= range_len_indep; ++indep_walker)
    {
        dep_walker += slope;
        dep_values.push_back(dep_walker);
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

   info() << P0 << "-->" << P1 << '\n';

    if (abs(P1.x - P0.x) >= abs(P1.y - P0.y))
    {
        info() << "x is independent\n";

        if (P1.x - P0.x < 0)
        {
            info() << "swap\n";
            std::swap(P0, P1);
        }

        std::vector<float> y_values = interpolate(P0.x, P1.x, P0.y, P1.y);

        // for (auto elem : y_values)
        //     info() << elem << ' ';
        // info() << '\n';

        for (int x = P0.x; x < P1.x; ++x)
        {
            setPixel(x, y_values[x - P0.x], color);
        }
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

        // for (auto elem : x_values)
        //     info() << elem << ' ';
        // info() << '\n';

        for (int y = P0.y; y < P1.y; ++y)
            setPixel(x_values[y - P0.y], y, color);
    }
}

void MaRasterizer::draw_triangle(sf::Vector2i P0, sf::Vector2i P1,
                                 sf::Vector2i P2, sf::Color color)
{
    draw_line(P0, P1, color);
    draw_line(P1, P2, color);
    draw_line(P2, P0, color);
}

void MaRasterizer::fill_triangle(sf::Vector2i P0, sf::Vector2i P1,
                                 sf::Vector2i P2, sf::Color color)
{
    sort_by_y(P0, P1, P2);

    info() << P0 << P1 << P2 << '\n';

    // for every Y wanna have appropriate X
    // -> cinsider Y as independent parameter
    std::vector<float> x01 = interpolate(P0.y, P1.y, P0.x, P1.x);
    std::vector<float> x12 = interpolate(P1.y, P2.y, P1.x, P2.x);
    std::vector<float> x02 = interpolate(P0.y, P2.y, P0.x, P2.x);

    if (x01.empty()) info() << "empty!\n";

    for (auto elem : x01)
        info() << elem << ' ';
    info() << '\n';

    for (auto elem : x12)
        info() << elem << ' ';
    info() << '\n';

    for (auto elem : x02)
        info() << elem << ' ';
    info() << '\n';

    for (int y_walker = P0.y; y_walker < P1.y; ++y_walker)
    {
        info() << "P0 - P1: " <<  y_walker << '\n';

        int x1 = int(x01[y_walker - P0.y]);
        int x2 = int(x02[y_walker - P0.y]);

        info() << "xs: " << x1 << ' ' << x2 << '\n';

        draw_line({x1, y_walker}, {x2, y_walker}, color);
    }

    for (int y_walker = P1.y; y_walker < P2.y; ++y_walker)
    {
        info() << "P1 - P2: " <<  y_walker << '\n';

        int x1 = int(x12[y_walker - P1.y]);
        int x2 = int(x02[y_walker - P0.y]);

        info() << "xs: " << x1 << ' ' << x2 << '\n';

        draw_line({x1, y_walker}, {x2, y_walker}, color);
    }
}

void MaRasterizer::draw_model(const Model& model)
{
    for (const auto& triangle : model.triangles)
    {
        draw_triangle(  ProjectOnPixel(model.vertices[triangle.a]),
                        ProjectOnPixel(model.vertices[triangle.b]),
                        ProjectOnPixel(model.vertices[triangle.c]),
                        triangle.clr);
    }
}

void MaRasterizer::draw_instance(const Instance& instance)
{
    for (const auto& triangle : instance.model.triangles)
    {
        draw_triangle(  ProjectOnPixel(instance.model.vertices[triangle.a] + instance.position),
                        ProjectOnPixel(instance.model.vertices[triangle.b] + instance.position),
                        ProjectOnPixel(instance.model.vertices[triangle.c] + instance.position),
                        triangle.clr);
    }
}

// [SCENE MANAGING]

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
