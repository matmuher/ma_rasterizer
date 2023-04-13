#include <vector>
#include <cassert>
#include <unistd.h>
#include <MaRasterizer.hpp>
#include <Debug.hpp>
#include <Clipping.hpp>
#include <CoordsTransform.hpp>

// [CTOR]

MaRasterizer::MaRasterizer( int Width, int Height,
                            float ViewPortDistance,
                            float ViewPortWidth, float ViewPortHeight, 
                            RenderMode mode)
    :
        camera  { 
                updater,
                Width,
                Height,
                ViewPortDistance,
                ViewPortWidth,
                ViewPortHeight,
                0,
                {0, 0, 0}
                }
{
    image.create(camera.get_width(), camera.get_height(), sf::Color::White);

    camera.update();

    if (mode == RenderMode::Window)
        window.create(sf::VideoMode(camera.get_width(), camera.get_height()), "ma_rasterizer");
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
    return  (0 <= x)  && (x < camera.get_width()) &&
            (0 <= y)  && (y < camera.get_height());
}

void MaRasterizer::setPixel(int x, int y, const sf::Color& color)
{
    if (is_in_borders(x, y))
    {
        image.setPixel(x, y, color);
    }
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

void MaRasterizer::draw_instance(const Instance& instance)
{
    const Model& model = instance.get_model();

    if (is_bounding_sphere_out_of_fov(camera, instance))
    {
        return;
    }

    std::vector<sf::Vector3f> updated_vertices = model.vertices;
    for (auto& vertex : updated_vertices)
    {
        vertex = transformToScene(camera, instance, vertex);
    }

    for (const auto& triangle : instance.get_model().triangles)
    {
        draw_triangle(  transformCompletely(camera,
                                            instance,
                                            model.vertices[triangle.a]),

                        transformCompletely(camera,
                                            instance,
                                            model.vertices[triangle.b]),

                        transformCompletely(camera,
                                            instance,
                                            model.vertices[triangle.c]),
                        
                        triangle.clr);
    }
}

// [SCENE MANAGING]

void MaRasterizer::clear_scene()
{
    for (int y = 0; y < camera.get_height(); ++y)
        for (int x = 0; x < camera.get_width(); ++x)
        {
            setPixel(x, y, sf::Color::White);
        }
}

void MaRasterizer::render_scene()
{
    sf::Texture texture;

    sf::Sprite sprite;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        clear_scene();
        update_scene();

        texture.loadFromImage(image);
        sprite.setTexture(texture);

        window.clear();
        window.draw(sprite);
        window.display();
    }
}

void MaRasterizer::save_scene() const
{
    image.saveToFile(file_name);
}
