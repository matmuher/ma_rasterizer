#pragma once

#include <string>
#include <array>
#include <vector>
#include <SFML/Graphics.hpp>
#include <Camera.hpp>
#include <Model.hpp>
#include <Homogeneous.hpp>
#include <Updater.hpp>

class MaRasterizer
{
protected:

    Updater updater;

    Camera camera;

private:

// [implementation details]

    mutable sf::RenderWindow window;

    sf::Image image;

    const std::string file_name = "querida_triangulo.png"; 

public:

// [CTOR]

    MaRasterizer(   int Width = 1000,
                    int Height = 1000,
                    float ViewPortDistance = 1.,
                    float ViewPortWidth = 1.,
                    float ViewPortHeight = 1., 
                    bool window_mode = false);
    
// [DRAWING]

    inline bool is_in_borders(int x, int y) const;

    void setPixel(int x, int y, const sf::Color& color);

    std::vector<float> interpolate(int indep_st, int indep_end,
                                   float dep_st, float dep_end) const;

    void draw_line(sf::Vector2i P0, sf::Vector2i P1, sf::Color color);
    
    void draw_triangle(sf::Vector2i P0, sf::Vector2i P1, sf::Vector2i P2, sf::Color color);
    
    void fill_triangle(sf::Vector2i P0, sf::Vector2i P1, sf::Vector2i P2, sf::Color color);

    void fill_triangle( sf::Vector2i P0, float h0,
                        sf::Vector2i P1, float h1,
                        sf::Vector2i P2, float h2,
                        sf::Color color);

    void draw_model(const Model& model);
    void draw_instance(const Instance& instance);

// [CONVERTION]

// complete transformation to pixel array
sf::Vector2i transform_point(   const Mat4f& instance_transform,
                                const sf::Vector3f& point) const;

sf::Vector2i CanvasToPixel(const sf::Vector2i& cnvs_pnt) const;
sf::Vector2i ViewPortToCanvas(const sf::Vector2f& view_port_pnt) const;
sf::Vector2i ViewPortToPixel(const sf::Vector2f& view_port_pnt) const;

// [PROJECT ON VIEW PORT : deprecated]

inline float project_component(float component, float z) const;
sf::Vector2f ProjectOnViewPort(const sf::Vector3f& pnt) const;
sf::Vector2i ProjectOnPixel(const sf::Vector3f& pnt) const;

// [SCENE MANAGING]

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

// [CLIPPING]


// transformation to position in scene (instance transform + camera transform)
sf::Vector3f map_to_scene(  const Camera& camera,    
                            const Mat4f& instance_transform,
                            const sf::Vector3f& point);

inline bool is_bounding_sphere_out_of_fov( const Camera& camera,
                            const Instance& instance)
{
    Sphere bounding_sphere = instance.get_model().bounding_sphere;
    const Mat4f& instance_transform = instance.get_instance_transform();

    sf::Vector3f updated_center = map_to_scene (camera,
                                                instance_transform,
                                                bounding_sphere.center);

    const std::vector<Plane>& fov_planes = camera.get_fov_planes();

    float dist = 0;
    for (const auto& plane : fov_planes)
    {
        dist = std::min(compute_dist(updated_center, plane), dist);
    }

    if (dist < -bounding_sphere.R)
    {
        info() << "instance is out of view field: " << dist << '\n';
        return true;
    }

    return false;
}